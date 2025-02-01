; Group 4: Arca, Co Chiong, Uy [S11]
; Non-SIMD x86-64 assembly language

section .data
Text1 db "X1: %d", 10, 0

section .text
bits 64
default rel

global x86
extern printf

x86:
; Function prologue
    push rbp
    mov rbp, rsp

    ; n - number of elements in vector
    ; rbx - address of X (double* X)
    ; rcx - address of Y (double* Y)
    mov rsi, rdx   ; rdx (n) -> rsi (vector length)
    mov rbx, r8    ; r8 (X) -> rbx (address of X)
    mov rcx, r9    ; r9 (Y) -> rcx (address of Y)

    ; index for the loop
    xor r8, r8     ; r8 = 0 (loop index i)
    xor r9, r9     ; r9 = 0 (index for Y)

loop_start:
    ; When the index i is less than 3, skip
    cmp r8, 3
    jl increment

    ; Check if there are fewer than 3 elements left in the range (handle boundary)
    mov rdx, rsi
    sub rdx, 3
    cmp r8, rdx
    jge end_loop

    ; Calculate Y[i] = X[i-3] + X[i-2] + X[i-1] + X[i] + X[i+1] + X[i+2] + X[i+3]
    ; Load X[i-3] (index = r8-3), X[i-2], X[i-1], X[i], X[i+1], X[i+2], X[i+3]
    ; Offset by 8 bytes per double
    movsd xmm0, [rbx + 8*(r8-3)]  ; X[i-3]
    movsd xmm1, [rbx + 8*(r8-2)]  ; X[i-2]
    movsd xmm2, [rbx + 8*(r8-1)]  ; X[i-1]
    movsd xmm3, [rbx + 8*r8]      ; X[i]
    movsd xmm4, [rbx + 8*(r8+1)]  ; X[i+1]
    movsd xmm5, [rbx + 8*(r8+2)]  ; X[i+2]
    movsd xmm6, [rbx + 8*(r8+3)]  ; X[i+3]

    ; Add all the values
    addsd xmm0, xmm1
    addsd xmm0, xmm2
    addsd xmm0, xmm3
    addsd xmm0, xmm4
    addsd xmm0, xmm5
    addsd xmm0, xmm6

    ; Store the result in Y[i]
    movsd [rcx + 8*r9], xmm0

    ; Increment Y index
    inc r9

increment:
    ; Increment loop index
    inc r8
    jmp loop_start

end_loop:
    ; Function epilogue
    mov rsp, rbp
    pop rbp
    ret
