#include "kernel.h"
#include <stdio.h>
#include <stdlib.h>
#include<math.h>
void compute_kernel(double* X, double* Y, int n) {
    int i;
    for (i = 3; i < n; i++) {
        Y[i] = (X[i - 3] + X[i - 2] + X[i - 1]) + X[i] + (X[i + 1] + X[i + 2] + X[i + 3]);
    }
}

void display_vector(double* Y, int n) {
    int i;

    printf("First 10 elements of Y:\n");
    for (i = 3; i < (n - 3 < 13 ? n - 3 : 13); i++) {
        printf("%.2f ", Y[i]);
    }
    printf("\n");

    if (n - 3 > 13) {
        printf("Last 10 elements of Y:\n");
        for (i = (n - 10 - 3 < 3 ? 3 : n - 10 - 3); i < n - 3; i++) {
            printf("%.2f ", Y[i]);
        }
        printf("\n");
    }
}
//----------for initializing----------//
void initialize_vector(double* X, int n) {
    int i; 
    for ( i = 0; i < n; i++) {
        X[i] = (double)(rand() % 10);  // random values as elements 
    }
}
void display_initialized(double* X, int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%g ",X[i]);  // random values as elements 
    }
}
//-----------for checking-------------// 
// 
// Comparison function for vectors with a tolerance
int compare_vectors(double* vec1, double* vec2, int n, double tolerance) {
    for (int i = 0; i < n; i++) {
        if (fabs(vec1[i] - vec2[i]) > tolerance) {
            return 0; // Return false if any element differs by more than the tolerance
        }
    }
    return 1; // Return true if all elements are within the tolerance
}