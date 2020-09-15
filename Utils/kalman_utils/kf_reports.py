import string

import sympy

if __name__ == '__main__':
    import kf_analysis as kfa
else:
    from . import kf_analysis as kfa

class LabelFormatter:
    def __init__(self, matrix_symbols=[]):
        self.__matrix_symbols = matrix_symbols
    
    def latex(self, label, wrapped=True): # TODO: DECIDE IF THIS SHOULD WRAP IN A MATH ENVIRONMENT $...$
        name_fmt = '{}'
        tokens = label.split('_')
        name = tokens[0]
        tokens = tokens[1:] if len(tokens) > 1 else []
        if len(name) > 2 and name.startswith('dd'):
            name = name[2:]
            name_fmt = '\ddot{{{}}}'
        elif len(name) > 1 and name.startswith('d'):
            name = name[1:]
            name_fmt = '\dot{{{}}}'
        if len(name) > 1:
            additional_token = name[:].lstrip(string.ascii_uppercase)
            name = name[:-len(additional_token)]
            if len(name) == 0:
                name = additional_token 
            else:
                tokens = [additional_token] + tokens
        subscript = ''
        for token in reversed(tokens):
            subscript = '_{{{}{}}}'.format(token, subscript)
        wrap_char = '$' if wrapped else ''
        return wrap_char + name_fmt.format(name) + subscript + wrap_char

    def code(self, label):
        tokens = label.split('_')
        index = None
        if len(tokens) > 1:
            header = '_'.join(tokens[:-1])            
            if header in self.__matrix_symbols:
                index = tokens[-1]
                N = len(index)
                if N == 1:
                    label = '{}({})'.format(header, index)
                else:
                    row = index[:int(N/2)]
                    column = index[int(N/2):]
                    label = '{}({}, {})'.format(header, row, column)
        return label


class MatrixFormatter:
    def __init__(self, matrix_symbols=[]):
        self.__matrix_symbols = matrix_symbols
    
    def latex(self, m, label=None, equation=True):
        symbols = kfa.matrix_symbols(m)
        symbol_fmt = LabelFormatter()
        symbol_map = {symbol:symbol_fmt.latex(symbol.name, wrapped=False) for symbol in symbols}
        matrix_core = sympy.latex(m, symbol_names=symbol_map)
        matrix_header = '' if label is None else '{} = '.format(symbol_fmt.latex(label, wrapped=False))
        matrix_wrap = '\\begin{{equation}}{}{}\\end{{equation}}' if equation else '{}'
        return matrix_wrap.format(matrix_header, matrix_core)
    
    def code(self, m):
        pass
    

class CppGenerator:
    def __init__(self, matrix_symbols=[]):
        self.__label_fmt = LabelFormatter(matrix_symbols=matrix_symbols)
    
    def format(self, expr, wrap=False):
        def wrapper(result):
            if wrap:
                return '({})'.format(result)
            else:
                return result
        #print(type(expr))
        if isinstance(expr, sympy.Symbol):
            return self.__label_fmt.code(expr.name)
        elif expr.is_rational and not expr.is_Integer:
            return 'Value({})'.format(expr.evalf())
        if isinstance(expr, sympy.Pow):
            assert len(expr.args) == 2, 'Error invalid Power (wrong number of arguments)'
            assert expr.args[1].is_Integer and expr.args[1].is_positive, 'Error only raising to positive integer is implemented'
            return wrapper(' * '.join([self.format(expr.args[0], wrap=True)]*int(expr.args[1].evalf())))
        
        formatted_args = [self.format(arg, wrap=True) for arg in expr.args]
        #print(formatted_args)
        if isinstance(expr, sympy.Add):
            return wrapper(' + '.join(formatted_args))
        elif isinstance(expr, sympy.Mul):
            return wrapper(' * '.join(formatted_args))
        #print('***', type(expr), str(expr))
        return str(expr)
    
    
if __name__ == '__main__':
    import sympy
    dt = sympy.Symbol('dt')
    c = sympy.Symbol('c')
    F = sympy.Matrix([[1, dt, dt**2/2], [0, 1, dt], [0, 0, 1]])
    H = sympy.Matrix([[1, 0, 0], [0, 1, 0]])
    Q = 0.25 * sympy.eye(3)
    R = 0.18 * sympy.eye(2)
    matrix_fmt = MatrixFormatter() 
    F_str = matrix_fmt.latex(F, label='F')
    print(F_str)
    label_fmt = LabelFormatter(matrix_symbols = ['X_pre', 'X_post', 'F', 'H', 'P'])
    print(label_fmt.latex('x_60'))
    print(label_fmt.code('X_6'))
    print(label_fmt.code('X_pre_6'))
    print(label_fmt.code('P_57'))    
    print(label_fmt.code('P_5782')) 
    x, y, z, P_14 = sympy.symbols('x y z P_14')  
    w = 2*x + y**3 - P_14*z
    expr_fmt = CppGenerator(['X_pre', 'X_post', 'F', 'H', 'P', 'Q', 'R'])
    print(expr_fmt.format(w))
    
    