import functools

import mako
import mako.template 
import sympy
import sympy.printing
import sympy.printing.cxxcode

import kalman_utils.kf_analysis as kfa
import kalman_utils.kf_operations as kfo
import kalman_utils.kf_parsing as kfp
import kalman_utils.kf_generate as kfg
import kalman_utils.kf_reports as kfr

def determineSubexpressionOperations(cse_subexprs):
    subexpr_ops = kfo.OperationCounts()
    calculation_map = {'const':[], 'init':[], 'dynamic':[]}
    for symbol, expr in cse_subexprs:
        mode = kfa.expressionCalculationMode(expr, definition.params)
        definition.params.append(kfp.KalmanFilterParameter(symbol.name, value=expr, mode=mode, calc=True))
        if mode == 'dynamic':
            o = kfo.exprOps(expr)
            subexpr_ops.writes += 1
            subexpr_ops += o
        calculation_map[mode].append(symbol)
    return subexpr_ops, calculation_map


def determineMatrixOperations(matricies):
    ops = kfo.OperationCounts()
    for matrix in matricies:
        ops += kfo.matrixOps(matrix)
    return ops


def dependencySymbols(expressions, subexpressions, dependency_dict=None):
    symbols = set()
    subexpr_map = {expr[0]:expr[1] for expr in subexpressions}
    for expr in expressions:
        expr_symbols = kfa.expression_symbols(expr)
        for s in expr_symbols:
            if s in subexpr_map and not s in symbols:
                symbols.add(s)
                dependencies = set()  
                if not dependency_dict is None and s in dependency_dict.keys():
                    dependencies = dependency_dict[s]
                else:
                    expr = subexpr_map[s]
                    results = dependencySymbols([expr], subexpressions, dependency_dict)
                    if dependency_dict is None:
                        dependencies = results 
                    else:
                        dependencies = results[0]
                        dependency_dict = dependency_dict.copy()
                        dependency_dict[s] = dependencies
                symbols.update(dependencies)
    if dependency_dict is None:
        return symbols
    return symbols, dependency_dict

    
def determineStepDependencies(matricies, subexpressions, dependency_dict=None):
    subexpr_map = {expr[0]:expr[1] for expr in subexpressions}
    symbols = set()
    for matrix in matricies:
        symbols.update(kfa.matrix_symbols(matrix))
    expressions = [subexpr_map[s] for s in symbols if s in subexpr_map]
    results = dependencySymbols(expressions, subexpressions, dependency_dict)
    if dependency_dict is None:
        return symbols, results    
    dependencies = results[0]
    dependency_dict = dependency_dict.copy()
    for s, deps in results[1].items():
        dependency_dict[s] = deps
    return symbols, dependencies, dependency_dict
        

def formatOrderedSet(input_set):
    input_set = list(input_set)
    input_set.sort(key=lambda x: str(x))
    return '{{ {} }}'.format(', '.join([str(v) for v in input_set]))


def subexpressionOrder(subexpressions, dependency_dict):
    def subexpr_less(opa, opb):
        dep_a, _ = dependencySymbols([opa[1]], subexpressions, dependency_dict)
        dep_b, _ = dependencySymbols([opb[1]], subexpressions, dependency_dict)
        if opa[0] in dep_b:
            assert opb[0] in dep_a, 'Error: Circular dependency!'
            return True
        return False
    return sorted(subexpressions, key=functools.cmp_to_key(subexpr_less))


def orderedSubexpressionSubset(subexpressions, ordered_reference):
    ordered_list = []
    for s, expr in ordered_reference:
        if s in subexpressions:
            ordered_list.append( (s, expr) )
    return ordered_list


def subexpressionDescriptions(subexpressions, ordered_reference, member_subexpressions):
    ordered_list = orderedSubexpressionSubset(subexpressions, ordered_reference)
    return [(s in member_subexpressions, s, expr) for s, expr in ordered_list]
    

