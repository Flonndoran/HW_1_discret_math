#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/iterator.h"

void test_init() {
    iterator_t *it = malloc(sizeof(iterator_t));
    assert(it != NULL);

    iterator_init(it, 3);

    assert(it->value.n == 3);
    assert(it->value.mask == 0);
    assert(it->state == 0);
    assert(it->total == (1ULL << 3));

    iterator_destroy(it);
    printf("test_init passed\n");
}

void test_iteration_count() {
    iterator_t *it = malloc(sizeof(iterator_t));
    assert(it != NULL);

    iterator_init(it, 2);

    unsigned count = 0;
    while (iterator_has_next(it)) {
        iterator_next(it);
        const set_t *s = iterator_value(it);
        assert(s != NULL);
        count++;
    }

    assert(count == (1U << 2));
    iterator_destroy(it);
    printf("test_iteration_count passed\n");
}

void test_masks_correctness() {
    iterator_t *it = malloc(sizeof(iterator_t));
    assert(it != NULL);

    iterator_init(it, 3);

    uint64_t expected_masks[] = {0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7};

    unsigned idx = 0;
    while (iterator_has_next(it)) {
        iterator_next(it);
        const set_t *s = iterator_value(it);
        assert(s->mask == expected_masks[idx]);
        idx++;
    }

    assert(idx == (1U << 3));
    iterator_destroy(it);
    printf("test_masks_correctness passed\n");
}

void test_destroy_function() {
    iterator_t *it = malloc(sizeof(iterator_t));
    assert(it != NULL);

    iterator_init(it, 4);
    iterator_destroy(it);
    printf("test_destroy_function passed\n");
}

void test_large_n_handling() {
    iterator_t *it = malloc(sizeof(iterator_t));
    assert(it != NULL);

    iterator_init(it, 64);
    assert(it->total == UINT64_MAX);
    iterator_destroy(it);
    printf("test_large_n_handling passed\n");
}

void test_null_safety() {
    iterator_init(NULL, 5);
    assert(iterator_value(NULL) == NULL);
    assert(iterator_has_next(NULL) == 0);
    iterator_next(NULL);
    iterator_destroy(NULL);
    printf("test_null_safety passed\n");
}

void test_empty_set() {
    iterator_t *it = malloc(sizeof(iterator_t));
    assert(it != NULL);

    iterator_init(it, 0);
    assert(it->total == 1ULL);
    
    assert(iterator_has_next(it) == 1);
    iterator_next(it);
    const set_t *s = iterator_value(it);
    assert(s->mask == 0);
    
    assert(iterator_has_next(it) == 0);
    iterator_destroy(it);
    printf("test_empty_set passed\n");
}

void test_single_element() {
    iterator_t *it = malloc(sizeof(iterator_t));
    assert(it != NULL);

    iterator_init(it, 1);
    
    assert(iterator_has_next(it) == 1);
    iterator_next(it);
    const set_t *s1 = iterator_value(it);
    assert(s1->mask == 0);
    
    assert(iterator_has_next(it) == 1);
    iterator_next(it);
    const set_t *s2 = iterator_value(it);
    assert(s2->mask == 1);
    
    assert(iterator_has_next(it) == 0);
    iterator_destroy(it);
    printf("test_single_element passed\n");
}

void run_all_tests() {
    printf("Running tests...\n\n");
    
    test_init();
    test_iteration_count();
    test_masks_correctness();
    test_destroy_function();
    test_large_n_handling();
    test_null_safety();
    test_empty_set();
    test_single_element();
    
    printf("\nAll tests passed!\n");
}

int main() {
    run_all_tests();
    return 0;
}