#include "perms.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void permutation_init(permutation_t *p, size_t capacity) {
    p->elements = malloc(capacity * sizeof(unsigned));
    p->size = 0;
    p->capacity = capacity;
}

static void permutation_clear(permutation_t *p) {
    p->size = 0;
}

static void permutation_append(permutation_t *p, unsigned value) {
    if (p->size >= p->capacity) {
        p->capacity = p->capacity == 0 ? 8 : p->capacity * 2;
        p->elements = realloc(p->elements, p->capacity * sizeof(unsigned));
    }
    p->elements[p->size++] = value;
}

static void permutation_destroy(permutation_t *p) {
    free(p->elements);
    p->elements = NULL;
    p->size = p->capacity = 0;
}

static void generate_subset(iterator_t *iter, size_t mask) {
    permutation_clear(&iter->current);
    
    for (unsigned i = 0; i < iter->n; i++) {
        if (mask & (1ULL << i)) {
            permutation_append(&iter->current, i);
        }
    }
}

void iterator_init(iterator_t *i, unsigned n) {
    i->n = n;
    i->counter = 0;
    i->finished = false;
    
    permutation_init(&i->current, n > 0 ? n : 8);
    generate_subset(i, 0);
}

const permutation_t *iterator_value(const iterator_t *i) {
    return &i->current;
}

bool iterator_has_next(const iterator_t *i) {
    return !i->finished;
}

void iterator_next(iterator_t *i) {
    if (i->finished) return;
    
    i->counter++;
    
    if (i->counter >= (1ULL << i->n)) {
        i->finished = true;
        return;
    }
    
    generate_subset(i, i->counter);
}

void iterator_destroy(iterator_t *i) {
    permutation_destroy(&i->current);
}