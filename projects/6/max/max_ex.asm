(LOOP)
@0
D = M 
@1 
D = D-M 
@FIRST
D;JGT
@1 
D = M 
@2 
M = D 
@LOOP 
0;JMP

(FIRST)
@FIRST 
// if (R0>R1)
@0 
D = M 
@2 
M = D