// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
// The algorithm is based on repetitive addition.

  @R2 
  M = 0
  @R3
  M = 1
(LOOP)
  // if (R3 > R1) goto END
  @R3 
  D = M
  @R1 
  D = D - M 
  @END 
  D;JGT 
  // R2 = R2 + R0
  @R0 
  D = M 
  @R2 
  M = M + D 
  // R3 = R3 + 1
  @R3
  M = M + 1
  // goto LOOP
  @LOOP 
  0;JMP
(END)
  @END
  0;JMP

