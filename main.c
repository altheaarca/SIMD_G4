#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "kernel.h"



int main() {
    int vLength, i;

    printf("Enter the length of vector X: ");
    if (scanf_s("%d", &vLength) != 1 || vLength < 4) {
        printf("Invalid input. Vector length must be at least 4.\n");
        return 1;
    }

    double* X = (double*)malloc(vLength * sizeof(double));
    double* Y = (double*)malloc(vLength * sizeof(double));

    if (!X || !Y) {
        printf("Memory allocation failed.\n");
        free(X);
        free(Y);
        return 1;
    }

    printf("Enter %d elements for vector X:\n", vLength);
    for (i = 0; i < vLength; i++) {
        if (scanf_s("%lf", &X[i]) != 1) {
            printf("Invalid input. Please enter numeric values.\n");
            free(X);
            free(Y);
            return 1;
        }
    }

    compute_kernel(X, Y, vLength);
    display_vector(Y, vLength);

    printf("\n[Running Non-SIMD Assembly Kernel]\n");
    x86(vLength, X, Y);
    display_vector(Y, vLength);
    printf("\n[Running SIMD Assembly Kernel XMM Register ]\n");
    stencil_1D_xmm_SIMD(vLength, X, Y);
    printf("\n[Running Non-SIMD Assembly Kernel YMM Register]\n");
    stencil_1D_ymm_SIMD(vLength, X, Y);

    free(X);
    free(Y);
    return 0;
}