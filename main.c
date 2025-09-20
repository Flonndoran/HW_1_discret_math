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
    return 0;
}