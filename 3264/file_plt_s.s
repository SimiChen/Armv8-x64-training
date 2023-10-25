.global filt_plt

filt_plt:
    SXTH x3, w3
    MOV x4, #32767
    SUB x6, x4, x3            // gain_plt_1 = 32767 - gain_plt
    SXTH x6, w6

    // Check if gain_plt is not equal to 0
    CBZ x3, .filt_plt_skip       // if gain_plt == 0, skip increment
    ADD x6, x6, 1               // gain_plt_1++

.filt_plt_skip:
    // Initialize loop counter (n = 0)
    MOV x4, #0

.loop_start:
    LSL x9, x4, #1               //x9 = x4 * 2(address shift)
    // Load s_in[n] into w7 (assuming short is 2 bytes)
    LDRH w7, [x0, x9] // s_in[n] (short *s_in)
    SXTH x7, w7
    // Load s_ltp[n] into w8 (assuming short is 2 bytes)
    LDRH w8, [x1, x9] // s_ltp[n] (short *s_ltp)
    SXTH x8, w8

    MUL x7, x3, x7           // x7 = gain_plt * s_in[n] 
    MUL x8, x6, x8           // x8 = gain_plt_1 * s_ltp[n]
    ADD x7, x7, x8
    ADD x7, x7, #0x4000
    // Right shift 15 bits to divide by 2^15 (equivalent to >> 15 in C)
    ASR x8, x7, #15            // x8  = x7 >> 15

    // Store the result in s_out[n]
    STRH w8, [x2, x9]  // s_out[n] = x7 (short *s_out)

    // Increment loop counter (n++)
    ADD x4, x4, 1

    // Check loop condition (n < L_SUBFR =40), loop if true
    CMP x4, #40
    BLT .loop_start

    RET
