#include <stdio.h>
#ifndef RECURRENT_H
#define RECURRENT_H

typedef struct {
    double r1;
    double r2;
    int type;
} Roots;

typedef struct {
    double A;
    double B;
    double r1;
    double r2;
    int type;
} RecurrentFormula;

// Function declarations
void find_roots(double a, double b, Roots *roots);
void find_coefficients(const Roots *roots, double c, double d, RecurrentFormula *formula);
double calculate_nth_term(const RecurrentFormula *formula, int n);
void print_formula(const RecurrentFormula *formula);

#endif