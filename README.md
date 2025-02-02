# 1D Stencil Operation using SIMD x86 Assembly
## 👨‍💻 Authors: Arca, Co Chiong, Uy
### This project implements a 1D stencil operation on a vector using:
- C (Baseline Implementation)
- x86-64 Assembly (Non-SIMD)
- x86 SIMD Assembly with XMM Registers (128-bit AVX)
- x86 SIMD Assembly with YMM Registers (256-bit AVX2)
### Our goal is to compare execution times and demonstrate performance improvements using SIMD (Single Instruction, Multiple Data).
## [INPUT] 
- length of the vector (integer)
- Vectors X and Y (double-precision float)
## Stencil Operation Formula
### Y[i]=X[i−3]+X[i−2]+X[i−1]+X[i]+X[i+1]+X[i+2]+X[i+3]
## [OUTPUT] 
- Result stored in Y
- Diplay first 10 elements of Y
- Display last 10 elements of Y
# RESULT 
### [Screenshots] 
- [Output] x86-64 Assembly (Non-SIMD)
- [Output] x86 SIMD Assembly with XMM Registers (128-bit AVX)
- [Output] x86 SIMD Assembly with YMM Registers (256-bit AVX2)
### [Performance Comparison Table] 
#### observations
### [Screenshots] 
- [Correctness] x86-64 Assembly (Non-SIMD)
- [Correctness] x86 SIMD Assembly with XMM Registers (128-bit AVX)
- [Correctness] x86 SIMD Assembly with YMM Registers (256-bit AVX2)



