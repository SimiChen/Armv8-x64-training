section .data
    input_prompt db "Enter a 32-bit integer: ", 0
    result_msg db "Saturated 16-bit result: %d", 0xA, 0
    result_msg_len equ $ - result_msg

section .bss
    input resb 12   ; 32-bit input + null-terminator
    result resw 1

section .text
    global _start
    extern sature

_start:
    ; Display prompt and read 32-bit input
    mov rax, 0x1            ; syscall number for sys_write
    mov rdi, 0x1            ; file descriptor 1 (stdout)
    mov rsi, input_prompt   ; pointer to the prompt
    mov rdx, 26             ; length of the prompt
    syscall

    mov rax, 0              ; syscall number for sys_read
    mov rdi, 0              ; file descriptor 0 (stdin)
    mov rsi, input          ; pointer to the input buffer
    mov rdx, 12             ; number of bytes to read (32-bit input + null-terminator)
    syscall

    ; Call the "atoi32" function to convert the input to a signed 32-bit integer
    mov rsi, input
    call atoi32

    ; Call the "sature" function to limit the input
    mov rdi, rax
    call sature

    ; Store the result in "result" variable
    mov [result], ax

    ; Display the result
    mov rax, 0x1            ; syscall number for sys_write
    mov rdi, 0x1            ; file descriptor 1 (stdout)
    mov rsi, result_msg     ; pointer to the result message
    mov rdx, result_msg_len ; length of the result message
    syscall

    ; Exit the program
    mov rax, 0x60           ; syscall number for sys_exit
    xor rdi, rdi            ; exit status, 0 indicates success
    syscall

atoi32:
    ; Convert a null-terminated ASCII string to a 32-bit integer in rax
    xor rax, rax            ; Clear rax to store the result
    xor rcx, rcx            ; Clear rcx for counting characters processed
.loop:
    movzx rdi, byte [rsi + rcx]  ; Load the next character into rdi
    test  rdi, rdi               ; Check for the null terminator
    jz    .done                  ; If null terminator, we are done
    sub   rdi, '0'               ; Convert ASCII character to integer ('0' -> 0, '1' -> 1, ..., '9' -> 9)
    imul  rax, rax, 10           ; Multiply the current result by 10
    add   rax, rdi               ; Add the new digit to the result
    inc   rcx                    ; Move to the next character
    jmp   .loop
.done:
    ret
