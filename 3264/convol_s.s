.equ MAX31, 0x3fffffff
.equ MIN31, -0x40000000

.global __ConvAdd

__ConvAdd:
    ASR x3, x3, #1          // acc >>= 1 (right shift by 1)
    MOV x8, #0              // Initialize j to 0

.__ConvAdd_loop:
    LSL x4, x8, #1

    LDRH w5, [x0, x4]      // Load p1[j] into w5 
    LDRH w6, [x1, x4]      // Load p2[j] into w6 
    SXTH x5, w5
    SXTH x6, w6

    MUL x5, x5, x6          // Multiply p1[j] and p2[j], store the result in x5
    ADD x3, x3, x5          // Add the result to acc

    ADD x8, x8, #1          // Increment j
    CMP x8, x2
    BLT .__ConvAdd_loop     // Branch back to loop

    LSL x0, x3, #1          // acc << 1 (left shift by 1)
    RET x30

.global __ConvSub

__ConvSub:
    ASR x3, x3, #1          // acc >>= 1 (right shift by 1)
    MOV x8, #0              // Initialize j to 0

.__ConvSub_loop:
    LSL x4, x8, #1          // Calculate the offset for loading elements from arrays

    LDRH w5, [x0, x4]       // Load p1[j] into w5
    LDRH w6, [x1, x4]       // Load p2[j] into w6
    SXTH x5, w5             // Sign-extend p1[j] to 32 bits
    SXTH x6, w6             // Sign-extend p2[j] to 32 bits

    MUL x5, x5, x6          // Multiply p1[j] and p2[j], store the result in x5
    SUB x3, x3, x5          // Subtract the result from acc

    ADD x8, x8, #1          // Increment j
    CMP x8, x2              // Compare j with size
    BLT .__ConvSub_loop     // Branch back to loop if j < size

    LSL x0, x3, #1          // acc << 1 (left shift by 1)
    RET x30                  // Return, x30 holds the return address

.global __ConvAdds

__ConvAdds:
    ASR x3, x3, #1           // acc >>= 1 (right shift by 1)
    MOV x9, #MAX31          // Load MAX31 into x9
    MOV x10, #MIN31          // Load MIN31 into x10
    MOV x8, #0              // Initialize overflow flag to 0

.__ConvAdds_loop:
    LSL x4, x8, #1          // Calculate the offset for loading elements from arrays

    LDRH w5, [x0, x4]        // Load p1[j] into w5
    LDRH w6, [x1, x4]        // Load p2[j] into w6
    SXTH x5, w5              // Sign-extend p1[j] to 32 bits
    SXTH x6, w6              // Sign-extend p2[j] to 32 bits

    MUL x5, x5, x6           // Multiply p1[j] and p2[j], store the result in x5
    ADDS x3, x3, x5          // Add the result to acc and set flags

    CMP x3, x9               // Compare acc with MAX31
    CSEL x3, x9, x3, GT      // If acc > MAX31, set acc to MAX31

    CMP x3, x10              // Compare acc with MIN31
    CSEL x3, x10, x3, LT     // If acc < MIN31, set acc to MIN31

    ADD x8, x8, #1           // Increment j
    CMP x8, x2               // Compare j with size
    BLT .__ConvAdds_loop     // Branch back to loop if j < size

    LSL x0, x3, #1           // acc << 1 (left shift by 1)
    RET x30                   // Return, x30 holds the return address

.global __ConvSubs

__ConvSubs:
    ASR x3, x3, #1           // acc >>= 1 (right shift by 1)
    MOV x9, #MAX31           // Load MAX31 into x9
    MOV x10, #MIN31          // Load MIN31 into x10
    MOV x8, #0               // Initialize overflow flag to 0

