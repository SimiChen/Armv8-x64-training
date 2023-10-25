.global Chebps_11

Chebps_11:
    // Input parameters: x (in x0), f (in x1), n (in x2)
    // Output: cheb (in x0)

    // Initialize b2_h and b2_l
    MOV x3, #256     // b2_h = 256
    MOV x4, #0       // b2_l = 0

    // Initialize t0 with x
    SXTH x0, w0
    MOV x5, x0       // t0 = x

    // Add f[1] << 3 to t0
    LDRH w6, [x1, #2]    // Load f[1] (second element of f array) into x6 (16-bit value)
    SXTH x6, w6
    LSL x6, x6, #3       // Convert f[1] to Q24 and left shift by 3 bits
    ADD x5, x5, x6       // t0 += (int)f[1] << 3 in Q24

    // Calculate b1_h and b1_l
    ASR x6, x5, #6       // Calculate b1_h = t0 >> 6
    LSL x7, x5, #9       // t0 << 9
    SUB x7, x7, x6, LSL #15  // Subtract b1_h << 15 [29 line print]
    

    // Initialize loop counter (i = 2)
    MOV x8, #2

loop_start:
    // Calculate b1_h * x
    MUL x5, x6, x0

    // Calculate (int)b1_l * (int)x >> 15
    MUL x9, x7, x0
    ASR x9, x9, #15
    ADD x5, x5, x9     //[37 line print]


    // Multiply t0 by 2 and subtract b2
    LSL x5, x5, #2    //t0 <<= 2;
    SUB x5, x5, x3, LSL #16
    SUB x5, x5, x4, LSL #1


    // Add f[i] << 13
    LSL x9, x8, #1
    LDRH w10, [x1, x9]   // Load f[i] (ith element of f array) into x10 (16-bit value)
    SXTH x10, w10
    LSL x10, x10, #13            // Convert f[i] shift left 13 bits
    ADD x5, x5, x10              // t0 += f[i] << 13 [43 line print]

    // Get b0_h and b0_l
    SXTW x5, w5
    ASR x11, x5, #16
    ASR x12, x5, #1
    SUB x12, x12, x11, LSL #15   //[50 line print]

    MOV x3, x6   //b2_h = b1_h
    MOV x4, x7   //b2_l = b1_l
    MOV x6, x11  //b1_h = b0_h
    MOV x7, x12  //b1_l = b0_l

    // Check if the loop counter is less than n
    ADD x8, x8, #1
    CMP x8, x2
    BLT loop_start

    //break from looop
    // Calculate b1_h * x
    MUL x5, x6, x0

    // Calculate (int)b1_l * (int)x >> 15
    MUL x9, x7, x0
    ASR x9, x9, #15
    ADD x5, x5, x9         //[62 line print]

    SUB x5, x5, x3, LSL #15
    SUB x5, x5, x4

    LSL x9, x8, #1
    LDRH w10, [x1, x9]    // Load f[i] (ith element of f array) into x10 (16-bit value)
    SXTH x10, w10
    LSL x10, x10, #11            // Convert f[i] shift left 11 bits
    ADD x5, x5, x10              // t0 += f[i] << 11
 
    ASR x5, x5, #9           //t0 >>= 9       [67 line print]

saturation:
    // Saturation: if t0 > 32767L, t0 = 32767L
    MOV x1, #32767
    CMP x5, x1
    CSEL x5, x1, x5, GT

    // Saturation: if t0 < -32768L, t0 = -32768L
    MOV x1, #-32768
    CMP x5, x1
    CSEL x5, x1, x5, LT

    MOV x0, x5

    RET x30
