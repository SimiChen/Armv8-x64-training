.global multiply



multiply:
    LD1 {V1.4H}, [x0]
    LD1 {V2.4H}, [x1]

    //MUL V3.4S, V1.4S, V2.4S
    PMUL V4.4S, V1.4H, V2.4H


    ST1 {V4.4S}, [x2]

    //MOV w1, V3.S[0]        // Move the first float value to w1
    //MOV w2, V3.S[1]        // Move the second float value to w2
    //MOV w3, V3.S[2]        // Move the third float value to w3
    //MOV w4, V3.S[3]        // Move the fourth float value to w4



    RET