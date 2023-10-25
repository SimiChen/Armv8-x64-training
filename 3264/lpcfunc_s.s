.global Get_lsp_pol

Get_lsp_pol:
    // x0 -> lsp, x1 -> f
    MOV x2, #0x1000000
    STR x2, [x1]              //f[0] = 0x1000000

    LDRH w3, [x0]               // Load lsp[0] into w3
    SXTH x3, w3                  // Sign-extend w3 to x3

    LSL x3, x3, #10              // Convert lsp[0] to Q24 format

    NEG x3, x3                  // Negate lsp[0] and store in x3
    STR w3, [x1, #4]                // Store -lsp[0] << 10 in Q24 format in f[1]

    MOV x8, 2                    // Set i = 2

.Get_lsp_pol_outer_loop:
    MOV x9, x8
    LSL x10, x8, #2               
    SUB x11, x10, #8
    LDR x3, [x1, x11]
    SXTW x3, w3
    STR w3, [x1, x10]           //f[2] = f[0];

.Get_lsp_pol_inner_loop:
    LSL x10, x9, #2               //add shift for f2
    SUB x11, x10, #4              //add shift for f1
    SUB x12, x11, #4              //add shift for f0
    LSL x13, x8, #1               
    SUB x13, x13, #2              
    LSL x13, x13, #1              //add shift for lsp2

    //x3 = f0, x4 = f1, x5 = f2, x2 = l sp2
    LDR x3, [x1, x12]                // Load f[j-2]
    SXTW x3, w3
    LDR x4, [x1, x11]                //load f[j-1]
    SXTW x4, w4
    LDR x5, [x1, x10]                //load f[j]
    SXTW x5, w5

    LDRH w2, [x0, x13]    // Load lsp[2*j-2] into w2
    SXTH x2, w2

    //x6 = hi, x7 = lo, x14 = t0
    
    ASR x6, x4, #16              //hi  = (short)(f[1] >> 16);

    LSL x7, x6, #16
    SUB x7, x4, x7              //lo  = (short)((f[1] >> 1) - ((int)hi<<15) );
    ASR x7, x7, #1              //lo  = (short)(f[1] - (int)hi << 16) >> 1

    MUL x14, x6, x2             //t0 = (int)hi * (int)lsp[2];

    MUL x15, x7, x2
    ASR x15, x15, #15
    ADD x14, x14, x15            //t0 += (int)lo * (int)lsp[2] >> 15;

    LSL x14, x14, #2              //t0 <<= 2;

    ADD x5, x5, x3                 //f[2] += f[0];
    SUB x5, x5, x14                //f[2] -= t0;

    //store f[2]
    STR w5, [x1, x10]                //f2

    SUB x9, x9, #1
    CMP x9, #1
    BNE .Get_lsp_pol_inner_loop            //inner loop when x9 > 1

    LSL x15, x2, #10
    SUB x4, x4, x15               //f[1] -= (int)lsp[2] << 10;

    STR w4, [x1, #4]             //f[1] -= (int)lsp[x8*2-2] << 10;
    
    ADD x8, x8, #1
    CMP x8, #6                   // Compare i with 2
    BNE .Get_lsp_pol_outer_loop         // If i != 6, repeat the loop
    RET

