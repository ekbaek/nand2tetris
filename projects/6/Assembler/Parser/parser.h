#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <map>

using namespace std;

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