#include <stdio.h>

//Оптимизированное вычисление квадратного корня
unsigned int isqrt(unsigned int x)
{
    register unsigned int m, y, b;
    m = 0x4000;
    y = 0;
    while (m != 0){
        b = y | m;
        y = y >> 1;
        if (x >= b) {
            x = x - b;
            y = y | m;
        }
        m = m >> 2;
    }
    return y;
}

//Проверка числа на простоту
int is_prime(int n){
    register int i;
    int stop;
    if (n > 1) {
        stop = n/2;
        for (i = 2; i < stop; i++)
            if (n % i == 0)
                return 0;
        return i;
    }
    else
        return 0;
}
//Факторизация положительного числа n на a и b
void factorize( int n, int* a, int* b )
{
    register int i, ii;
    int start, stop, stop1;
    if(!(n > 0)) return;
    if (n == 1 || (is_prime(n) != 0)){
        *a = 1;
        *b = n;
        return;
    }
    else{
        if(n % 2 != 0)
            start = 1;
        else
            start = 2;
        stop = n/2;
        stop1 = isqrt(n);
        for(i = start; i <= stop1; i = i + 2){
            for(ii = start; ii <= stop; ii = ii + 2){
                if(i * ii == n){
                    *a = i;
                    *b = ii;
                    return;
                }
            }
        }
    }
}

int main() {
    int size, a, b;
    scanf("%d", &size);
    factorize(size, &a, &b);
    printf("a: %d, b: %d", a, b);
    return 0;
}
