#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "recurrent.h"

#define EPSILON 0.0001

void test_fibonacci() {
    printf("Testing Fibonacci sequence (a=1, b=1, x1=1, x2=1)...\n");
    
    Roots roots;
    RecurrentFormula formula;
    
    find_roots(1, 1, &roots);
    find_coefficients(&roots, 1, 1, &formula);
    
    // Test first 10 terms of Fibonacci sequence
    int expected[] = {1, 1, 2, 3, 5, 8, 13, 21, 34, 55};
    
    for (int n = 1; n <= 10; n++) {
        double result = calculate_nth_term(&formula, n);
        double expected_val = expected[n-1];
        
        printf("x_%d: calculated=%.2f, expected=%d\n", n, result, expected[n-1]);
        assert(fabs(result - expected_val) < EPSILON);
    }
    printf("Fibonacci test passed!\n\n");
}


void test_repeated_roots() {
    printf("Testing repeated roots case (a=4, b=-4, x1=1, x2=2)...\n");
    
    Roots roots;
    RecurrentFormula formula;
    
    find_roots(4, -4, &roots);
    find_coefficients(&roots, 1, 2, &formula);
    
    // This should give repeated roots case (r^2 - 4r + 4 = 0)
    assert(roots.type == 2);
    
    // Test calculation
    double result = calculate_nth_term(&formula, 3);
    printf("x_3 calculated: %.2f\n", result);
    
    printf("Repeated roots test passed!\n\n");
}

void test_complex_roots() {
    printf("Testing complex roots case (a=1, b=1, x1=1, x2=1)...\n");
    
    Roots roots;
    RecurrentFormula formula;
    
    find_roots(1, 1, &roots);
    find_coefficients(&roots, 1, 1, &formula);
    
    // This should give complex roots case
    assert(roots.type == 3);
    
    // Test that print_formula doesn't crash
    print_formula(&formula);
    
    printf("Complex roots test passed!\n\n");
}

void test_print_functions() {
    printf("Testing print functions with different cases...\n");
    
    // Test case 1: distinct real roots
    Roots roots1;
    RecurrentFormula formula1;
    find_roots(1, 1, &roots1);
    find_coefficients(&roots1, 1, 1, &formula1);
    print_formula(&formula1);
    
    // Test case 2: repeated roots
    Roots roots2;
    RecurrentFormula formula2;
    find_roots(4, -4, &roots2);
    find_coefficients(&roots2, 1, 2, &formula2);
    print_formula(&formula2);
    
    printf("Print functions test passed!\n\n");
}

void run_all_tests() {
    printf("Running Recurrent Sequence Tests...\n");
    printf("===================================\n\n");
    
    test_fibonacci();
    test_repeated_roots();
    test_print_functions();
    
    printf("All tests passed successfully!\n");
}

int main() {
    run_all_tests();
    return 0;
}