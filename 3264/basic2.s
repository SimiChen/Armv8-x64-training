.global sature

sature:
    LDR x2, [x0]      // Load L_var1 from the address in x0 into x2
    MOV x3, x2
    LDR x5, =0x00007fff   // Load the constant 0x00007fff into x5
    LDR x6, =0xffff8000   // Load the constant 0xffff8000 into x6

    CMP x3, x5            // Compare the value in x3 with the value in x5
    BGT greater_than      // Branch if greater than

    CMP x3, x6            // Compare the value in x3 with the value in x6
    BLT less_than         // Branch if less than

    B end                   // Branch to end if neither condition is met

    greater_than:
        MOV x4, #0x00007fff   // Load the immediate value 0x7fff into x4
        STR x4, [x1]      // Store the value from x4 to the address in x1
        B done

    less_than:
        MOV x4, #0xffff8000   // Load the immediate value 0x8000 into x4
        STR x4, [x1]      // Store the value from x4 to the address in x1
        B done

    end:
        STR x3, [x1]
        RET

    done:
        RET
