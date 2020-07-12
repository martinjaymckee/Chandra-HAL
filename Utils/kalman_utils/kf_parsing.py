import itertools
import string


import sympy
import sympy.parsing.sympy_parser

class KalmanFilterParameter:
    def __init__(self, name, value=None, mode='const'):
        self.__name = name
        self.__value = value
        self.__mode = mode
        self.__msg = 'ok'
        
    def __str__(self):      
        #if not self.valid: return 'Invalid({})'.format(self.name)
        if self.value is None:
            return '{} {}'.format(self.mode, self.name)
        return '{} {} = {}'.format(self.mode, self.name, self.value)
    
    @property
    def name(self): return self.__name
    
    @property
    def value(self): return self.__value
    
    @property
    def mode(self): return self.__mode
    
    @property
    def valid(self):
        self.__msg = 'ok'
        if not self.mode in ['const', 'init', 'dynamic']:
            self.__msg = 'Invalid mode, {}'.format(self.__mode)
            return False
        if self.name is None:
            self.__msg = 'Name was undefined'
            return False
        if self.__mode == 'dynamic' or self.__mode == 'init':
#            print('{}, {}, {}'.format(self.__name, self.__mode, self.__value))
            if not self.__value is None:
                self.__msg = 'Value was defined with mode {}'.format(self.mode)
                return False
            return True
        if self.value is None:
            self.__msg = 'Value was undefined in constant, mode = {}'.format(self.mode)
            return False 
        return True 
    
    @property
    def msg(self):
        self.valid
        return self.__msg
        
    
class KalmanFilterMappingExpr:
    def __init__(self, dest, expr):
        self.__dest = dest
        self.__expr = sympy.sympify(expr).simplify() 
        self.__msg = 'ok'
        
    def __str__(self):
        return '{} <- {}'.format(self.__dest, self.__expr)
    
    @property
    def dest(self): return self.__dest
    
    @property
    def expr(self): return self.__expr
    
    @property
    def valid(self):
        self.__msg = 'ok'
        return True
    
    @property
    def msg(self): return self.__msg 
    
    
class KalmanFilterMatrixDefinition:
    def __init__(self, mappings, row_labels=None, column_labels=None, column_major_mappings=False):
        self.__mappings = mappings
        self.__row_labels = row_labels
        self.__column_labels = column_labels
        self.__column_major_mappings = column_major_mappings
        self.__msg = 'ok'    
    
    def __str__(self):
        text = '[\n'
        text += '\tRows : <{}>\n'.format(None if self.__row_labels is None else ', '.join(self.__row_labels))
        text += '\tColumns : <{}>\n'.format(None if self.__column_labels is None else ', '.join(self.__column_labels))
        text += '\tM = {}\n'.format(None if self.__row_labels is None else len(self.__row_labels))
        text += '\tN = {}\n'.format(None if self.__column_labels is None else len(self.__column_labels))        
        if len(self.__mappings) > 0:
            text += '\n\tMappings(by {}):\n'.format('column' if self.__column_major_mappings else 'row')
            for mapping in self.__mappings:
                if mapping.valid:
                    expr = mapping.expr
                    text += '\t{} <- {}\n'.format(mapping.dest, expr)
                else:
                    if not mapping.dest is None:
                        text += '\t{} <- INVALID\n'.format(mapping.dest)
                    else:
                        text += '\tINVALID\n'
        text += ']'
        return text
    
    @property
    def mappings(self):
        return self.__mappings 
    
    @property
    def row_labels(self): return self.__row_labels
    
    @row_labels.setter
    def row_labels(self, labels):
        self.__row_labels = labels 
        return self.__row_labels 
    
    @property
    def column_labels(self): return self.__column_labels
    
    @column_labels.setter
    def column_labels(self, labels):
        self.__column_labels = labels 
        return self.__column_labels 

    @property
    def column_major_mappings(self): return self.__column_major_mappings
    
    @property
    def valid(self): # TODO: REARRANGE THESE CHECKS TO GET RID OF MULTIPLE PASSES
        self.__msg = 'ok'
        success = True
        dests = []
        exprs = []
        for mapping in self.__mappings:
            if not mapping.valid:
                self.__msg = 'mapping expression ({}) invalid'.format(mapping.msg)
                success = False
                break
            else:
                dests.append(mapping.dest)
                exprs.append(mapping.expr)
        if success:
            success = set(dests) == set(self.__column_labels)
        
        if success:
            if self.__column_labels is None:
                self.__msg = 'column labels are undefined'
                success = False
            else:
                for dest, expr in zip(dests, exprs):
                    if not self.is_linear(expr):
                        self.__msg = 'expression ({}) is not linear'
                        success = False
                        break
        return success
    
    @property
    def msg(self): return self.__msg 
    
    def is_linear(self, expr):
        variables = [sympy.symbols(label) for label in self.__column_labels]
        combs = itertools.combinations_with_replacement(variables, 2)
        try:
            return all(sympy.Eq(sympy.diff(expr, *t), 0) for t in combs)
        except TypeError:
            return False   
    
