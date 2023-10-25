.global sature

sature:
    LDR x2, [x0]               // Load L_var1 from the address in x0 into x2
    MOV x3, x2                 // Move the value in x2 to x3
    LDR x5, =0x0000000000007fff // Load the constant 0x0000000000007fff into x5
    LDR x6, =0xffffffffffff8000 // Load the constant 0xffffffffffff8000 into x6

    CMP x3, x5                 // Compare the value in x3 with the value in x5
    BGT .greater_than           // Branch to greater_than if x3 is greater than x5

    CMP x3, x6                 // Compare the value in x3 with the value in x6
    BLT .less_than              // Branch to less_than if x3 is less than x6

    B .end                      // Branch to end if neither condition is met

.greater_than:
    STR x5, [x1]               // Store the value from x5 to the address in x1
    RET                     // Branch to done

.less_than:
    STR x6, [x1]               // Store the value from x6 to the address in x1
    RET                     // Branch to done

.end:
    STR x3, [x1]               // Store the value from x3 to the address in x1
    RET                        // Return from the function


.global shl
.global shr

shl:
    // Load var1 and var2 into x3 and x4
    LDRSH x3, [x0]           // Load var1 into x3 (16-bit signed load)
    LDRSH x4, [x1]           // Load var2 into x4 (16-bit signed load)

    MOV x5, x4

    // Check if var2 is negative
    CMP x5, #0               // Compare the sign bit with zero
    BGE .shl_internal        // Branch to shl_internal if sign bit is non-negative

    // Negative shift (right shift with sign extension)
    NEG x5, x4               // Negate var2 to make it positive
    B .shr_internal           // Call the internal shr function

.shl_internal:
    // Positive shift (left shift)
    CMP x5, #15              // Compare the value in x5 with 15
    BLT .shl_less_than_15    // Branch to shl_less_than_15 if x5 is less than 15
    LDR x5, =15             // If x5 is not less than 15, assign 15 to x5
    B .shl_end               // Branch to shl_end

.shl_less_than_15:
    // If x5 is less than 15, do nothing
    B .shl_end

.shl_end:
    LSL x7, x3, x5          //get new x7
    CMP x7, #0              //check if below 0
    BLT .shl_end_less_0      //if less than 0, go to shl_end_less_0
    LDR x6, =0x7fff          //check positive overflow
    CMP x7, x6
    BGE .shl_end_large       //if overflow go to shl_end_large
    B .shl_store_result     // Branch to the common store_result logic

.shl_end_less_0:
    LDR x6, =0xffffffffffff8000  //check negative overflow
    CMP x7, x6
    BLT .shl_end_small         //if overflow go to shl_end_small
    B .shl_store_result       //else store the value

.shl_end_large:
    LDR x7, =0x7fff
    B .shl_store_result

.shl_end_small:
    LDR x7, =0xffffffffffff8000
    B .shl_store_result

.shl_store_result:
    STR x7, [x2]           // Store the result back to memory as a 16-bit signed value
    RET x30

shr:
    // Load var1 and var2 into x3 and x4
    LDRSH x3, [x0]           // Load var1 into x3 (16-bit signed load)
    LDRSH x4, [x1]           // Load var2 into x4 (16-bit signed load)

    MOV x5, x4

    // Check if var2 is negative
    CMP x5, #0               // Compare the sign bit with zero
    BGE .shr_internal        // Branch to shr_internal if sign bit is non-negative

    // Negative shift (right shift with sign extension)
    NEG x5, x4               // Negate var2 to make it positive
    B .shl_internal           // Call the internal shl function

.shr_internal:
    // Right shift with sign extension
    CMP x5, #15              // Compare the value in x5 with 15
    BLT .shr_less_than_15    // Branch to shr_less_than_15 if x5 is less than 15
    LDR x5, =15             // If x5 is not less than 15, assign 15 to x5
    B .shr_end               // Branch to shr_end

.shr_less_than_15:
    // If x5 is less than 15, do nothing
    B .shr_end  

.shr_end:
    ASR x7, x3, x5
    B .shr_store_result     // Branch to the common store_result logic

.shr_store_result:
    // Store the result in the pointer held by x2
    STR x7, [x2]           // Store the result back to memory as a 16-bit signed value
    RET x30