.__ConvSubs_loop:
    LSL x4, x8, #1           // Calculate the offset for loading elements from arrays

    LDRH w5, [x0, x4]        // Load p1[j] into w5
    LDRH w6, [x1, x4]        // Load p2[j] into w6
    SXTH x5, w5              // Sign-extend p1[j] to 32 bits
    SXTH x6, w6              // Sign-extend p2[j] to 32 bits

    MUL x5, x5, x6           // Multiply p1[j] and p2[j], store the result in x5
    SUBS x3, x3, x5          // Subtract the result from acc and set flags

    CMP x3, x9               // Compare acc with MAX31
    CSEL x3, x9, x3, GT      // If acc > MAX31, set acc to MAX31

    CMP x3, x10              // Compare acc with MIN31
    CSEL x3, x10, x3, LT     // If acc < MIN31, set acc to MIN31

    ADD x8, x8, #1           // Increment j
    CMP x8, x2               // Compare j with size
    BLT .__ConvSubs_loop     // Branch back to loop if j < size

    LSL x0, x3, #1           // acc << 1 (left shift by 1)
    RET x30                   // Return, x30 holds the return address

.global __ConvAddh

__ConvAddh:
    ASR x3, x3, #1           // acc >>= 1 (right shift by 1)
    MOV x8, #0               // Initialize j to 0

.__ConvAddh_loop:
    LSL x4, x8, #1           // Calculate the offset for loading elements from arrays

    LDRH w5, [x0, x4]        // Load p1[j] into w5
    LDRH w6, [x1, x4]        // Load p2[j] into w6
    SXTH x5, w5              // Sign-extend p1[j] to 32 bits
    SXTH x6, w6              // Sign-extend p2[j] to 32 bits

    MUL x5, x5, x6           // Multiply p1[j] and p2[j], store the result in x5
    ADD x3, x3, x5           // Add the result to acc

    ADD x8, x8, #1           // Increment j
    CMP x8, x2               // Compare j with size
    BLT .__ConvAddh_loop     // Branch back to loop if j < size

    MOV x0, x3
    RET x30                   // Return, x30 holds the return address

.global __ConvSubh

__ConvSubh:
    ASR x3, x3, #1           // acc >>= 1 (right shift by 1)
    MOV x8, #0               // Initialize j to 0

.__ConvSubh_loop:
    LSL x4, x8, #1           // Calculate the offset for loading elements from arrays

    LDRH w5, [x0, x4]        // Load p1[j] into w5
    LDRH w6, [x1, x4]        // Load p2[j] into w6
    SXTH x5, w5              // Sign-extend p1[j] to 32 bits
    SXTH x6, w6              // Sign-extend p2[j] to 32 bits

    MUL x5, x5, x6           // Multiply p1[j] and p2[j], store the result in x5
    SUB x3, x3, x5           // Subtract the result from acc

    ADD x8, x8, #1           // Increment j
    CMP x8, x2               // Compare j with size
    BLT .__ConvSubh_loop     // Branch back to loop if j < size

    MOV x0, x3
    RET x30                   // Return, x30 holds the return address

.global __ConvAddhs

__ConvAddhs:
    ASR x3, x3, #1           // acc >>= 1 (right shift by 1)
    MOV x9, #MAX31           // Load MAX31 into x9
    MOV x10, #MIN31 
    MOV x8, #0               // Initialize j to 0

.__ConvAddhs_loop:
    LSL x4, x8, #1           // Calculate the offset for loading elements from arrays

    LDRH w5, [x0, x4]        // Load p1[j] into w5
    LDRH w6, [x1, x4]        // Load p2[j] into w6
    SXTH x5, w5              // Sign-extend p1[j] to 32 bits
    SXTH x6, w6              // Sign-extend p2[j] to 32 bits

    MUL x5, x5, x6           // Multiply p1[j] and p2[j], store the result in x5
    ADDS x3, x3, x5          // Add the result to acc and set flags

    CMP x3, x9               // Compare acc with MAX31
    CSEL x3, x9, x3, GT      // If acc > MAX31, set acc to MAX31

    CMP x3, x10              // Compare acc with MIN31
    CSEL x3, x10, x3, LT     // If acc < MIN31, set acc to MIN31

    ADD x8, x8, #1           // Increment j
    CMP x8, x2               // Compare j with size
    BLT .__ConvAddhs_loop    // Branch back to loop if j < size

    MOV x0, x3
    RET x30                   // Return, x30 holds the return address

