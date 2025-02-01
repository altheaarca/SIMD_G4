;Group 4 : Arca, Co Chiong, Uy [S11]
; SIMD x86 assembly language using XMM register
section .text
bits 64
default rel

global stencil_1D_xmm_SIMD

stencil_1D_xmm_SIMD:
    ; RCX = n (vector length)
    ; RDX = pointer to X (input vector)
    ; R8  = pointer to Y (output vector)

    shr rcx, 1               ; XMM (128)/double prec float (64) == 4 elements will be processed at the same time
    sub rcx, 1               ; 
    add rdx, 24              ; Start from index 3 (8 bytes * 3 = 24 bytes offset)

stencil:
    
    vmovupd xmm1, [rdx - 24]  ; xmm1 = X[i-3], X[i-2]
    vmovupd xmm2, [rdx - 16]  ; xmm2 = X[i-1], X[i]
    vmovupd xmm3, [rdx - 8]   ; xmm3 = X[i+1], X[i+2]
    vmovupd xmm4, [rdx]       ; xmm4 = X[i+3], (next boundary)

    vaddpd xmm1, xmm1, xmm2   ; xmm1 = (X[i-3] + X[i-2]) + (X[i-1] + X[i])
    vaddpd xmm1, xmm1, xmm3   ; xmm1 = prev xmm1 + (X[i+1] + X[i+2])
    vaddpd xmm1, xmm1, xmm4   ; xmm1 = prev xmm1 + (X[i+3])

    vmovupd [rdx], xmm1       ; Store result in Y[i]

    ; Move to next 2 elements (2 * 8 bytes)
    add rdx, 16   
    add r8, 16    

    loop stencil    

    ret
