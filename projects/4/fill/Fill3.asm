// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, 
// the screen should be cleared.

// 화면 시작 주소: 0x4000
// 화면의 크기: 32 x 256 비트 (32 워드 높이, 각 워드당 16 비트)

  @16384
  D = A
  @SCREEN_START
  M = D
  @SCREEN_CURSOR
  M = D 
  @8192
  D = D + A
  @SCREEN_END
  M = D

(LOOP)
  // 키보드 입력 0이면 화면을 흰색으로 채움
  @KBD 
  D = M 
  @WHITE_SCREEN
  D;JEQ
  // 키보드 입력이 있으면 화면을 검정으로 채움
  D = -1
  @SETSCREEN
  0;JMP

(WHITE_SCREEN)
  D = 0
  @SETSCREEN
  0;JMP

(SETSCREEN)
  @ARG
  M = D         // Save new status arg
  @SCREEN_CURSOR
  M = @SCREEN_START
  @8192
  D = A         // 8192
  @i
  M = D         // i = 8192

(SETLOOP)
  @i
  D = M - 1
  M = D         // i = i - 1
  @LOOP
  D;JLT         // if i < 0, goto LOOP
  
  @ARG
  D = M         // D = status
  @SCREEN_CURSOR
  A = M         // A = SCREEN_CURSOR
  M = D         // Set pixel
  @SCREEN_CURSOR
  M = M + 1
  @SETLOOP
  0;JMP

@SCREEN_START
@16384
@SCREEN_END
@24576
@SCREEN_CURSOR
@0