.global __ConvSubhs

__ConvSubhs:
    ASR x3, x3, #1           // acc >>= 1 (right shift by 1)
    MOV x9, #MAX31           // Load MAX31 into x9
    MOV x10, #MIN31
    MOV x8, #0               // Initialize j to 0

.__ConvSubhs_loop:
    LSL x4, x8, #1           // Calculate the offset for loading elements from arrays

    LDRH w5, [x0, x4]        // Load p1[j] into w5
    LDRH w6, [x1, x4]        // Load p2[j] into w6
    SXTH x5, w5              // Sign-extend p1[j] to 32 bits
    SXTH x6, w6              // Sign-extend p2[j] to 32 bits

    MUL x5, x5, x6           // Multiply p1[j] and p2[j], store the result in x5
    SUBS x3, x3, x5          // Subtract the result from acc and set flags

    CMP x3, x9               // Compare acc with MAX31
    CSEL x3, x9, x3, GT      // If acc > MAX31, set acc to MAX31

    CMP x3, x10              // Compare acc with MIN31
    CSEL x3, x10, x3, LT     // If acc < MIN31, set acc to MIN31

    ADD x8, x8, #1           // Increment j
    CMP x8, x2               // Compare j with size
    BLT .__ConvSubhs_loop    // Branch back to loop if j < size

    MOV x0, x3
    RET x30                   // Return, x30 holds the return address


.equ MAX32, 0x7FFFFFFF      // Maximum 32-bit signed integer
.equ MIN32, -0x80000000     // Minimum 32-bit signed integer

.global __ConvAddhS

__ConvAddhS:
    ASR x3, x3, #1           // acc >>= 1 (right shift by 1)
    MOV x9, #MAX32            // Load MAX31 into x9
    MOV x10, #MIN32           // Load MIN31 into x10
    MOV x8, #0               // Initialize j to 0

.__ConvAddhS_loop:
    LSL x4, x8, #1           // Calculate the offset for loading elements from arrays

    LDRH w5, [x0, x4]        // Load p1[j] into w5
    LDRH w6, [x1, x4]        // Load p2[j] into w6
    SXTH x5, w5              // Sign-extend p1[j] to 32 bits
    SXTH x6, w6              // Sign-extend p2[j] to 32 bits

    MUL x5, x5, x6           // Multiply p1[j] and p2[j], store the result in x7
    ADD x3, x3, x5

    CMP x3, x9               // Compare acc with MAX31
    CSEL x3, x9, x3, GT      // If acc > MAX31, set acc to MAX31

    CMP x3, x10               // Compare m with 0
    CSEL x3, x10, x3, LT     // If m < 0, set x7 to MIN31, else set x7 to MAX31

    ADD x8, x8, #1           // Increment j
    CMP x8, x2               // Compare j with size
    BLT .__ConvAddhS_loop    // Branch back to loop if j < size

    MOV x0, x3
    RET x30                   // Return, x30 holds the return address

.global __vMulr

__vMulr:
    MOV x8, #0               // Initialize j to 0

.__vMulr_loop:
    LSL x4, x8, #1           // Calculate the offset for loading elements from arrays

    LDRH w5, [x0, x4]        // Load v1[j] into w5
    LDRH w6, [x1, x4]        // Load v2[j] into w6
    SXTH x5, w5              // Sign-extend v1[j] to 32 bits
    SXTH x6, w6              // Sign-extend v2[j] to 32 bits

    MUL x5, x5, x6           // Multiply v1[j] and v2[j], store the result in x5

    ADD x5, x5, #0x00004000   // Add 0x00004000 to the result
    ASR x5, x5, #15          // Right shift the result by 15

    STRH w5, [x0, x4]        // Store the result back to v1[j]

    ADD x8, x8, #1           // Increment j
    CMP x8, x2               // Compare j with size
    BLT .__vMulr_loop        // Branch back to loop if j < size

    RET x30                   // Return, x30 holds the return address

.global __vAdd

__vAdd:
    MOV x8, #0               // Initialize j to 0

