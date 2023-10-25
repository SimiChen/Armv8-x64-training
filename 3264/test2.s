.global shl  // Declare the function as a global symbol

shl:
    // Function body
    // Compute the return value (for example, 42)
    //LDR x3, [x0]
    //LDR x4, [x1]

    add x0, x0, x1


    ret x30       // Return using the link register x30