if __name__ == '__main__':
    
    filename = 'kalman_gen_test.def'
    
    definition = None
    errors = []
    with open(filename) as file:
        definition, errors = kfp.parseKalmanFilterDefinition(file)

    if len(errors) > 0:
        print('Errors:')
    for error in errors:
        print('\t' + error)
            
    print('\nParameters:')
    for param in definition.params:
        print('{}'.format(param))
        
    print('\nState Values: {}'.format(definition.X))
    print('\nInput Values: {}'.format(definition.U))
    print('\nMeasurement Values: {}'.format(definition.Z))
    
    definition.F.row_labels = definition.X 
    definition.F.column_labels = definition.X
    
    definition.H.row_labels = definition.Z 
    definition.H.column_labels = definition.X
    
    if not definition.Q is None:
        definition.Q.row_labels = definition.X 
        definition.Q.column_labels = definition.X
        
    if not definition.R is None:
        definition.R.row_labels = definition.Z 
        definition.R.column_labels = definition.Z
        
    print('\n')
    print('F : {}'.format(definition.F))
    
    print('\n')
    print('H : {}'.format(definition.H)) 
    
    X_symbols = [sympy.symbols(label) for label in definition.X]

    
    F, errors = kfg.generateMatrixFromDefinition('F', definition.F)
    
    H, errors = kfg.generateMatrixFromDefinition('H', definition.H)
    
    Z = kfg.generateSymbolicMatrix('Z', len(definition.Z), 1)
    
    observable = kfa.calcObservability(F, H)
    if observable:
        print('System is Observable!')
    else:
        print('Warning: System is NOT observable!')
    
        
    X = kfg.generateSymbolicMatrix('X_post', len(definition.X), 1) #kfg.generateStateMatrix(definition.X)

    
    P = kfg.generateSymmetricSymbolicMatrix('P', X.shape[0])

    
    Q = None
    if definition.Q is None:
        Q = kfg.generateSymmetricSymbolicMatrix('Q', X.shape[0])
    else:
        Q, errors = kfg.generateMatrixFromDefinition('Q', definition.Q)

    R = None
    if definition.R is None:
        R = kfg.generateSymmetricSymbolicMatrix('R', Z.shape[0])
    else:
        R, errors = kfg.generateMatrixFromDefinition('R', definition.R)
        for err in errors:
            print(err)
        assert not R is None, 'Error creating measurement covariance matrix.'
    
    X_pre, P_pre = kfg.generatePredict(F, X, P, Q)
    Y_pre = kfg.generateMeasurement(X_pre, H, Z)
    S, b, K = kfg.generateGainUpdate(H, P_pre, R)
    X_post, P_post = kfg.generateCorrect(X_pre, K, Y_pre, H, P_pre)
    
    constant_parameters = definition.const_params
    constant_parameters = [(sympy.Symbol(p.name), p.value) for p in constant_parameters]
    print('constant parameters -> {}'.format([str(param) for param in constant_parameters]))
    
    input_matricies = [X_pre, P_pre, Y_pre, S, b, P_post]
    input_matricies = [m.subs(constant_parameters) for m in input_matricies]
    subexpressions, matricies = sympy.cse(input_matricies)
    X_pre_opt, P_pre_opt, Y_pre_opt, S_opt, b_opt, P_post_opt = matricies
    
    print('\n\n')
    
    unoptimized_ops = kfo.OperationCounts()
    optimized_ops = kfo.OperationCounts()
    
    subexpr_ops, subexpr_map = determineSubexpressionOperations(subexpressions)
    print('Subexpression Operations -> {}'.format(subexpr_ops))
    print('{} subexpressions'.format(len(subexpressions)))
    print('{} const subexpressions'.format(len(subexpr_map['const'])))
    print('{} init subexpressions'.format(len(subexpr_map['init'])))    
    print('{} dynamic subexpressions\n'.format(len(subexpr_map['dynamic'])))
    optimized_ops += subexpr_ops
    
    subexpression_set = set([expr[0] for expr in subexpressions])
    remaining_subexpression_set = subexpression_set.copy()
    redundant_subexpressions = set() 
    dependency_dict = {}
    
    
    for s, expr in subexpressions:
        symbols, dependency_dict = dependencySymbols([expr], subexpressions, dependency_dict)
        if not s in dependency_dict:
            dependency_dict[s] = symbols
    
    init_subexpressions = subexpr_map['init']
    remaining_subexpression_set -= set(init_subexpressions)
    
    naive_ops = kfo.Unoptimized.predictStep(F, X_pre)
    unoptimized_ops += naive_ops
    ops = determineMatrixOperations([X_pre_opt, P_pre_opt])
    optimized_ops += ops
    predict_symbols, predict_dependencies, dependency_dict = determineStepDependencies([X_pre_opt, P_pre_opt], subexpressions, dependency_dict)
    print('Naive predict -> {}'.format(naive_ops))    
    print('Optimized predict -> {}'.format(ops)) 
    predict_subexpressions = {s for s in predict_symbols.union(predict_dependencies) if s in subexpression_set}
    calc_predict_subexpressions = {s for s in predict_subexpressions if s in remaining_subexpression_set}    
    print('Predict subexpressions ({}) -> {}\n'.format(len(predict_subexpressions), formatOrderedSet(predict_subexpressions)))
    remaining_subexpression_set -= predict_subexpressions 
    
    naive_ops = kfo.Unoptimized.measureStep(H, X_pre, Z)
    unoptimized_ops += naive_ops
    ops = determineMatrixOperations([Y_pre_opt])
    optimized_ops += ops
    measure_symbols, measure_dependencies, dependency_dict = determineStepDependencies([Y_pre_opt], subexpressions, dependency_dict)
    print('Naive measure -> {}'.format(naive_ops))    
    print('Optimized measure -> {}'.format(ops))
    measure_subexpressions = {s for s in measure_symbols.union(measure_dependencies) if s in subexpression_set}
    calc_measure_subexpressions = {s for s in measure_subexpressions if s in remaining_subexpression_set}
    redundant_measure_subexpressions = measure_subexpressions - calc_measure_subexpressions
    print('Measure subexpressions ({}) -> {}\n'.format(len(calc_measure_subexpressions), formatOrderedSet(calc_measure_subexpressions)))
    remaining_subexpression_set -= calc_measure_subexpressions 
    redundant_subexpressions |= redundant_measure_subexpressions 
    
    naive_ops = kfo.Unoptimized.gainUpdateStep(H, P_pre, R)
    unoptimized_ops += naive_ops
    ops = determineMatrixOperations([S_opt, b_opt])
    ops += kfo.Unoptimized.LDLSolve(S, b)
    ops += kfo.Unoptimized.matrixTranspose(K)
    optimized_ops += ops
    gain_update_symbols, gain_update_dependencies, dependency_dict = determineStepDependencies([S_opt, b_opt], subexpressions, dependency_dict)
    print('Naive gain update -> {}'.format(naive_ops))    
    print('Optimized gain update -> {}'.format(ops))
    gain_update_subexpressions = {s for s in gain_update_symbols.union(gain_update_dependencies) if s in subexpression_set}
    calc_gain_update_subexpressions = {s for s in gain_update_subexpressions if s in remaining_subexpression_set}
    redundant_gain_update_subexpressions = gain_update_subexpressions - calc_gain_update_subexpressions
    print('Gain update subexpressions ({}) -> {}\n'.format(len(calc_gain_update_subexpressions), formatOrderedSet(calc_gain_update_subexpressions)))
    remaining_subexpression_set -= calc_gain_update_subexpressions
    redundant_subexpressions |= redundant_gain_update_subexpressions 
        
    naive_ops = kfo.Unoptimized.correctStep(H, K, X_pre, Y_pre, P_pre)
    unoptimized_ops += naive_ops 
    ops = determineMatrixOperations([P_post_opt])
    ops += kfo.Unoptimized.matrixAddSub(X_pre, X_pre)
    ops += kfo.Unoptimized.matrixMult(K, Y_pre)
    optimized_ops += ops
    correct_symbols, correct_dependencies, dependency_dict = determineStepDependencies([P_post_opt], subexpressions, dependency_dict)
    print('Naive correct -> {}'.format(naive_ops))    
    print('Optimized correct -> {}'.format(ops))  
    correct_subexpressions = {s for s in correct_symbols.union(correct_dependencies) if s in subexpression_set}
    calc_correct_subexpressions = {s for s in correct_subexpressions if s in remaining_subexpression_set}
    redundant_correct_subexpressions = correct_subexpressions - calc_correct_subexpressions
    print('Correct subexpressions ({}) -> {}\n'.format(len(calc_correct_subexpressions), formatOrderedSet(calc_correct_subexpressions)))
    remaining_subexpression_set -= calc_correct_subexpressions
    redundant_subexpressions |= redundant_correct_subexpressions 
     
    print('Total Unoptimized -> {}'.format(unoptimized_ops))    
    print('Total Optimized -> {}\n'.format(optimized_ops))
    print('Member subexpressions ({}) -> {}\n'.format(len(redundant_subexpressions), formatOrderedSet(redundant_subexpressions)))
    local_subexpressions = subexpression_set.difference(redundant_subexpressions)
    print('Local subexpressions ({}) -> {}\n'.format(len(local_subexpressions), formatOrderedSet(local_subexpressions)))

    ordered_subexpressions = subexpressionOrder(subexpressions, dependency_dict)
    ordered_keys = [s[0] for s in ordered_subexpressions]
    for s, expr in ordered_subexpressions:
        mode = 'dynamic'
        if s in subexpr_map['init']: 
            mode = 'init'
        elif s in subexpr_map['const']:
            mode = 'const'
        print('{} {} -> {}'.format(mode, s, expr))

    init_subexpressions = subexpressionDescriptions(init_subexpressions, ordered_subexpressions, redundant_subexpressions)
    predict_subexpressions = subexpressionDescriptions(calc_predict_subexpressions, ordered_subexpressions, redundant_subexpressions)
    measure_subexpressions = subexpressionDescriptions(calc_measure_subexpressions, ordered_subexpressions, redundant_subexpressions)
    gain_update_subexpressions = subexpressionDescriptions(calc_gain_update_subexpressions, ordered_subexpressions, redundant_subexpressions)
    correct_subexpressions = subexpressionDescriptions(calc_correct_subexpressions, ordered_subexpressions, redundant_subexpressions)
            
    member_vars = orderedSubexpressionSubset(redundant_subexpressions, ordered_subexpressions)
    
    mytemplate = mako.template.Template(filename='./kalman_utils/kf_template.mako.h')
    subs_dict = {
        'kf_class_name':'TestKF', 
        'state_size':len(definition.X), 
        'measurement_size':len(definition.Z), 
        'init_params' : definition.init_params,
        'init_subexprs' : init_subexpressions,        
        'predict_subexprs': predict_subexpressions,
        'predict_matricies': [],
        'measure_subexprs': measure_subexpressions,
        'measure_matricies': [],
        'gain_update_subexprs': gain_update_subexpressions,
        'gain_update_matricies': [],
        'correct_subexprs': correct_subexpressions,
        'correct_matricies': [],
        'member_vars': member_vars
    }

