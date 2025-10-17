#include <stdio.h>
#include <math.h>
#include "recurrent.h"

void find_roots(double a, double b, Roots *roots) {
    double discriminant = a*a + 4*b;
    
    if (discriminant > 0) {
        roots->type = 1; // two distinct real roots
        roots->r1 = (a + sqrt(discriminant)) / 2;
        roots->r2 = (a - sqrt(discriminant)) / 2;
    } else if (discriminant == 0) {
        roots->type = 2; // one repeated real root
        roots->r1 = a / 2;
        roots->r2 = a / 2;
    } else {
        roots->type = 3; // two complex roots
        roots->r1 = a / 2; // real part
        roots->r2 = sqrt(-discriminant) / 2; // imaginary part
    }
}

void find_coefficients(const Roots *roots, double c, double d, RecurrentFormula *formula) {
    formula->type = roots->type;
    formula->r1 = roots->r1;
    formula->r2 = roots->r2;
    
    if (roots->type == 1) {
        // Two distinct real roots
        formula->A = (c * roots->r2 - d) / (roots->r1 * (roots->r2 - roots->r1));
        formula->B = (d - c * roots->r1) / (roots->r2 * (roots->r2 - roots->r1));
    } else if (roots->type == 2) {
        // One repeated root
        formula->A = c / roots->r1;
        formula->B = (d / (roots->r1 * roots->r1) - c / roots->r1) / roots->r1;
    } else {
        // For complex roots, coefficients are not calculated in this version
        formula->A = 0;
        formula->B = 0;
    }
}

double calculate_nth_term(const RecurrentFormula *formula, int n) {
    if (formula->type == 1) {
        return formula->A * pow(formula->r1, n) + formula->B * pow(formula->r2, n);
    } else if (formula->type == 2) {
        return (formula->A + formula->B * n) * pow(formula->r1, n);
    } else {
        return 0;
    }
}

void print_formula(const RecurrentFormula *formula) {
    printf("Formula for the n-th term:\n");
    
    if (formula->type == 1) {
        printf("x_n = %.6f * (%.6f)^n + %.6f * (%.6f)^n\n", 
               formula->A, formula->r1, formula->B, formula->r2);
    } else if (formula->type == 2) {
        printf("x_n = (%.6f + %.6f * n) * (%.6f)^n\n", 
               formula->A, formula->B, formula->r1);
    } else {
        double modulus = sqrt(formula->r1 * formula->r1 + formula->r2 * formula->r2);
        double argument = atan2(formula->r2, formula->r1);
        printf("x_n = R * %.6f^n * cos(%.6f * n + phi)\n", modulus, argument);
    }
}