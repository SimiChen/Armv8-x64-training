section .data
    msg db "hw", 0Ah;

section .text
    global _start

_start:
    mov rax, 1
    mov rdi, 1
    mov rsi, msg
    mov rdx, 3
    syscall

    mov rax, 60
    xor rdi, rdi
    syscall