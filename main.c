// Group 4 : Arca, Co Chiong, Uy [S11]
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "kernel.h"
int main() {
    int vLength = 8; //TODO:  replace : 1 << 20 
    int i;
    double time;
    clock_t start, end;
    double* answer = (double*)malloc(vLength * sizeof(double));

    if (!answer) {
        printf("Memory allocation for answer failed.\n");
        return 1;
    }

    // Memory allocation for vectors X and Y
    double* X = (double*)malloc(vLength * sizeof(double));
    double* Y = (double*)malloc(vLength * sizeof(double));
    if (!X || !Y) {
        printf("Memory allocation failed.\n");
        free(X);
        free(Y);
        free(answer);
        return 1;
    }

    // Array initialization
    printf("Enter %d elements for vector X:\n", vLength);
    for (i = 0; i < vLength; i++) {
        if (scanf_s("%lf", &X[i]) != 1) {
            printf("Invalid input.\n");
            free(X);
            free(Y);
            free(answer);
            return 1;
        }
    }

    // Time measurement for C version
    start = clock();
    compute_kernel(X, Y, vLength);
    end = clock();
    time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken for compute_kernel: %g seconds\n", time);
    display_vector(Y, vLength);

    // Non-SIMD Assembly Kernel
    printf("\n[Running Non-SIMD Assembly Kernel]\n");
    start = clock();
    x86(vLength, X, Y);
    end = clock();
    time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken for x86 (Non-SIMD): %.6lf seconds\n", time);
    display_vector(Y, vLength);

    // SIMD XMM Kernel
    printf("\n[Running SIMD Assembly Kernel XMM Register]\n");
    start = clock();
    stencil_1D_xmm_SIMD(vLength, X, Y);
    end = clock();
    time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken for SIMD XMM: %.6lf seconds\n", time);
    display_vector(Y, vLength);

    // SIMD YMM Kernel
    printf("\n[Running SIMD Assembly Kernel YMM Register]\n");
    start = clock();
    stencil_1D_ymm_SIMD(vLength, X, Y);
    end = clock();
    time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken for SIMD YMM: %.6lf seconds\n", time);
    display_vector(Y, vLength);

    // Run and display results for assembly kernels
    printf("\n[Running Non-SIMD Assembly Kernel]\n");
    x86(vLength, X, Y);
    display_vector(Y, vLength);
    if (compare_vectors(Y, answer, vLength, 1e-6)) {
        printf("Non-SIMD assembly kernel result matches C reference!\n");
    }
    else {
        printf("Non-SIMD assembly kernel result does not match C reference.\n");
    }

    printf("\n[Running SIMD Assembly Kernel XMM Register ]\n");
    stencil_1D_xmm_SIMD(vLength, X, Y);
    display_vector(Y, vLength);
    if (compare_vectors(Y, answer, vLength, 1e-6)) {
        printf("SIMD XMM assembly kernel result matches C reference!\n");
    }
    else {
        printf("SIMD XMM assembly kernel result does not match C reference.\n");
    }

    printf("\n[Running SIMD Assembly Kernel YMM Register]\n");
    stencil_1D_ymm_SIMD(vLength, X, Y);
    display_vector(Y, vLength);
    if (compare_vectors(Y, answer, vLength, 1e-6)) {
        printf("SIMD YMM assembly kernel result matches C reference!\n");
    }
    else {
        printf("SIMD YMM assembly kernel result does not match C reference.\n");
    }

    // Free allocated memory
    //free(X);
    free(Y);
    //free(answer);

    return 0;
}
