#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>

int64_t read_int64() { int64_t i; scanf("%" SCNd64 , &i); return i; }
size_t read_size() { size_t i; scanf("%zu", &i); return i; }

int64_t** marray_read( size_t* rows, size_t* sizes[] ) {
    size_t n = read_size();
    *rows = n;
    *sizes = malloc(n * sizeof(size_t));
    int64_t **array = (int64_t **)malloc(n*sizeof(int64_t*));
    size_t m = 0;
    for (size_t i = 0; i < n; i++) {
        m = read_size();
        (*sizes)[i] = m;
        array[i] = (int64_t *)malloc(m*sizeof(int64_t));
        for (size_t j = 0; j < m; j++) {
            array[i][j] = read_int64();
        }
    }
    return array;
}

void marray_free( int64_t** marray, size_t rows ) {
    for (size_t i = 0; i < rows; i++) {
        free(marray[i]);
    }
    free(marray);
}

void marray_print(int64_t** marray, size_t* sizes, size_t rows) {
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < sizes[i]; j++) {
            printf("%" PRId64 " ", marray[i][j]);
        }
        printf("\n");
    }
}

int64_t* int64_ptr_min(int64_t* x, int64_t* y) {
    if (x == NULL && y == NULL) return NULL;
    if (*x < *y) return x;
    else return y;
}

int64_t* marray_int_min( int64_t** marray, size_t* sizes, size_t rows ) {
    int64_t *minp = NULL;
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < *(sizes + i); j++) {
            if (i == 0 && j == 0) {
                minp = &marray[0][0];
                continue;
            }
            minp = int64_ptr_min(minp, &marray[i][j]);
        }
    }
    return minp;
}

void marray_normalize( int64_t** marray, size_t* sizes, size_t rows, int64_t m ) {
    size_t i, j;
    for(i = 0; i < rows; i++){
        for(j = 0; j < sizes[i]; j++){
            marray[i][j] = marray[i][j] - m;
        }
    }
}

void marray_garbage_collector( int64_t** marray, size_t* sizes, size_t rows) {
    marray_free(marray, rows);
    free(sizes);
}

//Теперь поработаем с массивом массивов. Нам требуется:
//
//считать его;
//найти минимальный элемент M (один на весь массив массивов);
//вычесть M изо всех элементов массива массивов;
//вывести результат.
int perform() {
    size_t rows;
    size_t* sizes;
    int64_t* min;
    int64_t** marray;
    marray = marray_read(&rows, &sizes);
    if(marray == NULL)
        return 1;
    min = marray_int_min(marray, sizes, rows);
    if(min){
        marray_normalize(marray, sizes, rows, *min);
        marray_print(marray, sizes, rows);
        return 1;
    }
    marray_garbage_collector(marray, sizes, rows);
    return 0;
}

int main(){
    return perform();
}
