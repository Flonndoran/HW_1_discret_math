#include <stdlib.h>
#include <stdio.h>
#include "../include/include.h"
#include "internal.h"

struct Relation *join_binary(struct Relation *r, struct Relation *s) {
    // Проверяем на NULL указатели
    if (r == NULL || s == NULL) {
        return NULL;
    }
    
    // 2 пустых
    if ((r->pairs == NULL || r->size == 0) && (s->pairs == NULL || s->size == 0)) {
        struct Relation *result = malloc(sizeof(struct Relation));
        if (result == NULL) {
            return NULL;
        }
        result->pairs = NULL;
        result->size = 0;
        return result;
    }
    
    // 1 пустое
    if (r->pairs == NULL || r->size == 0 || s->pairs == NULL || s->size == 0) {
        struct Relation *result = malloc(sizeof(struct Relation));
        if (result == NULL) {
            return NULL;
        }
        result->pairs = NULL;
        result->size = 0;
        return result;
    }

    unsigned int max_size = r->size * s->size;
    struct Pair *result_pairs = malloc(max_size * sizeof(struct Pair));
    if (result_pairs == NULL) {
        return NULL;
    }

    unsigned int result_size = 0;
    
    
    for (unsigned int i = 0; i < r->size; i++) {
        for (unsigned int j = 0; j < s->size; j++) {
            if (r->pairs[i].second == s->pairs[j].first) {
                struct Pair new_pair = {r->pairs[i].first, s->pairs[j].second};
                
                int duplicate = 0;
                for (unsigned int k = 0; k < result_size; k++) {
                    if (result_pairs[k].first == new_pair.first && 
                        result_pairs[k].second == new_pair.second) {
                        duplicate = 1;
                        break;
                    }
                }
                
                if (!duplicate) {
                    result_pairs[result_size] = new_pair;
                    result_size++;
                }
            }
        }
    }


    struct Relation *result = malloc(sizeof(struct Relation));
    if (result == NULL) {
        free(result_pairs);
        return NULL;
    }

    result->pairs = result_pairs;
    result->size = result_size;
    
    return result;
}

void free_relation(struct Relation *rel) {
    if (rel != NULL) {
        if (rel->pairs != NULL) {
            free(rel->pairs);
        }
        free(rel);
    }
}

struct Relation *create_relation(struct Pair *pairs, unsigned int size) {
    struct Relation *rel = malloc(sizeof(struct Relation));
    if (rel == NULL) {
        return NULL;
    }

    if (size > 0 && pairs != NULL) {
        rel->pairs = malloc(size * sizeof(struct Pair));
        if (rel->pairs == NULL) {
            free(rel);
            return NULL;
        }
        for (unsigned int i = 0; i < size; i++) {
            rel->pairs[i] = pairs[i];
        }
        rel->size = size;
    } else {
        rel->pairs = NULL;
        rel->size = 0;
    }

    return rel;
}

// Функция для печати отношения
void print_relation(struct Relation *rel) {
    if (rel == NULL) {
        printf("Relation: NULL\n");
        return;
    }
    
    printf("(size: %u): ", rel->size);
    
    if (rel->pairs == NULL || rel->size == 0) {
        printf("empty\n");
        return;
    }
    
    printf("{");
    for (unsigned int i = 0; i < rel->size; i++) {
        printf("(%d, %d)", rel->pairs[i].first, rel->pairs[i].second);
        if (i < rel->size - 1) {
            printf(", ");
        }
    }
    printf("}\n");
}