class KalmanFilterDefinition:
    def __init__(self):
        self.params = []
        self.X = None
        self.U = None
        self.Z = None 
        self.F = None
        self.B = None
        self.Q = None
        self.H = None
        self.R = None

    @property
    def valid(self):
        # X is None or it exists and all state values in X are defined in F
        # F uses only defined variables or other state values
        # H uses only defined variables or input values
        # No matrix has non-linear functions of states present
        return True

        
def parseParameter(mode, text):
    name = None 
    value = None
    if not text.find('=') == -1:
        head, _, tail = text.partition('=')
        name = head.strip()
        expr = sympy.parsing.sympy_parser.parse_expr(tail.strip())
        value = float(expr)
    else:
        name = text.strip()
    return KalmanFilterParameter(name = name, value = value, mode = mode)
    

def parseTokenList(buffer, delimiter=','):
    if buffer is None or len(buffer) <= 2: return None
    idx_start = buffer.find('[')
    idx_end = buffer.find(']')
    if idx_start == -1: return None
    tokens = buffer[idx_start+1:idx_end].split(delimiter)
    tokens = [token.strip() for token in tokens]
    tokens = [token for token in tokens if not token == '']
    return tokens
    

def parseStateLabels(buffer):
    errors = []
    token_list = parseTokenList(buffer, ',')
    if token_list is None: return None
    if not len(token_list) == len(set(token_list)):
        errors.append('duplicate labels defined')
    return token_list, errors
    

def parseMatrixDefinition(buffer, column_major_mappings=False):
    definition = None
    errors = []
    mapping_lines = parseTokenList(buffer, delimiter='\n')
    mappings = []
    for mapping in mapping_lines:
        dest, _, expr = mapping.partition('<-')
        dest = dest.strip()
        expr = expr.strip()
        if dest == '':
            pass # TODO: INVALID DESTINATION ERROR
        if expr == '':
            pass # TODO: INVALID EXPRESSION ERROR
        mappings.append(KalmanFilterMappingExpr(dest, expr))
    definition = KalmanFilterMatrixDefinition(mappings, column_major_mappings=column_major_mappings)
    return definition, errors

def setStateLabels(definition, value, values):
    # TODO HANDLE ANY ERRORS HERE
    setattr(definition, value, values)
    
def setMatrixDefinition(definition, value, components):
    setattr(definition, value, components)
    
def parseKalmanFilterDefinition(file):
    parameter_modes = ['const', 'init', 'dynamic']
    state_defs = ['X', 'Z']
    matrix_defs = ['F', 'Q', 'H', 'R']
    column_major_matrix_defs = ['H']
    definition = KalmanFilterDefinition()
    errors = []
    scope = 'global'
    block = None
    buffer = []
    ref_num = 0
    for num, line in enumerate(file):
        num += 1
        line = line.strip()
        head, _, comment = line.partition('#')
        if not head == '': 
            leading, tail = (head, '') if len(head) == 1 else head.split(None, 1)
            if scope == 'global':
                if leading in parameter_modes:
                    param = parseParameter(leading, tail)
                    msg = param.msg
                    if msg == 'ok':
                        definition.params.append(param)
                    else:
                        err = 'Warning({}): Invalid parameter declaration -- {}\n\t -> \'{}\' '.format(num, msg, head)
                        errors.append(err)
                elif leading in state_defs:
                    block = leading
                    if ']' in line:
                        states, errs = parseStateLabels(tail)
                        for err in errs:
                            errors.append('Fatal Error({}): Failure parsing state labels for block {} -- {}'.format(num, block, err))
                        if not states is None and len(errs) == 0:
                            setStateLabels(definition, block, states)
                    else:
                        scope = 'value_defs'
                        ref_num = num
                        buffer = tail
                elif leading in matrix_defs:
                    block = leading
                    if ']' in line:
                        column_major_mappings = not block in column_major_matrix_defs
                        matrix_def, errs = parseMatrixDefinition(tail, column_major_mappings)
                        if len(errs) == 0:
                            setMatrixDefinition(definition, block, matrix_def)
                    else:
                        ref_num = num
                        buffer = tail + '\n'
                        scope = 'matrix_defs'
                else:
                    assert False, 'Fatal Error: unknown value {} found while parsing line in scope {}'.format(leading, scope)
            elif scope == 'value_defs':
                buffer += line 
                if ']' in line:
                    values, errs = parseStateLabels(buffer)
                    for err in errs:
                        errors.append('Fatal Error({}): Failure parsing state labels for block {} -- {}'.format(ref_num, block, err))
                    if not values is None:
                        setStateLabels(definition, block, values)
                    scope = 'global'
            elif scope == 'matrix_defs':
                buffer += (line + '\n')
                if ']' in line:
                    column_major_mappings = not block in column_major_matrix_defs
                    matrix_def, errs = parseMatrixDefinition(buffer, column_major_mappings)
                    if len(errs) == 0:
                        setMatrixDefinition(definition, block, matrix_def)
                    scope = 'global'
    return definition, errors