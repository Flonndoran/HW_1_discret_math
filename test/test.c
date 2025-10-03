#include "../include/perms.h"
#include <stdio.h>
#include <assert.h>

void test_empty_set() {
    printf("Testing empty set (n=0)... ");
    
    iterator_t iter;
    iterator_init(&iter, 0);
    
    const permutation_t *current = iterator_value(&iter);
    assert(current->size == 0);
    assert(!iterator_has_next(&iter));
    
    iterator_destroy(&iter);
    printf("PASSED\n");
}

void test_single_element() {
    printf("Testing single element (n=1)... ");
    
    iterator_t iter;
    iterator_init(&iter, 1);
    
    size_t count = 0;
    do {
        const permutation_t *current = iterator_value(&iter);
        
        if (count == 0) assert(current->size == 0);
        else if (count == 1) assert(current->size == 1 && current->elements[0] == 0);
        
        count++;
        
        if (iterator_has_next(&iter)) {
            iterator_next(&iter);
        } else {
            break;
        }
    } while (1);
    
    assert(count == 2);
    iterator_destroy(&iter);
    printf("PASSED\n");
}

void test_three_elements() {
    printf("Testing three elements (n=3)... ");
    
    iterator_t iter;
    iterator_init(&iter, 3);
    
    unsigned expected[8][3] = {{}, {0}, {1}, {0,1}, {2}, {0,2}, {1,2}, {0,1,2}};
    size_t expected_sizes[8] = {0, 1, 1, 2, 1, 2, 2, 3};
    
    size_t count = 0;
    do {
        const permutation_t *current = iterator_value(&iter);
        
        assert(current->size == expected_sizes[count]);
        
        for (size_t i = 0; i < current->size; i++) {
            assert(current->elements[i] == expected[count][i]);
        }
        
        count++;
        
        if (iterator_has_next(&iter)) {
            iterator_next(&iter);
        } else {
            break;
        }
    } while (1);
    
    assert(count == 8);
    iterator_destroy(&iter);
    printf("PASSED\n");
}

void test_output_format() {
    printf("Testing output format... ");
    
    iterator_t iter;
    iterator_init(&iter, 2);
    
    // Проверяем что первое подмножество - пустое
    const permutation_t *current = iterator_value(&iter);
    assert(current->size == 0);
    
    iterator_destroy(&iter);
    printf("PASSED\n");
}

int main() {
    printf("Running permutation iterator tests...\n\n");
    
    test_empty_set();
    test_single_element();
    test_three_elements();
    test_output_format();
    
    printf("\nAll tests passed successfully!\n");
    return 0;
}