


if __name__ == '__main__':
    import sympy
    
    import kalman_utils.kf_analysis as kfa
    import kalman_utils.kf_operations as kfo
    import kalman_utils.kf_parsing as kfp
    import kalman_utils.kf_generate as kfg
    
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
    
    print('\n')
    print('F : {}'.format(definition.F))
    
    print('\n')
    print('H : {}'.format(definition.H)) 
    
    X_symbols = [sympy.symbols(label) for label in definition.X]
    print(X_symbols)

    print('\nF:')    
    F, errors = kfg.generateMatrixFromDefinition('F', definition.F)
    print(F)
    
    print('\nH:')
    H, errors = kfg.generateMatrixFromDefinition('H', definition.H)
    print(H)

    observable = kfa.calcObservability(F, H)
    if observable:
        print('System is Observable!')
    else:
        print('Warning: System is NOT observable!')
            
    print('\nX:')
    X = kfg.generateSymbolicMatrix('X', len(definition.X), 1) #kfg.generateStateMatrix(definition.X)
    print(X)
    
    #print('\nP:')
    P = kfg.generateSymmetricSymbolicMatrix('P', X.shape[0])
    #print(P)
    
    #print('\nQ:')
    Q = None
    if definition.Q is None:
        Q = kfg.generateSymmetricSymbolicMatrix('Q', X.shape[0])
    else:
        Q, errors = kfg.generateMatrixFromDefinition('Q', definition.Q)
    #print(Q)

    X_pre, P_pre = kfg.generatePredict(F, X, P, Q)
    
    print('\nX_pre:')
    print(X_pre)

    print('\nP_pre:')
    print(P_pre)
    
    stuff, matricies = sympy.cse([X_pre, P_pre])
    
#    symbol, expr0 = stuff[0]
#    print(expr0)
#    mode = kfa.expressionCalculationMode(expr0, definition.params)
#    print(mode)

    ops = kfo.OperationCounts()
    for symbol, expr in stuff:
        mode = kfa.expressionCalculationMode(expr, definition.params)
        definition.params.append(kfp.KalmanFilterParameter(symbol.name, value=expr, mode=mode))
        print('{} {} = {}'.format(mode, symbol, expr))
        if mode == 'dynamic':
            o = kfo.exprOps(expr)
            ops.writes += 1
            ops += o
        
    for matrix in matricies:
        o = kfo.matrixOps(matrix)
        ops += ops
        print(matrix)
    
    naive_ops = kfo.Unoptimized.predictStep(F, X)
    print('Naive predict -> {}'.format(naive_ops))    
    print('Optimized predict -> {}'.format(ops))
    
    # formatter = LabelFormatter()
    # for state in definition.vars:
    #     print(formatter.latex(state.name))
