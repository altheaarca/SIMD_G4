//Group 4 : Arca, Co Chiong, Uy [S11]
// NON - SIMD assembly language
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "kernel.h"

//TODO: Fix warnings. Function Definition for these three are not found.
extern void x86(int n,double* x, double* y);
extern void stencil_1D_xmm_SIMD(int n, double* X, double* Y);
extern void stencil_1D_ymm_SIMD(int n, double* X, double* Y);

int main() {
    int vLength, i;
    double pcFreq;          // Counter frequency 
    __int64 counterStart;   // Timer value
    LARGE_INTEGER li;       // Large integer for timer value
    double time_taken;      // Time taken in seconds
    double average_time = 0;// Average time
    int retcode;            // Return code

    // frequency of counter
    retcode = QueryPerformanceFrequency(&li);
    if (retcode == 0)
        printf("ERROR: QueryPerformanceFrequency() failed\n");
    pcFreq = li.QuadPart;

    // Get the vector length
    printf("Enter the length of vector X: ");
    if (scanf_s("%d", &vLength) != 1 || vLength < 4) {
        printf("Invalid input. Vector length must be at least 4.\n");
        return 1;
    }
    // double precision memory alloc
    double* X = (double*)malloc(vLength * sizeof(double));
    double* Y = (double*)malloc(vLength * sizeof(double));
    double* answer = (double*)malloc(vLength * sizeof(double));
    if (!X || !Y || !answer) {
        printf("Memory allocation failed.\n");
        free(X);
        free(Y);
        free(answer);
        return 1;
    }
    // X elements 
    printf("Enter %d elements for vector X:\n", vLength);
    for (i = 0; i < vLength; i++) {
        if (scanf_s("%lf", &X[i]) != 1) {
            printf("Invalid input. Please enter numeric values.\n");
            free(X);
            free(Y);
            free(answer);
            return 1;
        }
    }

    // C Version 
    compute_kernel(X, answer, vLength);
    QueryPerformanceCounter(&li); //start time 
    counterStart = li.QuadPart;
    compute_kernel(X, Y, vLength);
    QueryPerformanceCounter(&li); //end time
    time_taken = (double)(li.QuadPart - counterStart) / pcFreq;
    printf("Time taken for compute_kernel (C version): %lf seconds\n", time_taken);
    average_time = average_time + time_taken;
    // Display result after C kernel
    display_vector(Y, vLength);

    // Run and display results for assembly kernels
    printf("\n[Running Non-SIMD Assembly Kernel]\n");
    x86(X, Y, vLength);
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
    free(X);
    free(Y);
    free(answer);

    return 0;
}

