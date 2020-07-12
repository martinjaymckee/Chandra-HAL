import sympy

class OperationCounts:
    def __init__(self, addsubs=0, mults=0, divs=0, cmps=0, reads=0, writes=0):
        self.addsubs = addsubs
        self.mults = mults 
        self.divs = divs
        self.cmps = cmps
        self.reads = reads
        self.writes = writes
    
    def __str__(self):
        return 'Ops(+/- = {}, * = {}, / = {}. cmp = {}, rd = {}, wr = {})'.format(
            self.addsubs, self.mults, self.divs, self.cmps, self.reads, self.writes)
    
    def __add__(self, other):
        ops = OperationCounts()
        ops.addsubs = self.addsubs + other.addsubs
        ops.mults = self.mults + other.mults 
        ops.divs = self.divs + other.divs
        ops.cmps = self.cmps + other.cmps
        ops.reads = self.reads + other.reads
        ops.writes = self.writes + other.writes
        return ops
    
    
class Unoptimized:
    @classmethod
    def matrixAddSub(cls, m0, m1):
        assert m0.shape == m1.shape, 'Fatal Error: Unable to add matricies of shape {} and {}'.format(m0.shape, m1.shape)
        N, M = m0.shape
        return OperationCounts(addsubs=N*M, reads=2*N*M, writes=N*M)

    @classmethod
    def matrixAddSubSymmetric(cls, m0, m1):
        assert m0.shape == m0.shape and m0.shape[0] == m0.shape[1], 'Fatal Error: Symmetric matricies cannot be of shapes {} and {}'.format(m0.shape, m1.shape)
        N = m0.shape[0]
        num = N*N - (((N-1) * (N-1)) / 2)
        return OperationCounts(addsubs=num, reads=2*num, writes=num)
        
    @classmethod
    def matrixMult(cls, m0, m1):
        assert m0.shape[1] == m1.shape[0], 'Fatal Error: Unable to multiply matricies of shape {} and {}'.format(m0.shape, m1.shape)
        N, M = m0.shape
        _, P = m1.shape
        return OperationCounts(addsubs=N*P*(M-1), mults=N*M*P, reads=2*N*M*P, writes=N*P)
       
    @classmethod
    def matrixMultToSymmetric(cls, m0, m1):
        assert m0.shape[1] == m1.shape[0] and m0.shape[0] == m1.shape[1], 'Fatal Error: Unable to multiply matricies of shape {} and {} to symmetric'.format(m0.shape, m1.shape)
        N, M = m0.shape
        _, P = m1.shape
        return OperationCounts(addsubs=N*P*(M-1), mults=N*M*P, reads=2*N*M*P, writes=N*P)
    
    @classmethod
    def GJInversion(cls, m0):
        assert m0.shape[0] == m0.shape[1], 'Fatal Error: Only symmetric matricies may be inverted'
        N = m0.shape[0]
        num = (N**3) + (N**2) - 3*N + 2
        cmps = (N*(N-1))/2
        return OperationCounts(addsubs=num, mults=num, divs=N, cmps=cmps, reads=num, writes=num)
                
    @classmethod
    def predictStep(cls, F, X, B=None, u=None):
        ops = OperationCounts()
        # State Prediction
        # F*X
        ops = ops + cls.matrixMult(F, X)
        if not B is None:
            # B*u
            ops = ops + cls.matrixMult(B, u)
            # (F*X) + (B*u)
            ops = ops + cls.matrixAddSub(X, X)
            
        # Covariance Prediction
        #   A*P
        ops = ops + cls.matrixMult(F, F)
        #   P*At
        ops = ops + cls.matrixMult(F, F)
        #   (A*P*At) + Q
        ops = ops + cls.matrixAddSub(F, F)
        return ops
         
def exprOps(expr):
    """This operation estimation is not handling some simple optimizations that 
    should be done (i.e. y-x is treated as -1*x+y) and it is overestimating multiplications
    in situations such as divisions.  This is as a result of the simple method
    of implementing this function given the rudimentary form of the expression
    tree.  It should only be overestimating the number of operations though,
    so it is a viable way to see how much optimization is improving the 
    computational load of the generated Kalman filters"""
    
    ops = OperationCounts()
    if isinstance(expr, sympy.Symbol) or isinstance(expr, sympy.Number):
        print('--> {}'.format(expr))
        ops.reads += 1
    else:
        func = expr.func
        num = len(expr.args) - 1
        print('--> ({}, {})'.format(func, expr.args))        
        process = True
        if func == sympy.Add:
            ops.addsubs += num
        elif func == sympy.Mul:
            ops.mults += num
        elif func == sympy.Pow:
            if expr.args[1] == -1:
                ops.divs += 1
                process = False
            elif expr.args[1] > 0:
                ops.mults += int(expr.args[1].evalf()-1)
                process = False
            else:
                print('Error: Unknown how to map expression {} to operation counts'.format(expr))
        else:
            print('Unknown function {}'.format(func))
        if process:
            for arg in expr.args:
                o = exprOps(arg)
                ops += o
    return ops
        
def matrixOps(expr_matrix):
    ops = OperationCounts()
    rows, columns = expr_matrix.shape
    for row in range(rows):
        for column in range(columns):
            expr = expr_matrix[row, column]
            if not sympy.simplify(expr - 0) == 0:
                o = exprOps( expr )
                ops += o
                ops.writes += 1
    return ops

def defaultOpWeights(): return (1, 1, 1, 1, 1, 1)        
def fixedpointOpWeights(): return (10, 5, 32, 5, 1, 1) # NOTE: MADE UP
def floatingPointOpWeights(): return (65, 50, 150, 5, 1, 1) # NOTE: MADE UP

def clockCycles(ops, weights=None):
    cycles = 0
    if weights is None: weights = defaultOpWeights() 
    cycles += ops.addsubs * weights[0]
    cycles += ops.mults * weights[1]
    cycles += ops.divs * weights[2]
    cycles += ops.cmps * weights[3]
    cycles += ops.reads * weights[4]
    cycles += ops.writes * weights[5]    
    return cycles

if __name__ == '__main__':
    w, x, y, z = sympy.symbols('w x y z')
    expr = -x + 3*x*y + w**2*(y+z) + y/w
    ops = exprOps(expr)
    print(expr)
    print(ops)