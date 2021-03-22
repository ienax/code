#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct maybe_int64 {
    bool valid;
    int64_t value;
};

const struct maybe_int64 none_int64 = {0};

struct maybe_int64 some_int64(int64_t i) {
    return (struct maybe_int64) {.value = i, .valid = true};
}

struct list {
    int64_t value;
    struct list *next;
};

int64_t read_int64() {
    int64_t i;
    scanf("%" SCNd64, &i);
    return i;
}

struct list *node_create(int64_t value) {
    struct list *tmp = (struct list *) malloc(sizeof(struct list));
    tmp->value = value;
    tmp->next = NULL;
    return tmp;
}

void list_add_front(struct list **old, int64_t value) {
    struct list *tmp = node_create(value);
    tmp->next = (*old);
    (*old) = tmp;
}

size_t list_length(const struct list *head) {
    size_t counter;
    struct list prev;
    if (head == NULL)
        return 0;
    counter = 1;
    prev = *head;
    while (prev.next) {
        prev = *(prev.next);
        counter++;
    }
    return counter;
}

void list_destroy(struct list *list) {
    struct list *local_list;
    while (list) {
        local_list = list;
        list = list->next;
        free(local_list);
    }
}

struct list *list_last(struct list *list) {
    if (list == NULL)
        return NULL;
    printf("Элементы связного списка: ");
    while (list->next) {
        printf("%zu ", list->value);
        list = list->next;
    }
    printf("\n");
    return list;
}

void list_add_back(struct list **list, int64_t value) {
    for (; *list != NULL; list = &(*list)->next);
    *list = node_create(value);
}

int64_t list_sum(const struct list *list) {
    int64_t counter;
    struct list prev;
    if (list == NULL)
        return 0;
    prev = *list;
    counter = prev.value;
    while (prev.next) {
        prev = *(prev.next);
        counter += prev.value;
    }
    return counter;
}

struct maybe_int64 list_at(const struct list *list, size_t idx) {
    struct list prev;
    if (list == NULL)
        return none_int64;
    prev = *list;
    while (prev.next && idx) {
        prev = *(prev.next);
        idx--;
    }
    if (idx && prev.next == NULL)
        return none_int64;
    return some_int64(prev.value);
}

// создать перевернутую копию списка
struct list *list_reverse(const struct list *list) {
    if (list == NULL)
        return NULL;
    struct list prev = *list;
    struct list *rev_list = {0};
    list_add_front(&rev_list, prev.value);
    while (prev.next) {
        prev = *(prev.next);
        list_add_front(&rev_list, prev.value);
    }
    return rev_list;
}

bool check_value(unsigned char *str, size_t size) {
    for (size_t i = 0; i < size; i++) {
        switch (str[i]) {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                continue;
            default:
                return false;
        }
    }
    return true;
}

struct maybe_int64 maybe_read_int64() {
    unsigned char str[12];
    printf("Введите значение, которое будет добавлено в связный список\n");
    fgets(str, sizeof(str), stdin);
    if(str[0] == '\n')
        return none_int64;
    if (check_value(str, strlen(str) - 1) == false)
        return none_int64;
    return some_int64(atoi(str));
}

inline static struct list **opt_list_add_back(struct list **list, int64_t value) {
    for (; *list != NULL; list = &(*list)->next);
    *list = node_create(value);
    return list;
}

struct list *list_read() {
    struct maybe_int64 i;
    struct list *list = {0};
    struct list **pList = &list;
    i = maybe_read_int64();
    while (i.valid == true) {
        pList = opt_list_add_back(pList, i.value);
        i = maybe_read_int64();
    }
    return list;
}

int main() {
    struct maybe_int64 i;
    struct list *result = {0}, *rev_list;
    result = list_read();
    printf("Длина односвязного списка: %zu\n", list_length(result));
    printf("Введите значение, которое будет добавлено в связный список\n");
    list_add_back(&result, read_int64());
    list_last(result);
    printf("Введите значение, которое будет добавлено в начало списка\n");
    list_add_front(&result, read_int64());
    list_last(result);
    printf("Введите индекс: \n");
    i = list_at(result,  read_int64() % list_length(result));
    if(i.valid)
        printf("Значение по данному индексу: %zu\n", i.value);
    else
        printf("Значение по данному индексу не найдено\n");
    printf("Сумма элементов односвязного списка: %zu\n", list_sum(result));
    rev_list = list_reverse(result);
    printf("Длина обратного односвязного списка: %zu\n", list_length(rev_list));
    list_last(rev_list);
    list_destroy(result);
    printf("Работа программы завершена\n");
    return 0;
}
