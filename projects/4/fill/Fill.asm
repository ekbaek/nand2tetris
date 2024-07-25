// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, 
// the screen should be cleared.

// 화면의 크기: 32 x 256 비트
// 이 16진수를 10진수로 변환

  @SCREEN 
  D=A
  @8192
  D=D+A
  @END_ADDRESS
  M=D

(LOOP)
// 키보드 입력 0이면 계속 무한루프
  @KBD 
  D = M 
  @COLOR_SELECT
  D;JEQ
  D=-1

(COLOR_SELECT)
  @ARG //keyboard 값 임시 저장
  M=D 
  @COLOR
  D=D-M 
  @LOOP 
  D;JEQ 

  @ARG 
  D=M 
  @COLOR
  M=D 

  @SCREEN
  D=A 
  @SCREEN_CURSOR 
  M=D

(COLOR_SCREEN)
  @SCREEN_CURSOR
  D=M+1
  M=D
  @END_ADDRESS
  D=D-M 
  @LOOP
  D;JGT

  @COLOR
  D=M
  @SCREEN_CURSOR
  A=M 
  M=D // M[screen cursor]=data
  @COLOR_SCREEN
  0;JMP