.__vAdd_loop:
    LSL x4, x8, #1           // Calculate the offset for loading elements from arrays

    LDRH w5, [x0, x4]        // Load v1[j] into w5
    LDRH w6, [x1, x4]        // Load v2[j] into w6
    SXTH x5, w5
    SXTH x6, w6

    ADD x5, x5, x6          // Add v2[j] to v1[j], set flags
    STRH w5, [x0, x4]        // Store the result back to v1[j]

    ADD x8, x8, #1           // Increment j
    CMP x8, x2               // Compare j with size
    BLT .__vAdd_loop         // Branch back to loop if j < size

    RET x30                   // Return, x30 holds the return address

.global __vSub

__vSub:
    MOV x8, #0               // Initialize j to 0

.__vSub_loop:
    LSL x4, x8, #1           // Calculate the offset for loading elements from arrays

    LDRH w5, [x0, x4]        // Load v1[j] into w5
    LDRH w6, [x1, x4]        // Load v2[j] into w6
    SXTH x5, w5
    SXTH x6, w6

    SUB x5, x5, x6          // Subtract v2[j] from v1[j], set flags
    STRH w5, [x0, x4]        // Store the result back to v1[j]

    ADD x8, x8, #1           // Increment j
    CMP x8, x2               // Compare j with size
    BLT .__vSub_loop         // Branch back to loop if j < size

    RET x30                   // Return, x30 holds the return address

.global __cMulr

__cMulr:
    MOV x8, #0               // Initialize j to 0

.__cMulr_loop:
    LSL x4, x8, #1           // Calculate the offset for loading elements from arrays

    LDRH w5, [x0, x4]        // Load v[j] into w5
    SXTH x5, w5              // Sign-extend v[j] to 32 bits

    MUL x5, x5, x1           // Multiply v[j] by coef, store the result in x5

    ADD x5, x5, #0x00004000   // Add 0x00004000 to the result
    ASR x5, x5, #15          // Right shift the result by 15

    STRH w5, [x0, x4]        // Store the result back to v[j]

    ADD x8, x8, #1           // Increment j
    CMP x8, x2               // Compare j with size
    BLT .__cMulr_loop        // Branch back to loop if j < size

    RET x30                   // Return, x30 holds the return address

.global __cAdd

__cAdd:
    MOV x8, #0               // Initialize j to 0

.__cAdd_loop:
    LSL x4, x8, #1           // Calculate the offset for loading elements from arrays

    LDRH w5, [x0, x4]        // Load v[j] into w5
    SXTH x5, w5

    ADD x5, x5, x1          // Add a to v[j], set flags
    STRH w5, [x0, x4]        // Store the result back to v[j]

    ADD x8, x8, #1           // Increment j
    CMP x8, x2               // Compare j with size
    BLT .__cAdd_loop         // Branch back to loop if j < size

    RET x30                   // Return, x30 holds the return address

.global __cSub

__cSub:
    MOV x8, #0               // Initialize j to 0

.__cSub_loop:
    LSL x4, x8, #1           // Calculate the offset for loading elements from arrays

    LDRH w5, [x0, x4]        // Load v[j] into w5
    SXTH x5, w5

    SUB x5, x5, x1          // Subtract a from v[j], set flags
    STRH w5, [x0, x4]        // Store the result back to v[j]

    ADD x8, x8, #1           // Increment j
    CMP x8, x2               // Compare j with size
    BLT .__cSub_loop         // Branch back to loop if j < size

    RET x30                   // Return, x30 holds the return address

.global __Circ

__Circ:
    MOV x9, #0               // Initialize i to 0

.__Circ_outer_loop:
    MOV x10, #0              // Initialize acc to 0
    MOV x8, x9               // Initialize j to i

