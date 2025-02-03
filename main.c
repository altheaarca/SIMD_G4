// Group 4 : Arca, Co Chiong, Uy [S11]
#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include <time.h>
#include "kernel.h"

extern void x86(int n, double* x, double* y);
extern void stencil_1D_xmm_SIMD(int n, double* X, double* Y);
extern void stencil_1D_ymm_SIMD(int n, double* X, double* Y);

int main() {
    int vLength =  1 << 20;//change to lower values for checking 
    int i, run, num_runs;
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
    initialize_vector(X, vLength);
    //display_initialized(X, vLength); //for checking

    // Time measurement for C version
    start = clock();
    compute_kernel(X, Y, vLength);
    end = clock();
    time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken for compute_kernel: %g seconds\n", time);
    display_vector(Y, vLength);
    compute_kernel(X, Y, vLength);
    memcpy(answer, Y, vLength * sizeof(double));

    // Non-SIMD Assembly Kernel
    printf("\n[Running Non-SIMD Assembly Kernel]\n");
    time = 0.0;
    num_runs = 30;
    for ( run = 0; run < num_runs; run++) {
        start = clock();
        x86(vLength, X, Y);
        end = clock();
        time += ((double)(end - start)) / CLOCKS_PER_SEC;
    }
    printf("Time taken for NON-SIMD: %g seconds\n", time);
    // SIMD XMM kernel
    printf("\n[Running SIMD Assembly Kernel XMM Register]\n");
    time = 0.0;
    num_runs = 30;
    for ( run = 0; run < num_runs; run++) {
        start = clock();
        stencil_1D_xmm_SIMD(vLength, X, Y);
        end = clock();
        time += ((double)(end - start)) / CLOCKS_PER_SEC;
    }
    printf("Time taken for SIMD XMM: %g seconds\n", time);

    // SIMD YMM Kernel
    printf("\n[Running SIMD Assembly Kernel YMM Register]\n");
    time = 0.0;
    num_runs = 30;
    for ( run = 0; run < num_runs; run++) {
        start = clock();
        stencil_1D_ymm_SIMD(vLength, X, Y);
        end = clock();
        time += ((double)(end - start)) / CLOCKS_PER_SEC;
    }
    printf("Time taken for SIMD YMM: %g seconds\n", time);

    // Run and display results for assembly kernels
    memcpy(Y, answer, vLength * sizeof(double)); // Restore reference values before running next test
    printf("\n[Running Non-SIMD Assembly Kernel]\n");
    x86(vLength, X, Y);
    //display_vector(Y, vLength);
    if (compare_vectors(Y, answer, vLength, 1e-6)) {
        printf("Non-SIMD assembly kernel result matches C reference!\n");
    }
    else {
        printf("Non-SIMD assembly kernel result does not match C reference.\n");
    }
    memcpy(Y, answer, vLength * sizeof(double)); // Restore reference values before running next test

    printf("\n[Running SIMD Assembly Kernel XMM Register ]\n");
    stencil_1D_xmm_SIMD(vLength, X, Y);
    display_vector(Y, vLength);
    if (compare_vectors(Y, answer, vLength, 1e-6)) {
        printf("SIMD XMM assembly kernel result matches C reference!\n");
    }
    else {
        printf("SIMD XMM assembly kernel result does not match C reference.\n");
    }
    memcpy(Y, answer, vLength * sizeof(double)); // Restore reference values before running next test

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
