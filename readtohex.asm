section .data
    output_format db "Hexadecimal: %s", 10, 0
    input_format db "%ld", 0

section .bss
    number resq 1
    hex_buffer resb 17  ; Buffer to store the hexadecimal representation (up to 16 digits)

section .text
    global _start

_start:
    ; Read the number from the terminal
    mov rdi, 0          ; File descriptor 0 (stdin)
    mov rsi, number     ; Address to store the input number
    mov rdx, 16         ; Maximum number of digits to read
    mov rax, 0          ; syscall number for sys_read
    syscall

.ascii_to_int_loop:
    movzx rax, byte [rsi]
    test rax, rax
    






    ; Convert the ASCII input to an integer
.ascii_to_int_loop:
    movzx rax, byte [rsi] ; Load the next character from the input
    test  rax, rax        ; Check if it's the null terminator
    jz    .ascii_to_int_done ; If null terminator, we are done
    sub   rax, '0'        ; Convert ASCII digit to integer
    imul  rdi, rdi, 10    ; Multiply the current result by 10
    add   rdi, rax        ; Add the digit to the result
    inc   rsi             ; Move to the next character
    jmp   .ascii_to_int_loop
.ascii_to_int_done:

    ; Convert the integer to hexadecimal and store it in hex_buffer
    mov rdi, hex_buffer  ; Destination buffer
    mov rsi, rdi         ; Pointer to the end of the buffer
    add rsi, 16          ; Move rsi to the end of the buffer
    mov byte [rsi], 0   ; Null-terminate the string

.int_to_hex_loop:
    dec rsi              ; Move backward in the buffer
    xor rdx, rdx         ; Clear any previous remainder
    div rcx              ; Divide rax by 16, result in rax, remainder in rdx
    add rdx, '0'          ; Convert remainder to ASCII
    cmp rax, '9'          ; Check if it's in the range '0'-'9'
    jbe .int_to_hex_store_digit
    add dl, 7            ; Adjust for 'A'-'F'
.int_to_hex_store_digit:
    mov [rsi], rdx        ; Store the ASCII digit in the buffer
    test rsi, rsi        ; Check if quotient is zero
    jnz .int_to_hex_loop

    ; Print the hexadecimal representation
    mov rdi, 1          ; File descriptor 1 (stdout)
    mov rax, 0x1        ; syscall number for sys_write
    lea rsi, [rdi + rsi] ; Address of the hexadecimal output
    mov rdx, 16         ; Length of the output (up to 16 digits)
    syscall

    ; Print a newline character
    mov rax, 0x1
    mov rdi, 0x1
    mov rsi, newline
    mov rdx, 1
    syscall

    ; Exit the program
    mov rax, 60         ; syscall number for sys_exit
    xor rdi, rdi        ; Exit status: 0
    syscall

section .data
    newline db 10, 0