.__Circ_inner_loop:
    //x9 -> i  x8 -> j
    LSL x4, x8, #1           // Calculate the offset for loading elements from arrays s1 and s2
    SUB x7, x8, x9
    LSL x7, x7, #1

    LDRH w5, [x1, x4]        // Load s1[j] into w5
    LDRH w6, [x2, x7]        // Load s2[j-i] into w6
    SXTH x5, w5              // Sign-extend s1[j] to 32 bits
    SXTH x6, w6              // Sign-extend s2[j-i] to 32 bits

    MUL x5, x5, x6           // Multiply s1[j] and s2[j-i], store the result in x5
    ADD x10, x10, x5         // Add the result to acc

    ADD x8, x8, #1           // Increment j
    CMP x8, x3               // Compare j with len
    BLT .__Circ_inner_loop   // Branch back to inner loop if j < len

    LSL x10, x10, #1         // acc << 1 (left shift by 1)
    LSL x7, x9, #2
    STR w10, [x0, x7]        // Store acc into dst[i]

    ADD x9, x9, #1           // Increment i
    CMP x9, x3               // Compare i with len
    BLT .__Circ_outer_loop   // Branch back to outer loop if i < len

    RET x30                  // Return, x30 holds the return address
 
.global __Circs

__Circs:
    MOV x9, #0               // Initialize i to 0
    MOV x11, #MIN31
    MOV x12, #MAX31

.__Circs_outer_loop:
    MOV x10, #0              // Initialize acc to 0
    MOV x8, x9               // Initialize j to i

.__Circs_inner_loop:
    LSL x4, x8, #1           // Calculate the offset for loading elements from arrays s1 and s2
    SUB x7, x8, x9
    LSL x7, x7, #1

    LDRH w5, [x1, x4]        // Load s1[j] into w5
    LDRH w6, [x2, x7]        // Load s2[j-i] into w6
    SXTH x5, w5              // Sign-extend s1[j] to 32 bits
    SXTH x6, w6              // Sign-extend s2[j-i] to 32 bits

    MUL x5, x5, x6           // Multiply s1[j] and s2[j-i], store the result in x5
    ADD x10, x10, x5         // Add the result to acc

    CMP x10, x11            // Compare acc with MIN31
    CSEL x10, x11, x10, LT  // If acc < MIN31, set acc to MIN31

    CMP x10, x12            // Compare acc with MAX31
    CSEL x10, x12, x10, GT  // If acc > MAX31, set acc to MAX31

    ADD x8, x8, #1           // Increment j
    CMP x8, x3               // Compare j with len
    BLT .__Circs_inner_loop  // Branch back to inner loop if j < len

    LSL x10, x10, #1         // acc << 1 (left shift by 1)
    LSL x7, x9, #2
    STR x10, [x0, x7]        // Store acc into dst[i]

    ADD x9, x9, #1           // Increment i
    CMP x9, x3               // Compare i with len
    BLT .__Circs_outer_loop  // Branch back to outer loop if i < len

    RET x30                   // Return, x30 holds the return address

.global __InvCirc

__InvCirc:
    MOV x9, #0               // Initialize i to 0

.__InvCirc_outer_loop:
    MOV x10, #0              // Initialize acc to 0
    MOV x8, #0               // Initialize j to 0

.__InvCirc_inner_loop:
    LSL x4, x8, #1           // Calculate the offset for loading elements from arrays s1 and s2
    SUB x7, x9, x8
    LSL x7, x7, #1

    LDRH w5, [x1, x4]        // Load s1[j] into w5
    LDRH w6, [x2, x7]        // Load s2[i-j] into w6
    SXTH x5, w5              // Sign-extend s1[j] to 32 bits
    SXTH x6, w6              // Sign-extend s2[i-j] to 32 bits

    MUL x5, x5, x6           // Multiply s1[j] and s2[i-j], store the result in x5
    ADD x10, x10, x5         // Add the result to acc

    ADD x8, x8, #1           // Increment j
    CMP x8, x9               // Compare j with i
    BLE .__InvCirc_inner_loop // Branch back to inner loop if j <= i

    LSL x10, x10, #1         // acc << 1 (left shift by 1)
    LSL x7, x9, #2
    STR x10, [x0, x7]        // Store acc into dst[i]

    ADD x9, x9, #1           // Increment i
    CMP x9, x3               // Compare i with len
    BLT .__InvCirc_outer_loop // Branch back to outer loop if i < len

    RET x30                   // Return, x30 holds the return address

