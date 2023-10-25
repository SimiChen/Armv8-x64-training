section .text
global sature

sature:
    ; Input:
    ;   rdi: 32-bit signed integer (Word32)
    ; Output:
    ;   ax: 16-bit signed integer (Word16)

    ; Check if input is within the range of a signed 16-bit integer
    cmp rdi, 32767
    jg .input_too_large
    cmp rdi, -32768
    jl .input_too_small

    ; Input is within the valid range, store it as 16-bit result
    mov ax, di  ; Copy the lower 16 bits of the 32-bit input to ax
    ret

.input_too_large:
    ; Input is larger than the maximum 16-bit value, set ax to 32767
    mov ax, 32767
    ret

.input_too_small:
    ; Input is smaller than the minimum 16-bit value, set ax to -32768
    mov ax, -32768
    ret
