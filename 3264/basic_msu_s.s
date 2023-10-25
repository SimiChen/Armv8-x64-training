.global sature

sature:
    LDR x2, [x0]               // Load L_var1 from the address in x0 into x2
    MOV x3, x2                 // Move the value in x2 to x3
    LDR x5, =0x000000007fffffff // Load the constant 0x00007fff into x5
    LDR x6, =0xffffffff80000000 // Load the constant 0xffffffff80000000 into x6

    CMP x3, x5                 // Compare the value in x3 with the value in x5
    BGT greater_than           // Branch to greater_than if x3 is greater than x5

    CMP x3, x6                 // Compare the value in x3 with the value in x6
    BLT less_than              // Branch to less_than if x3 is less than x6

    B end                      // Branch to end if neither condition is met

greater_than:
    STR x5, [x1]               // Store the value from x5 to the address in x1
    B done                     // Branch to done

less_than:
    STR x6, [x1]               // Store the value from x6 to the address in x1
    B done                     // Branch to done

end:
    STR x3, [x1]               // Store the value from x3 to the address in x1
    RET                        // Return from the function

done:
    RET                        // Return from the function

.global add

add:
    // Load the two 64-bit words into registers x3 and x4
    LDR x3, [x0]       // Load the first 64-bit word from the address in x0 into x3
    LDR x4, [x1]       // Load the second 64-bit word from the address in x1 into x4
    
    // Perform the addition and store the result in x5
    ADD x5, x3, x4
    
    // Store the result back to the address in x2
    STR x5, [x2]
    
    // Return from the function
    RET

.global sub

sub:
    // Load the two 64-bit words into registers x3 and x4
    LDR x3, [x0]       // Load the first 64-bit word from the address in x0 into x3
    LDR x4, [x1]       // Load the second 64-bit word from the address in x1 into x4
    
    // Perform the subtraction and store the result in x5
    SUB x5, x3, x4
    
    // Store the result back to the address in x2
    STR x5, [x2]
    
    // Return from the function
    RET

.global abss

abss:
    // Load the 32-bit signed integer from the address in x0
    LDRSW x2, [x0]     // Load a signed word (32 bits) from the address in x0 into x2

    // Check for the special case where x2 is equal to 0xffff ffff 8000 0000
    // If it's the special case, set x2 to 0x000000007fffffff
    // Otherwise, continue to return the absolute value
    
    // Compare x2 with the constant since immediate values in instructions 
    // are limited to a 12-bit signed range
    // Load the 0xffff ffff 8000 0000 into a register
    MOV x3, #0xffffffff80000000
    CMP x2, x3
    BEQ special_case

    // Check if x2 is negative (sign bit is set)
    // If it's negative, take two's complement to get the absolute value
    TST x2, x2         // Test the sign bit of x2
    BMI negative       // Branch to negative if x2 is negative

    // x2 is non-negative and not the special case, no need to negate it
    // Continue to return the absolute value

    // Store the absolute value back to the address in x1
    STR x2, [x1]
    RET

negative:
    // x2 is negative, negate it to get the absolute value
    NEG x2, x2

    // Store the absolute value back to the address in x1
    STR x2, [x1]

    // Return the absolute value in x2
    RET

special_case:
    // x2 is equal to 0xffffffff80000000, set it to 0x000000007fffffff
    MOV x2, #0x7fffffff

    // Store the special case value back to the address in x1
    STR x2, [x1]

    // Return the special case value in x2
    RET


.global msu

msu:
    LDR X4, [X1]           // Load the value at the address in X0 into X4
    LDR X5, [X2]           // Load the value at the address in X1 into X5
    LDR X6, [X0]           // Load the value at the address in X2 into X6

    MUL X7, X4, X5   // Perform Multiply X7 = X4 * X5

    SUB X7, X6, X7, LSL #1 // X7 = X6 - X7 << 1 or X7 = X6 - X7 * 2

    STR X7, [X3]           // Store the value in X7 to the address in X3
    ret
