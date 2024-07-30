SANFLAGS = -fsanitize=address
CXX = g++
CXXFLAGS += -Wall -std=c++2b -g $(SANFLAGS)
LDFLAGS += $(SANFLAGS)

# 실행 파일 이름
TARGET = main

# 소스 및 객체 파일
SRC = HackAssembler.cc Code/code.cc Parser/parser.cc SymbolTable/symbolTable.cc
OBJ = $(SRC:.cc=.o)

# 기본 규칙
all: $(TARGET)

# 실행 파일 생성 규칙
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# 개별 객체 파일 규칙
HackAssembler.o: HackAssembler.cc
	$(CXX) $(CXXFLAGS) -c HackAssembler.cc

Code/code.o: Code/code.cc Code/code.h
	$(CXX) $(CXXFLAGS) -c Code/code.cc

Parser/parser.o: Parser/parser.cc Parser/parser.h
	$(CXX) $(CXXFLAGS) -c Parser/parser.cc

SymbolTable/symbolTable.o: SymbolTable/symbolTable.cc SymbolTable/symbolTable.h
	$(CXX) $(CXXFLAGS) -c SymbolTable/symbolTable.cc

# 청소 규칙
clean:
	rm -f $(OBJ) $(TARGET)
