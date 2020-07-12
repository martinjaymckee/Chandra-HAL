
class LabelFormatter:
    def __init__(self):
        pass
    
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
        return label

