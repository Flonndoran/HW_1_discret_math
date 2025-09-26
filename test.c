#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "include/include.h"

int main() {

    printf("Test 1:\n");
    struct Relation empty = {NULL, 0};
    printf("Input: ");
    print_relation(&empty);
    struct Relation *result = join_binary(&empty, &empty);
    printf("Result: ");
    print_relation(result);
    assert(result != NULL);
    assert(result->size == 0);
    assert(result->pairs == NULL);
    free_relation(result);
    printf("Passed\n\n");
    

    printf("Test 2:\n");
    struct Pair r_pairs[] = {{1, 2}, {3, 4}};
    struct Pair s_pairs[] = {{5, 6}, {7, 8}};
    struct Relation r = {r_pairs, 2};
    struct Relation s = {s_pairs, 2};
    printf("R: ");
    print_relation(&r);
    printf("S: ");
    print_relation(&s);
    result = join_binary(&r, &s);
    printf("Result: ");
    print_relation(result);
    assert(result != NULL);
    assert(result->size == 0);
    free_relation(result);
    printf("Passed\n\n");
    
    printf("Test 3:\n");
    struct Pair r2_pairs[] = {{1, 2}, {2, 3}};
    struct Pair s2_pairs[] = {{2, 4}, {3, 5}};
    struct Relation r2 = {r2_pairs, 2};
    struct Relation s2 = {s2_pairs, 2};
    printf("R: ");
    print_relation(&r2);
    printf("S: ");
    print_relation(&s2);
    result = join_binary(&r2, &s2);
    printf("Result: ");
    print_relation(result);
    assert(result != NULL);
    assert(result->size == 2);
    int found1 = 0, found2 = 0;
    for (unsigned int i = 0; i < result->size; i++) {
        if (result->pairs[i].first == 1 && result->pairs[i].second == 4) found1 = 1;
        if (result->pairs[i].first == 2 && result->pairs[i].second == 5) found2 = 1;
    }
    assert(found1 == 1);
    assert(found2 == 1);
    free_relation(result);
    printf("Passed\n\n");
    
    printf("Test 4:\n");
    struct Pair r3_pairs[] = {{1, 2}, {1, 2}};
    struct Pair s3_pairs[] = {{2, 3}, {2, 3}};
    struct Relation r3 = {r3_pairs, 2};
    struct Relation s3 = {s3_pairs, 2};
    printf("R: ");
    print_relation(&r3);
    printf("S: ");
    print_relation(&s3);
    result = join_binary(&r3, &s3);
    printf("Result: ");
    print_relation(result);
    assert(result != NULL);
    assert(result->size == 1);
    assert(result->pairs[0].first == 1);
    assert(result->pairs[0].second == 3);
    free_relation(result);
    printf("Passed\n\n");
    
    printf("Test 5:\n");
    struct Pair r5_pairs[] = {{1, 2}, {2, 3}, {3, 4}};
    struct Pair s5_pairs[] = {{2, 5}, {3, 6}, {4, 7}};
    struct Relation r5 = {r5_pairs, 3};
    struct Relation s5 = {s5_pairs, 3};
    printf("R: ");
    print_relation(&r5);
    printf("S: ");
    print_relation(&s5);
    result = join_binary(&r5, &s5);
    printf("Result: ");
    print_relation(result);
    assert(result != NULL);
    assert(result->size == 3);
    struct Pair expected[] = {{1, 5}, {2, 6}, {3, 7}};
    for (int i = 0; i < 3; i++) {
        int found = 0;
        for (unsigned int j = 0; j < result->size; j++) {
            if (result->pairs[j].first == expected[i].first && 
                result->pairs[j].second == expected[i].second) {
                found = 1;
                break;
            }
        }
        assert(found == 1);
    }
    free_relation(result);
    printf("Passed\n\n");

    printf("Test 6:\n");
    struct Pair r4_pairs[] = {{1, 2}, {3, 4}};
    struct Pair s4_pairs[] = {{2, 5}, {4, 6}};
    struct Relation *r4 = create_relation(r4_pairs, 2);
    struct Relation *s4 = create_relation(s4_pairs, 2);
    printf("Created R: ");
    print_relation(r4);
    printf("Created S: ");
    print_relation(s4);
    result = join_binary(r4, s4);
    printf("Result R and S: ");
    print_relation(result);
    assert(result != NULL);
    assert(result->size == 2);
    free_relation(r4);
    free_relation(s4);
    free_relation(result);
    printf("Passed\n\n");
    
    printf("All tests passed!\n");
    return 0; 
}