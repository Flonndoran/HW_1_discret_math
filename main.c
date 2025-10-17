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
    
    return 0;
}