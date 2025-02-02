#include "kernel.h"
#include <stdio.h>

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