.global __InvCircs

__InvCircs:
    MOV x9, #0               // Initialize i to 0
    MOV x11, #MIN31
    MOV x12, #MAX31

.__InvCircs_outer_loop:
    MOV x10, #0              // Initialize acc to 0
    MOV x8, #0               // Initialize j to 0

.__InvCircs_inner_loop:
    LSL x4, x8, #1           // Calculate the offset for loading elements from arrays s1 and s2
    SUB x7, x9, x8
    LSL x7, x7, #1

    LDRH w5, [x1, x4]        // Load s1[j] into w5
    LDRH w6, [x2, x7]        // Load s2[i-j] into w6
    SXTH x5, w5              // Sign-extend s1[j] to 32 bits
    SXTH x6, w6              // Sign-extend s2[i-j] to 32 bits

    MUL x5, x5, x6           // Multiply s1[j] and s2[i-j], store the result in x5
    ADD x10, x10, x5         // Add the result to acc

    CMP x10, x11            // Compare acc with MIN31
    CSEL x10, x11, x10, LT  // If acc < MIN31, set acc to MIN31

    CMP x10, x12            // Compare acc with MAX31
    CSEL x10, x12, x10, GT  // If acc > MAX31, set acc to MAX31

    ADD x8, x8, #1           // Increment j
    CMP x8, x9               // Compare j with i
    BLE .__InvCircs_inner_loop // Branch back to inner loop if j <= i

    LSL x10, x10, #1         // acc << 1 (left shift by 1)
    LSL x7, x9, #2
    STR x10, [x0, x7]        // Store acc into dst[i]

    ADD x9, x9, #1           // Increment i
    CMP x9, x3               // Compare i with len
    BLT .__InvCircs_outer_loop // Branch back to outer loop if i < len

    RET x30                   // Return, x30 holds the return address

.global __vShlw

__vShlw:
    MOV x8, #0                // Initialize j to 0
    SXTH x2, w2
    CMP x2, #0
    BGE .__vShlw_loop_positive

    NEG x2, x2
    B .__vShlw_loop_negative

.__vShlw_loop_positive:
    LSL x4, x8, #1            // Calculate the offset for loading elements from arrays

    LDRH w5, [x1, x4]         // Load v2[j] into w5
    SXTH x5, w5

    LSL x5, x5, x2
    STRH w5, [x0, x4]         // Store the result to v1[j]

    ADD x8, x8, #1            // Increment j
    CMP x8, x3                // Compare j with size
    BLT .__vShlw_loop_positive         // Branch back to loop if j < size

    RET x30                   // Return, x30 holds the return address

.__vShlw_loop_negative:
    LSL x4, x8, #1            // Calculate the offset for loading elements from arrays

    LDRH w5, [x1, x4]         // Load v2[j] into w5
    SXTH x5, w5

    ASR x5, x5, x2
    STRH w5, [x0, x4]         // Store the result to v1[j]

    ADD x8, x8, #1            // Increment j
    CMP x8, x3                // Compare j with size
    BLT .__vShlw_loop_negative         // Branch back to loop if j < size

    RET x30                   // Return, x30 holds the return address

.global __vShrw

__vShrw:
    MOV x8, #0                // Initialize j to 0
    SXTH x2, w2
    CMP x2, #0
    BGE .__vShrw_loop_positive

    NEG x2, x2
    B .__vShrw_loop_negative

.__vShrw_loop_positive:
    LSL x4, x8, #1            // Calculate the offset for loading elements from arrays

    LDRH w5, [x1, x4]         // Load v2[j] into w5
    SXTH x5, w5

    ASR x5, x5, x2
    STRH w5, [x0, x4]         // Store the result to v1[j]

    ADD x8, x8, #1            // Increment j
    CMP x8, x3                // Compare j with size
    BLT .__vShrw_loop_positive         // Branch back to loop if j < size

    RET x30                   // Return, x30 holds the return address

