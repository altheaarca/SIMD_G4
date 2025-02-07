# 1D Stencil Operation using SIMD x86 Assembly
## 👨‍💻 Authors: Arca, Co Chiong, Uy
# PROJECT SPECS:
![image](https://github.com/user-attachments/assets/665418fb-a487-4d2c-8493-9f0ca4ef8e63)
![image](https://github.com/user-attachments/assets/aa6de12d-5e95-4674-b868-6ed3cbdcd483)
### Based on the Given specifications, this project implements a 1D-stencil operation on a vector using:
- C (Baseline Implementation)
- x86-64 Assembly (Non-SIMD)
- x86 SIMD Assembly with XMM Registers (128-bit AVX)
- x86 SIMD Assembly with YMM Registers (256-bit AVX2)
### Our goal is to compare execution times and demonstrate performance improvements using SIMD (Single Instruction, Multiple Data).
## [INPUT] 
- length of the vector (integer) variable used vLength 
- Vectors X and Y (double-precision float) 
## Stencil Operation Formula
### Y[i]=X[i−3]+X[i−2]+X[i−1]+X[i]+X[i+1]+X[i+2]+X[i+3]
## [EXPECTED OUTPUT] 
- Result stored in Y
- Diplay first 10 elements of Y
- Display last 10 elements of Y
# RESULT 
### [Screenshots] 
![image](https://github.com/user-attachments/assets/06ef9c58-cc39-4c96-aad7-8b378b074ec7)
![image](https://github.com/user-attachments/assets/95c23445-4332-4f11-a5a8-c746bbe64098)

### [Performance Comparison Table] 
| Array Size    | Method        | Time | 
|     :---:     | :---:         | :---:         |
| 2^20          | C             | 0.011 seconds |   
|               | Non-SIMD      | 0.375 seconds |                       
|               | SIMD XMM      | 0.21  seconds |               
|               | SIMD YMM      | 0.234 seconds |                  
| 2^26          | C             | 0.43 seconds  |
|               | Non-SIMD      |18.405 seconds |               
|               | SIMD XMM      |  12.174 seconds |                 
|               | SIMD YMM      | 8.862  seconds |                    
| 2^30          | C             |  seconds |                  
|               | Non-SIMD      |  seconds |                    
|               | SIMD XMM      |  seconds |                    
|               | SIMD YMM      |  seconds |                  
#### observations


