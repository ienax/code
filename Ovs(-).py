from sympy import *


def l_rule(t, g, n):
    res = str(limit(t/g, n, oo))
    if res == '0':
        return str(t) + ' имеет меньший порядок роста, чем ' + str(g)
    elif res == 'oo':
        return str(t) + ' имеет больший порядок роста, чем ' + str(g)
    else:
        return str(t) + ' имеет тот же порядок роста, что и ' + str(g)


n = Symbol('n')

funcs = {
    n ** 0.5: 5 ** log(n),
    n * log(n): n,
    sqrt(n): log(n) ** 3,
    100 * n * log(n): n + (log(n) ** 2),
    factorial(n): 2 ** n,
    2 ** n: 2 ** (n + 1),
    10 * log(n): log(n) ** 2
}

for func1, func2 in funcs.items():
    print(l_rule(func1, func2, n))