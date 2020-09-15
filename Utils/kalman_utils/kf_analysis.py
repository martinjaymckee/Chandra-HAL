import sympy

def stateTransitionStable(F):
    eigs = F.eigenvals()
    vecs = F.eigenvects()
    # TODO: IMPLEMENT DYNAMICS STABILITY CHECK
    return False


def calcObservability(F, H):
    O = H
    prod = H
    for _ in range(1, F.shape[0]):
        prod *= F
        O = O.col_join(prod)
    return O.rank() == F.shape[0]


def expression_symbols(expr):
    symbols = set()
    if isinstance(expr, sympy.Symbol):
        symbols.add(expr)
    else:
        for arg in expr.args:
            ss = expression_symbols(arg)
            for s in ss:
                symbols.add(s)
    return symbols

def matrix_symbols(m):
    symbols = set()
    for row in range(m.shape[0]):
        for column in range(m.shape[1]):
            expr = m[row,column]
            symbols.update(expression_symbols(expr))
    return symbols

def __match_parameter(symbol, parameters):
    for param in parameters:
        if param.name == symbol.name:
            return param
    return None


def expressionCalculationMode(expr, parameters):
    mode = 'const'
    symbols = expression_symbols(expr)
    for symbol in symbols:
        param = __match_parameter(symbol, parameters)
        if param is None:
            mode = 'dynamic'
        else:
            if mode == 'const':
                mode = param.mode 
            elif mode == 'init' and param.mode == 'dynamic':
                mode = param.mode
        if mode == 'dynamic': break
    return mode


if __name__ == '__main__':
    x, y, z = sympy.symbols('x y z')
    w = 3*x + 4*x*y - y/z
    symbols = expression_symbols(w)
    print(symbols)