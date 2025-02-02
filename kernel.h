#ifndef KERNEL_H
#define KERNEL_H

void compute_kernel(double* X, double* Y, int n);
void display_vector(double* Y, int n);
// for checking 
int compare_vectors(double* vec1, double* vec2, int n, double tolerance);
#endif  