.__vShrw_loop_negative:
    LSL x4, x8, #1            // Calculate the offset for loading elements from arrays

    LDRH w5, [x1, x4]         // Load v2[j] into w5
    SXTH x5, w5

    LSL x5, x5, x2
    STRH w5, [x0, x4]         // Store the result to v1[j]

    ADD x8, x8, #1            // Increment j
    CMP x8, x3                // Compare j with size
    BLT .__vShrw_loop_negative         // Branch back to loop if j < size

    RET x30                   // Return, x30 holds the return address

.global __vShldw

__vShldw:
    MOV x8, #0                // Initialize j to 0
    SXTH x2, w2
    CMP x2, #0
    BGE .__vShldw_loop_positive

    NEG x2, x2
    B .__vShldw_loop_negative

.__vShldw_loop_positive:
    LSL x4, x8, #2            // Calculate the offset for loading elements from arrays

    LDR w5, [x1, x4]         // Load v2[j] into w5
    SXTw x5, w5

    LSL x5, x5, x2
    STR w5, [x0, x4]         // Store the result to v1[j]

    ADD x8, x8, #1            // Increment j
    CMP x8, x3                // Compare j with size
    BLT .__vShldw_loop_positive         // Branch back to loop if j < size

    RET x30                   // Return, x30 holds the return address

.__vShldw_loop_negative:
    LSL x4, x8, #2            // Calculate the offset for loading elements from arrays

    LDR w5, [x1, x4]         // Load v2[j] into w5
    SXTW x5, w5

    ASR x5, x5, x2
    STR w5, [x0, x4]         // Store the result to v1[j]

    ADD x8, x8, #1            // Increment j
    CMP x8, x3                // Compare j with size
    BLT .__vShldw_loop_negative         // Branch back to loop if j < size

    RET x30                   // Return, x30 holds the return address

.global __vShrdw

__vShrdw:
    MOV x8, #0                // Initialize j to 0
    SXTH x2, w2
    CMP x2, #0
    BGE .__vShrdw_loop_positive

    NEG x2, x2
    B .__vShrdw_loop_negative

.__vShrdw_loop_positive:
    LSL x4, x8, #2            // Calculate the offset for loading elements from arrays

    LDR w5, [x1, x4]         // Load v2[j] into w5
    SXTW x5, w5

    ASR x5, x5, x2
    STR w5, [x0, x4]         // Store the result to v1[j]

    ADD x8, x8, #1            // Increment j
    CMP x8, x3                // Compare j with size
    BLT .__vShrdw_loop_positive         // Branch back to loop if j < size

    RET x30                   // Return, x30 holds the return address

.__vShrdw_loop_negative:
    LSL x4, x8, #2            // Calculate the offset for loading elements from arrays

    LDR w5, [x1, x4]         // Load v2[j] into w5
    SXTW x5, w5

    LSL x5, x5, x2
    STR w5, [x0, x4]         // Store the result to v1[j]

    ADD x8, x8, #1            // Increment j
    CMP x8, x3                // Compare j with size
    BLT .__vShrdw_loop_negative         // Branch back to loop if j < size

    RET x30                   // Return, x30 holds the return address

.global __vRound

__vRound:
    MOV x8, #0                // Initialize i to 0

.__vRound_loop:
    LSL x6, x8, #2
    LSL x4, x8, #1            // Calculate the offset for loading elements from v2 and storing into v1

    LDR w5, [x1, x6]          // Load v2[i] into w5 (32-bit value)
    ADD x5, x5, #0x00008000    // Add 0x00008000 to round the value
    LSR x5, x5, #16            // Right shift 16 bits to perform the division by 2^16 (equivalent to >> 16 in C)
    SXTH x5, w5                // Extract the lower 16 bits (WORD16) of the result

    STRH w5, [x0, x4]         // Store the rounded value into v1[i] (WORD16)

    ADD x8, x8, #1            // Increment i
    CMP x8, x2                // Compare i with size
    BLT .__vRound_loop        // Branch back to loop if i < size

    RET x30                   // Return, x30 holds the return address

.global __ConvFirIir

