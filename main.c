#include "include/perms.h"
#include <stdio.h>

int main() {
    unsigned n;
    printf("Enter n: ");
    scanf("%u", &n);
    
    iterator_t iter;
    iterator_init(&iter, n);
    
    do {
        const permutation_t *current = iterator_value(&iter);
        
        printf("{");
        for (size_t i = 0; i < current->size; i++) {
            printf("%u", current->elements[i]);
            if (i < current->size - 1) printf(", ");
        }
        printf("}\n");
        
        if (iterator_has_next(&iter)) {
            iterator_next(&iter);
        } else {
            break;
        }
    } while (1);
    
    iterator_destroy(&iter);
    return 0;
}