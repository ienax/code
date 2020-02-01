def fact(n):
    if n <= 0:
        return 1
    if n <= 2:
        return n
    return n * fact(n - 1)


def comb(k, n):
    return fact(n) // (fact(k) * fact(n - k))


def main():
    ans = 0
    n = 10
    for i1 in range(1, n):
        m = n - i1
        for i2 in range(1, m + 1):
            ans += comb(i1, n) * comb(i2, m)
    print(ans)

if __name__ == "__main__":
    main()