__ConvFirIir:
    MOV x8, #0              // Initialize i to 0

    // First loop: accumulate the products of v1[i] and v2[i] for i in [0, 10)
.__ConvFirIir_first_loop:
    LSL x4, x8, #1          // Calculate the offset for loading elements from v1 and v2
    LDRH w5, [x0, x4]       // Load v1[i] into w5
    LDRH w6, [x1, x4]       // Load v2[i] into w6
    SXTH x5, w5             // Sign-extend v1[i] to 32 bits
    SXTH x6, w6             // Sign-extend v2[i] to 32 bits
    MUL x5, x5, x6          // Multiply v1[i] and v2[i]
    LSL x5, x5, #1          // Left shift the result by 1
    ADD x2, x2, x5          // Accumulate the result in acc

    ADD x8, x8, #1          // Increment i
    CMP x8, #10             // Compare i with 10
    BLT .__ConvFirIir_first_loop // Branch back to loop if i < 10

    // Second loop: subtract the products of v1[i] and v2[i] for i in [10, 20)
.__ConvFirIir_second_loop:
    LSL x4, x8, #1          // Calculate the offset for loading elements from v1 and v2
    LDRH w5, [x0, x4]       // Load v1[i] into w5
    LDRH w6, [x1, x4]       // Load v2[i] into w6
    SXTH x5, w5             // Sign-extend v1[i] to 32 bits
    SXTH x6, w6             // Sign-extend v2[i] to 32 bits
    MUL x5, x5, x6          // Multiply v1[i] and v2[i]
    LSL x5, x5, #1          // Left shift the result by 1
    SUB x2, x2, x5          // Subtract the result from acc

    ADD x8, x8, #1          // Increment i
    CMP x8, #20             // Compare i with 20
    BLT .__ConvFirIir_second_loop // Branch back to loop if i < 20

    MOV x0, x2
    RET x30                 // Return, x30 holds the return address

.global __vMovw
.global __vMovdw
.global __vSetw
.global __vSetdw

__vMovw:
    MOV x8, #0               // Initialize i to 0

.__vMovw_loop:
    LSL x4, x8, #1           // Calculate the offset for loading elements from v2 and storing into v1

    LDRH w5, [x1, x4]        // Load v2[i] into w5 (16-bit value)
    STRH w5, [x0, x4]        // Store the value into v1[i] (16-bit)

    ADD x8, x8, #1           // Increment i
    CMP x8, x2               // Compare i with size
    BLT .__vMovw_loop        // Branch back to loop if i < size

    RET x30                   // Return, x30 holds the return address

__vMovdw:
    MOV x8, #0               // Initialize i to 0

.__vMovdw_loop:
    LSL x4, x8, #2           // Calculate the offset for loading elements from v2 and storing into v1

    LDR w5, [x1, x4]         // Load v2[i] into w5 (32-bit value)
    STR w5, [x0, x4]         // Store the value into v1[i] (32-bit)

    ADD x8, x8, #1           // Increment i
    CMP x8, x2               // Compare i with size
    BLT .__vMovdw_loop       // Branch back to loop if i < size

    RET x30                   // Return, x30 holds the return address

__vSetw:
    MOV x8, #0               // Initialize i to 0

.__vSetw_loop:
    LSL x4, x8, #1           // Calculate the offset for storing elements in v1

    STRH w1, [x0, x4]        // Store the constant value into v1[i] (16-bit)

    ADD x8, x8, #1           // Increment i
    CMP x8, x2               // Compare i with size
    BLT .__vSetw_loop        // Branch back to loop if i < size

    RET x30                   // Return, x30 holds the return address

__vSetdw:
    MOV x8, #0               // Initialize i to 0

.__vSetdw_loop:
    LSL x4, x8, #2           // Calculate the offset for storing elements in v1

    STR w1, [x0, x4]         // Store the constant value into v1[i] (32-bit)

    ADD x8, x8, #1           // Increment i
    CMP x8, x2               // Compare i with size
    BLT .__vSetdw_loop       // Branch back to loop if i < size

    RET x30                   // Return, x30 holds the return address

