import math

import sympy

def __labels_to_symbols(labels):
    if labels is None: return None
    return [sympy.Symbol(label) for label in labels]

def __extract_mapping_terms(mapping):
    expr = mapping.expr
    if isinstance(expr, sympy.Symbol):
        return [expr]
    return expr.expand().args

# TODO: LOOK INTO AS_COEFF_MUL IN SYMPY...
def __extract_source_coefficient(symbol, terms):
    coefficients = []
    for term in terms:
        if isinstance(term, sympy.Symbol):
            if term == symbol:
                coefficients.append(sympy.Number(1))
        else:
            args = term.args
            valid = any(bool((arg-symbol).expand() == 0) for arg in args)
            subexprs = [arg for arg in args if not bool((arg-symbol).expand() == 0)]
            if valid and not subexprs == []:
                coefficients.append(sympy.Mul(*subexprs))
            else:
                if valid:
                    'Valid but no subexprs'
    coef = sympy.Number(0)
    if len(coefficients) == 1:
        coef = coefficients[0]
    else:
        coef = sympy.Add(*coefficients)                
    return coef

def generateSymbolicMatrix(name, N, M):
    structure = []
    digits = int(math.ceil(max(N, M) / 10.))
    s_fmt = '{{}}_{{:0{digits}d}}{{:0{digits}d}}'.format(digits=digits)
    for row in range(N):
        row_structure = []
        for column in range(M):
            row_structure.append(sympy.Symbol(s_fmt.format(name, row, column)))
        structure.append(row_structure)
    return sympy.Matrix(structure)

def generateSymmetricSymbolicMatrix(name, N):
    structure = []
    digits = int(math.ceil(N / 10.))
    s_fmt = '{{}}_{{:0{digits}d}}{{:0{digits}d}}'.format(digits=digits)
    for row in range(N):
        row_structure = []
        for column in range(N):
            row_structure.append(sympy.Symbol(s_fmt.format(name, min(row, column), max(row, column))))
        structure.append(row_structure)
    return sympy.Matrix(structure)

def generateStateMatrix(labels):
    return sympy.Matrix([[sympy.Symbol(label)] for label in labels])

def generateMatrixFromDefinition(name, matrix_def):
    errors = []
    row_symbols = __labels_to_symbols(matrix_def.row_labels)
    column_symbols = __labels_to_symbols(matrix_def.column_labels)
    if not matrix_def.column_major_mappings:
        temp = row_symbols
        row_symbols = column_symbols
        column_symbols = temp
    matrix = None
    if row_symbols is None and column_symbols is None:
        errors.append('Fatal Error: Neither row or column labels defined for {}!'.format(name))
    elif row_symbols is None:
        errors.append('Fatal Error: Row labels are not defined for {}!'.format(name))        
    elif column_symbols is None:
        errors.append('Fatal Error: Columns labels are not defined for {}!'.format(name))        
    else:
        rows = {}
        for mapping in matrix_def.mappings:        
            dest = mapping.dest
            terms = __extract_mapping_terms(mapping)
            row_coefficients = []
            for src in column_symbols:
                coefficients = __extract_source_coefficient(src, terms)
                row_coefficients.append(coefficients)
            rows[dest] = row_coefficients
            
        row_list = []
        for row in row_symbols:
            if row.name in rows:
                row_list.append(rows[row.name])
            else:
                row_list.append([0]*len(column_symbols))
        matrix = sympy.Matrix(row_list)
        if not matrix_def.column_major_mappings:
            matrix = matrix.transpose()
    return matrix, errors

def generatePredict(F, X, P, Q, B = None, U = None):
    X_pre = None
    if not B is None:
        X_pre = F*X + B*U
    else:
        X_pre = F*X
    X_pre = sympy.simplify(X_pre)
    P_pre = sympy.simplify(F*P*F.transpose() + Q)
    P_pre = P_pre.as_mutable()
    for row in range(P_pre.shape[0]):
        for column in range(P_pre.shape[1]):
            if row > column:
                P_pre[row, column] = 0

    return X_pre, P_pre 

def generateMeasurement(X, H, Z):
    Y_pre = Z - (H * X)
    return Y_pre
    
def generateGainUpdate(H, P, R):
    S = (H * P * H.transpose()) + R
    K = P * H.transpose() * S.inverse()
    
if __name__ == '__main__':
    print(generateSymbolicMatrix('R', 3, 3))