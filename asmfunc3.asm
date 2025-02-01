;;Group 4 : Arca, Co Chiong, Uy [S11]
; SIMD x86 assembly language using XMM register
section .text
bits 64
default rel

global stencil_1D_ymm_SIMD

stencil_1D_ymm_SIMD:
    ; RCX = n (vector length)
    ; RDX = pointer to X (input vector)
    ; R8  = pointer to Y (output vector)

    shr rcx, 2               ;YMM (256)/double prec float (64) == 4 elements will be processed at the same time
    sub rcx, 1               
    add rdx, 24              ; Start from index 3 (8 bytes * 3 = 24 bytes offset)

stencil:
    
    vmovupd ymm1, [rdx - 24]  ; ymm1 = X[i-3]
    vmovupd ymm2, [rdx - 16]  ; ymm2 = X[i-2]
    vmovupd ymm3, [rdx - 8]   ; ymm3 = X[i-1]
    vmovupd ymm4, [rdx]       ; ymm4 = X[i]
    vmovupd ymm5, [rdx + 8]   ; ymm5 = X[i+1]
    vmovupd ymm6, [rdx + 16]  ; ymm6 = X[i+2]
    vmovupd ymm7, [rdx + 24]  ; ymm7 = X[i+3]

    vaddpd ymm1, ymm1, ymm2   ; ymm1 --- X[i-3] + X[i-2]
    vaddpd ymm1, ymm1, ymm3   ; ymm1 --- prev ymm1 + X[i-1]
    vaddpd ymm1, ymm1, ymm4   ; ymm1 --- prev ymm1 + X[i]
    vaddpd ymm1, ymm1, ymm5   ; ymm1 --- prev ymm1 + X[i+1]
    vaddpd ymm1, ymm1, ymm6   ; ymm1 --- prev ymm1 + X[i+2]
    vaddpd ymm1, ymm1, ymm7   ; ymm1 --- prev ymm1 + X[i+3]

    vmovupd [rdx], ymm1 ; Store result

    ; Move to next 4 elements (4 * 8 bytes)
    add rdx, 32   
    add r8, 32    

    loop stencil    

    ret