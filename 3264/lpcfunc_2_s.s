.global g729ab_Lsp_Az

g729ab_Lsp_Az:
    SUB SP, SP, #48     //reserve spaces for f1 and f2
    MOV x20, x1
    MOV x21, x30

    //x0 -> lsp[0], x1 -> f1
    //load x1 to f1 which is sp + 32
    ADD x1, SP, #24

    BL Get_lsp_pol

    //x0 -> lsp[1], x1 -> f2
    ADD x0, x0, #2
    MOV x1, SP

    BL Get_lsp_pol

    //a[0] = 4096
    MOV x3, #4096
    MOV x1, x20        //restore x1 value 
    STRH w3, [x1]
    
    //i = 5
    MOV x8, #5

    //x2 -> f1[i], SP -> f2[i]
    ADD x2, SP, #24

.g729ab_Lsp_Az_loop_1:
    //x3 -> shift for i
    LSL x3, x8, #2
    
    //x4 -> f1[i] x6-> f2[i]
    LDR x4, [x2, x3]
    SXTW x4, w4
    LDR x6, [SP, x3]
    SXTW x6, w6

    //x5 -> f1[i-1] x7 -> f2[i-1]
    SUB x3, x3, #4
    LDR x5, [x2, x3]
    SXTW x5, w5
    LDR x7, [SP, x3]
    SXTW x7, w7

    //f1[i] += f1[i-1];
    ADD x3, x3, #4
    ADD x4, x4, x5
    STR w4, [x2, x3]

    //f2[i] -= f2[i-1];
    SUB x6, x6, x7
    STR w6, [SP, x3]

    SUB x8, x8, #1
    CMP x8, #0
    BGT .g729ab_Lsp_Az_loop_1   //loop

    MOV x8, #1

.g729ab_Lsp_Az_loop_2:
    //x2->f1 SP->f2 x1->a
    //x4 -> shift for i
    LSL x4, x8, #2
    
    //t0 = f1[i] + f2[i];
    LDR x5, [x2, x4]
    SXTW x5, w5
    LDR x6, [SP, x4]
    SXTW x6, w6
    ADD x7, x5, x6

    //( t0 >> 13 );
    ASR x9, x7, #13

    //if((t0 & 0x00001000) != 0) a[i]++;
    AND x7, x7, #0x00001000
    CMP x7, #0
    CSET x7, NE      
    ADD x9, x9, x7

    LSL x4, x8, #1
    STRH w9, [x1, x4]

    //t0 = f1[i] - f2[i];
    SUB x7, x5, x6

    //( t0 >> 13 );
    ASR x9, x7, #13

    //if((t0 & 0x00001000) != 0) a[j]++;
    AND x7, x7, #0x00001000
    CMP x7, #0
    CSET x7, NE
    ADD x9, x9, x7

    MOV x10, #11
    SUB x5, x10, x8
    LSL x4, x5, #1
    STRH w9, [x1, x4]

    ADD x8, x8, #1
    CMP x8, #6
    BLT .g729ab_Lsp_Az_loop_2

    //return the sp
    ADD SP, SP, #48
    RET x21


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

