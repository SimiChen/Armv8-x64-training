.equ MIN_32, 0x80000000
.equ MAX_32, 0x7FFFFFFF


.global sature

sature:

    //LDR x3, [x0]           //old school shit, load the value that is in address which is in [x0]
    // Check if x0 is greater than 0x7fff
    MOV x2, x0                 // Copy the value in x0 to x2
    MOV x3, #0x0000000000007fff // Load the constant 0x7fff into x3
    MOV x4, #0xffffffffffff8000 // Load the constant 0xffff8000 into x4
    //LDR x4, =0xffffffffffff8000 not gonna use this since MOV is more efficient because it avoids memory access
    
    CMP x2, x3                // Compare x2 with x3
    BGT .sature_greater_than  // Branch to .sature_greater_than if x2 is greater than x3
    
    CMP x2, x4                // Compare x2 with x4
    BLT .sature_less_than     // Branch to .sature_less_than if x2 is less than x4
    
    RET x30 

.sature_greater_than:
    MOV x0, x3                 // Set x0 to 0x7fff
    RET x30         

.sature_less_than:
    MOV x0, x4                 // Set x0 to 0xffff8000
    RET x30             

.global add

add:
    ADD x0, x0, x1
    B   sature
    RET x30

.global L_add
 
L_add:
    ADD  x2, x0, x1                // L_var_out = L_var1 + L_var2
    EOR  x3, x0, x1                // Calculate L_var1 ^ L_var2
    AND  x3, x3, MIN_32            // Calculate (L_var1 ^ L_var2) & MIN_32
    CBNZ x3, .L_add_no_overflow    // If ((L_var1 ^ L_var2) & MIN_32) != 0, skip overflow check
    EOR  x4, x2, x0                // Calculate (L_var_out ^ L_var1)
    AND  x4, x4, MIN_32            // Calculate ((L_var_out ^ L_var1) & MIN_32)
    CBZ  x4, .L_add_no_overflow    // If ((L_var_out ^ L_var1) & MIN_32) == 0, skip overflow handling
    CMP  x0, #0                    // Compare L_var1 with 0
    MOV  x5, MIN_32
    MOV  x6, MAX_32
    CSEL x2, x5, x6, LT            // If L_var1 < 0, L_var_out = MIN_32, else L_var_out = MAX_32
    MOV  x0, x2
    RET  x30

.L_add_no_overflow:
    MOV  x0, x2
    RET  x30

.global L_sub
 
L_sub:
    SUB  x2, x0, x1                // L_var_out = L_var1 + L_var2
    EOR  x3, x0, x1                // Calculate L_var1 ^ L_var2
    AND  x3, x3, MIN_32            // Calculate (L_var1 ^ L_var2) & MIN_32
    CBZ  x3, .L_sub_no_overflow    // If ((L_var1 ^ L_var2) & MIN_32) == 0, skip overflow check
    EOR  x4, x2, x0                // Calculate (L_var_out ^ L_var1)
    AND  x4, x4, MIN_32            // Calculate ((L_var_out ^ L_var1) & MIN_32)
    CBZ  x4, .L_sub_no_overflow    // If ((L_var_out ^ L_var1) & MIN_32) == 0, skip overflow handling
    CMP  x0, #0                    // Compare L_var1 with 0
    MOV  x5, MIN_32
    MOV  x6, MAX_32
    CSEL x2, x5, x6, LT            // If L_var1 < 0, L_var_out = MIN_32, else L_var_out = MAX_32
    MOV  x0, x2
    RET  x30

.L_sub_no_overflow:
    MOV  x0, x2
    RET  x30


.global sub

sub:
    SUB  x0, x0, x1
    B    sature
    RET  x30

.global L_abs

L_abs:
    // Compare x0 with the constant 0xffff ffff 8000 0000
    MOV x2, MIN_32
    CMP x0, x2
    BEQ .abss_special_case

    // Check if x0 is negative
    TST x0, x0               // Test the sign bit of x0
    BMI .abss_negative       // Branch to .abss_negative if x0 is negative

    // x0 is non-negative and not the special case, no need to negate it
    RET  x30

.abss_special_case:
    // x0 is equal to 0xffff ffff 8000 0000, set it to 0x7fff ffff
    MOV  x0, MAX_32
    RET  x30

.abss_negative:
    // x0 is negative, negate it to get the absolute value
    NEG  x0, x0
    RET  x30

.global msu

msu:
    MUL  x3, x1, x2            // x3 = x1 * x2
    SUB  x0, x0, x3, LSL #1    // x0 = x0 - x3 * 2
    MOV  x4, MIN_32
    MOV  x5, MAX_32
    CMP  x0, x4            // Compare L_out with MIN_32
    CSEL x0, x4, x0, LT
    CMP  x0, x5             // Compare L_out with MAX_32
    CSEL x0, x5, x0, GT
    RET  x30


.global L_mac
//x0 L_var1 x1 var3 x2 var4
L_mac:
    MOV x4, x0
    MOV x0, x2
    MOV x8, x30
    BL L_mult
    MOV x1, x4
    BL L_add
    RET x8

.global extract_h

extract_h:
    LSR  x0, x0, #16    
    AND  x0, x0, #0xFFFF
    RET  x30

.global extract_l

extract_l:
    AND  x0, x0, #0xFFFF
    RET  x30

.global L_mult

L_mult:
    MUL  x0, x0, x1                // Multiply var1 and var2, result in x0 (L_var_out)
    MOV  x3, #0x40000000           // Load the constant 0x40000000 into x3
    CMP  x0, x3                    // Compare L_var_out with 0x40000000
    BNE  .L_mult_overflow           // Branch if not equal (not equal to 0x40000000)
    MOV  x0, MAX_32                 // Set L_var_out to 0x80000000
    RET  x30                       // Branch to the end
.L_mult_overflow:
    LSL  x0, x0, #1                // Multiply L_var_out by 2 (shift left by 1)
    RET  x30
