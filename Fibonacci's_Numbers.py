"""
Условие
Дано натуральное число A. 
Определите, каким по счету числом Фибоначчи оно является, то есть выведите такое число n, что φn = A. 
Если А не является числом Фибоначчи, выведите число -1.
"""
def fib_digit(a):
    i = 1
    if a == 0 :
        return 0
    else:
        x, y = 0, 1
    while y < a:
        x, y = y, x + y
        i += 1
    if y == a:
        return i
    else:
        return -1

def main():
    n = int(input())
    print(fib_digit(n))

if __name__ == "__main__":
    main()