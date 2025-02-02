#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "kernel.h"

// External functions
extern void x86(double* x, double* y, int n);
extern void stencil_1D_xmm_SIMD(int n, double* X, double* Y);
extern void stencil_1D_ymm_SIMD(int n, double* X, double* Y);

// Function prototypes (for clarity)
void compute_kernel(double* X, double* Y, int n);
void display_vector(double* Y, int n);

int main() {
    int vLength, i;

    // TIMER VARIABLES
    double pcFreq; // Counter frequency (timer resolution)
    __int64 counterStart; // Timer value
    LARGE_INTEGER li; // Large integer for timer value
    double time_taken; // Time taken in seconds
    double average_time = 0; // Average time
    int retcode; // Return code

    // Get frequency of counter
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

    // Memory allocation (Double precision)
    double* X = (double*)malloc(vLength * sizeof(double));
    double* Y = (double*)malloc(vLength * sizeof(double));
    double* answer = (double*)malloc(vLength * sizeof(double));

    // Check for memory allocation failure
    if (!X || !Y || !answer) {
        printf("Memory allocation failed.\n");
        free(X);
        free(Y);
        free(answer);
        return 1;
    }

    // Array initialization (randomizing input values)
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

    // Start timer
    QueryPerformanceCounter(&li);
    counterStart = li.QuadPart;

    // Perform operations on the vector
    compute_kernel(X, Y, vLength);

    // End timer and calculate time taken
    QueryPerformanceCounter(&li);
    time_taken = (double)(li.QuadPart - counterStart) / pcFreq;
    printf("Time taken for compute_kernel: %lf seconds\n", time_taken);
    average_time += time_taken;

    // Display result after compute_kernel
    display_vector(Y, vLength);

    // Run and display results for assembly kernels
    printf("\n[Running Non-SIMD Assembly Kernel]\n");
    x86(X, Y, vLength);
    display_vector(Y, vLength);

    printf("\n[Running SIMD Assembly Kernel XMM Register ]\n");
    stencil_1D_xmm_SIMD(vLength, X, Y);
    display_vector(Y, vLength);

    printf("\n[Running SIMD Assembly Kernel YMM Register]\n");
    stencil_1D_ymm_SIMD(vLength, X, Y);
    display_vector(Y, vLength);

    // Free allocated memory
    free(X);
    free(Y);
    free(answer);

    return 0;
}
