<<<<<<< HEAD
#include <stdio.h>
#include "recurrent.h"

int main() {
    int a, b, c, d;
    
    printf("Enter coefficients a, b, c, d: ");
    scanf("%d %d %d %d", &a, &b, &c, &d);
    
    Roots roots;
    RecurrentFormula formula;
    
    find_roots(a, b, &roots);
    find_coefficients(&roots, c, d, &formula);
    
    if (roots.type == 1) {
        printf("Two distinct real roots:\n");
        printf("l1 = %.6f, l2 = %.6f\n", roots.r1, roots.r2);
    } else if (roots.type == 2) {
        printf("One repeated real root:\n");
        printf("l = %.6f\n", roots.r1);
    } else {
        printf("Two complex roots:\n");
        printf("l1,2 = %.6f ± %.6fi\n", roots.r1, roots.r2);
    }
    
    print_formula(&formula);
    
    printf("\n check: \n");
    for (int n = 1; n <= 5; n++) {
        double xn = calculate_nth_term(&formula, n);
        printf("x_%d = %.2f\n", n, xn);
    }
    
=======
#include "include/iterator.h"

void set_print(const set_t *s) {
    if (!s) return;
    
    printf("{ ");
    for (unsigned j = 0; j < s->n; j++) {
        if (s->mask & (1ULL << j)) {
            printf("%u ", j);
        }
    }
    printf("}");
}

int main() {
    unsigned n;

    printf("n: ");
    if (scanf("%u", &n) != 1) {
        printf("Ошибка ввода!\n");
        return 1;
    }

    if (n > 63) {
        printf("Предупреждение: n=%u слишком большое, будут показаны не все подмножества\n", n);
    }

    iterator_t *it = malloc(sizeof(iterator_t));
    if (!it) {
        printf("Ошибка: не удалось выделить память\n");
        return 1;
    }

    iterator_init(it, n);

    unsigned count = 0;
    while (iterator_has_next(it)) {
        iterator_next(it);
        const set_t *s = iterator_value(it);
        set_print(s);
        printf("\n");
        count++;
        
        // Ограничиваем вывод для больших n
        if (n > 10 && count == 10) {
            printf("... (показано первых 10 подмножеств)\n");
            break;
        }
    }

    printf("%d",count);
    iterator_destroy(it);
>>>>>>> 48c2ce7b71291195b58adb08b87cb46fdd22493c
    return 0;
}