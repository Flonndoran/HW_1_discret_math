#include "../include/iterator.h"

void iterator_init(iterator_t *i, unsigned n) {
    if (!i) return;

    i->value.n = n;
    i->value.mask = 0ULL;
    i->state = 0ULL;
    
    // Безопасное вычисление 2^n
    if (n == 0) {
        i->total = 1ULL;
    } else if (n < 64) {
        i->total = 1ULL << n;
    } else {
        // Для n >= 64 устанавливаем максимальное значение
        i->total = UINT64_MAX;
    }
}

const set_t *iterator_value(const iterator_t *i) {
    if (!i) return NULL;
    return &i->value;
}

int iterator_has_next(const iterator_t *i) {
    if (!i) return 0;
    return i->state < i->total;
}

void iterator_next(iterator_t *i) {
    if (!i || !iterator_has_next(i)) return;
    
    i->value.mask = i->state;
    i->state++;
}

void iterator_destroy(iterator_t *i) {
    // Просто освобождаем память, если была выделена
    free(i);
}