//Group 4 : Arca, Co Chiong, Uy [S11]
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


extern void x86(int n, double* X, double* Y);
extern void stencil_1D_xmm_SIMD(int n, double* X, double* Y);
extern void stencil_1D_ymm_SIMD(int n, double* X, double* Y);



void compute_kernel(double* X, double* Y, int n) {
    int i;
    for (i = 3; i < n; i++) {
        Y[i] = (X[i - 3] + X[i - 2] + X[i - 1]) + X[i] + (X[i + 1] + X[i + 2] + X[i + 3]) ;
    }
}

// Displays the first and last 10 valid elements of Y
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

int main() {
    int vLength, i;
    double* X, * Y;

    printf("Enter the length of vector X: ");
    if (scanf_s("%d", &vLength) != 1 || vLength < 4) {
        printf("Invalid input. Vector length must be at least 4.\n");
        return 1;
    }

    X = (double*)malloc(vLength * sizeof(double));
    Y = (double*)malloc(vLength * sizeof(double));

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
    //x86(vLength, X, Y);
    printf("\n[Running SIMD Assembly Kernel XMM Register ]\n");
    //stencil_1D_xmm_SIMD(vLength, X, Y);
    printf("\n[Running Non-SIMD Assembly Kernel YMM Register]\n");
   // stencil_1D_ymm_SIMD(vLength, X, Y);
    

    free(X);
    free(Y);
    return 0;
}

