#ifndef PERMS_H
#define PERMS_H

#include <stddef.h>
#include <stdbool.h>

typedef struct {
    unsigned *elements;
    size_t size;
    size_t capacity;
} permutation_t;

typedef struct {
    permutation_t current;
    unsigned n;
    size_t counter;
    bool finished;
} iterator_t;

void iterator_init(iterator_t *i, unsigned n);
const permutation_t *iterator_value(const iterator_t *i);
bool iterator_has_next(const iterator_t *i);
void iterator_next(iterator_t *i);
void iterator_destroy(iterator_t *i);

#endif