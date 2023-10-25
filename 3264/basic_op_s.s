.global sature

sature:

    //LDR x3, [x0]           //old school shit, load the value that is in address which is in [x0]
    // Check if x0 is greater than 0x7fff
    MOV x2, x0                 // Copy the value in x0 to x2
    MOV x3, #0x0000000000007fff // Load the constant 0x7fff into x3
    MOV x4, #0xffffffffffff8000 // Load the constant 0xffff8000 into x4
    //LDR MOV x4, =0xffffffffffff8000 not gonna use this since MOV is more efficient because it avoids memory access
    
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
    RET x30

.global sub

sub:
    SUB x0, x0, x1
    RET x30

.global abss

abss:
    // Compare x0 with the constant 0xffff8000
    MOV x2, 0xffffffffffff8000
    CMP x0, x2
    BEQ .abss_special_case

    // Check if x0 is negative
    TST x0, x0               // Test the sign bit of x0
    BMI .abss_negative       // Branch to .abss_negative if x0 is negative

    // x0 is non-negative and not the special case, no need to negate it
    RET x30

.abss_special_case:
    // x0 is equal to 0xffff8000, set it to 0x7fff
    MOV x0, #0x7fff
    RET x30

.abss_negative:
    // x0 is negative, negate it to get the absolute value
    NEG x0, x0
    RET x30

.global msu

msu:
    MUL x3, x1, x2            // x3 = x1 * x2
    SUB x0, x0, x3, LSL #1    // x0 = x0 - x3 * 2
    RET x30

.global shl
.global shr

shl:
    // Check if var2 is negative
    CMP x1, #0               // Compare the sign bit with zero
    BGE .shl_internal        // Branch to .shl_internal if sign bit is non-negative

    // Negative shift (right shift with sign extension)
    NEG x1, x1               // Negate var2 to make it positive
    B .shr_internal           // Call the internal shr function

.shl_internal:
    // Positive shift (left shift)
    CMP x1, #15              // Compare the value in x1 with 15
    BLT .shl_end             // Branch to .shl_end if x1 is less than 15
    MOV x1, #15              // If x1 is not less than 15, assign 15 to x1
    
.shl_end:
    LSL x0, x0, x1          // Left shift x0 by the value in x1
    CMP x0, #0              // Check if x0 is below 0
    BLT .shl_end_less_0     // Branch to .shl_end_less_0 if x0 is less than 0
    MOV x4, #0x7fff         // Check for positive overflow
    CMP x0, x4
    BGE .shl_end_large      // Branch to .shl_end_large if overflow occurs
    RET x30

.shl_end_less_0:
    MOV x4, #0xffffffffffff8000  // Check for negative overflow
    CMP x0, x4
    BLT .shl_end_small      // Branch to .shl_end_small if overflow occurs
    RET x30

.shl_end_large:
    MOV x0, #0x7fff
    RET x30

.shl_end_small:
    MOV x0, #0xffffffffffff8000
    RET x30

shr:
    // Check if var2 is negative
    CMP x1, #0               // Compare the sign bit with zero
    BGE .shr_internal        // Branch to .shr_internal if sign bit is non-negative

    // Negative shift (right shift with sign extension)
    NEG x1, x1               // Negate var2 to make it positive
    B .shl_internal           // Call the internal shl function

.shr_internal:
    // Right shift with sign extension
    CMP x1, #15              // Compare the value in x1 with 15
    BLT .shr_end             // Branch to .shr_end if x1 is less than 15
    MOV x1, #15              // If x1 is not less than 15, assign 15 to x1
    
.shr_end:
    ASR x0, x0, x1           // Arithmetic right shift x0 by the value in x1
    RET x30                    // Return from the function


.global mac

mac:
    MOV x4, #2
    SMULL x3, w1, w2
    MADD x0, x4, x3, x0
    RET x30

