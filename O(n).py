from sympy import limit, Symbol, oo, log, sqrt, factorial

n = Symbol('n')
exprList = [
    n ** 0.3, sqrt(n), 4*n, log(n, 5),
    n * (log(n, 2)), n * ( log(n, 2) * log(n, 2) * log(n, 2) ), n ** 3,   
]

def exprSort(l):
    for i in range(len(l)):
        for j in range(i+1, len(l)):
            if limit(l[i] / l[j], n, oo) == oo:
                l[i], l[j] = l[j], l[i]


exprSort(exprList)
print(*exprList, sep='\n')