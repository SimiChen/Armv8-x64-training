section .data
    input_format db "%ld", 0       ; Format string for reading a long integer
    output_format db "You entered: %ld", 10, 0  ; Format string for printing the entered number

section .bss
    input_number resq 1             ; Reserve space for a 64-bit integer to store the input

section .text
    global _start

_start:
    ; Read a number from the terminal
    mov rdi, 0                      ; File descriptor 0 (stdin)
    mov rsi, input_number           ; Address to store the input
    mov rdx, 20                     ; Maximum number of digits to read (adjust as needed)
    mov rax, 0                      ; syscall number for sys_read
    syscall

    ; Null-terminate the input string (replace newline character with null terminator)
    mov rdi, rsi                    ; Set rdi to the address of the input string
    xor al, al                      ; Null terminator
    mov rcx, rdx                    ; Copy the maximum number of digits to rcx
    repnz scasb                     ; Search for null terminator
    jnz .input_done                 ; If not found, we are done
    mov byte [rdi - 1], 0          ; Null-terminate by replacing newline with null

.input_done:
    ; Print the entered number
    mov rdi, 1                      ; File descriptor 1 (stdout)
    mov rax, 0x1                    ; syscall number for sys_write
    mov rsi, input_number           ; Address of the entered number
    syscall

    

    ; Exit the program
    mov rax, 60                     ; syscall number for sys_exit
    xor rdi, rdi                    ; Exit status: 0
    syscall
