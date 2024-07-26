#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <map>

using namespace std;

// • Constructor / initializer: 
// Creates a Parser and opens the source text file

// • Getting the current instruction:
// hasMoreLines(): 
// Checks if there is more work to do (boolean)
// advance(): 
// Gets the next instruction and makes it the current instruction (string)

// • Parsing the current instruction:
// instructionType(): 
// Returns the instruction type symbol(): Returnstheinstruction’ssymbol(string) 
//dest(): Returnstheinstruction’sdestfield(string) 
//comp(): Returns the instruction’s comp field (string) jump(): Returnstheinstruction’sjumpfield(string)

class Parser {
private:
    map<char, char> commandT;
    string current_command;
public:
    Parser (string& textFile);
    bool hasMoreLines();
    void advance (long& lineNum);
    char instructionType(long& lineNum);  
    string symbol();  
    string dest();  
    string comp();  
    string jump();  
};

#endif PARSER_H