/**
 * File: task_1.c -- estimates the time cost of memory management in C
 * 
 * Author: Desmond Frimpong
 * Project: 07
 * Date: April 30, 2026
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_ITERATIONS 10000

int main() {
    clock_t start, end;
    double cpu_time_used;

    // Small allocation (100 ints)
    start = clock();
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        int* arr = malloc(sizeof(int) * 100);
        free(arr);
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken for %d small allocations: %f seconds\n", NUM_ITERATIONS, cpu_time_used);

    // Medium allocation (10K ints)
    start = clock();
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        int* arr = malloc(sizeof(int) * 10000);
        free(arr);
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken for %d medium allocations: %f seconds\n", NUM_ITERATIONS, cpu_time_used);

    // Large allocation (1 million ints)
    start = clock();
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        int* arr = malloc(sizeof(int) * 1000000);
        free(arr);
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken for %d large allocations: %f seconds\n", NUM_ITERATIONS, cpu_time_used);

    return 0;
}