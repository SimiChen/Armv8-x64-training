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
