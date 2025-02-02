#ifndef KERNEL_H
#define KERNEL_H

void compute_kernel(double* X, double* Y, int n);
void display_vector(double* Y, int n);
//for initializing 
void initialize_vector(double* X, int n);
void display_initialized(double* X, int n);
// for checking 
int compare_vectors(double* vec1, double* vec2, int n, double tolerance);
#endif  