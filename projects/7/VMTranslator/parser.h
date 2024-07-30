#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <fstream>

using namespace std;

enum TYPE
{
    C_ARITHMETIC,
    C_PUSH,
    C_POP,
    C_LABEL,
    C_GOTO,
    C_IF,
    C_FUNCTION,
    C_RETURN,
    C_CALL
};

class Parser {
private:
    istream fin;
    string current_command;
public:
    Parser (string& FileName);
    bool hasMoreLines ();
    string advance ();
    TYPE commandType ();
    string arg1 ();
    int arg2 ();
};

#endif PARSER_H