#    print(mytemplate.render(**subs_dict))
#    print(mytemplate.render(kf_class_name='TestKF', state_size=9, measurement_size=4))

    try:
        header = mytemplate.render(**subs_dict)
        print(header)
        with open('kf_output_file.hpp', 'w') as f:
            f.write(header)
    except:
        print(mako.exceptions.text_error_template().render())
         
    label_formatter = kfr.LabelFormatter(matrix_symbols=['X_pre', 'X_post', 'P_pre', 'P_post', 'F', 'H', 'Q', 'R', 'K'])
    user_functions = {'Symbol':lambda s: label_formatter.code(s.name)}

    for s, expr in subexpressions:
        print(sympy.cxxcode(expr, assign_to=s, user_functions=user_functions))
        
    # print('GENERATE REPORTS')
    # matrix_fmt = kfr.MatrixFormatter() 
    # print(matrix_fmt.latex(F, label='F'))
    # print()
    # print(matrix_fmt.latex(H, label='H'))
    # print()
    # print(matrix_fmt.latex(X_pre_opt, label='X_pre'))
    # print()
    # print(matrix_fmt.latex(P_pre_opt, label='P_pre'))
    # print()
    # print(matrix_fmt.latex(Y_pre_opt, label='Y_pre'))
    # print()
    # print(matrix_fmt.latex(S_opt, label='S'))
    # print()
    # print(matrix_fmt.latex(b_opt, label='b'))
    # print()
    # print(matrix_fmt.latex(X_post, label='X_post'))    
    # print()
    # print(matrix_fmt.latex(P_post_opt, label='P_post'))    
    
    # formatter = LabelFormatter()
    # for state in definition.vars:
    #     print(formatter.latex(state.name))