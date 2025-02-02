section .text
bits 64
default rel

global x86
extern printf

x86:
; Function prologue
    push rbp
    mov rbp, rsp

    ; n - number of digits 
    ; rbx address of x
    ; rcx address of y
    mov rsi, rcx   ; rcx (n) to rsi
    mov rbx, rdx   ; rdx (x) to rbx
    mov rcx, r8   ; r8 (y) to rcx

    ; index of loop
    xor r8, r8
    ; index of y
    xor r9, r9

loop:
    ; rdx is reusable
    ; When it is less than 3 jump to increment
    cmp r8, 3
    jle increment

    ; When there is less than 3 number left jump to end
    mov rdx, rsi
    sub rdx, 3
    cmp r8, rdx
    jge end

    ; add all the float value
    fld qword [rbx+ 8*r8]
    fld qword [rbx+ 8*r8 - 8*1]
    fld qword [rbx+ 8*r8 - 8*2]
    fld qword [rbx + 8*r8 - 8*3]
    xor rdx, rdx
    call addAll
    fld qword [rbx + 8*r8 + 8*1]
    fld qword [rbx+ 8*r8 + 8*2]
    fld qword [rbx + 8*r8 + 8*3]
    xor rdx, rdx
    call addAll

    ; store to the address of y and increment
    fstp qword [rcx + 8*r9]
    inc r9
    jmp increment

increment:
    ; increment the loop
    inc r8
    jmp loop

end:
    ; Function epilogue
    mov rsp, rbp
    pop rbp
    ret

addAll:
    fadd
    inc rdx
    cmp rdx, 3
    jne addAll
    ret