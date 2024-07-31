#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <fstream>
#include <string>

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
    ifstream fin;
    string current_command;
    string filename_;
public:
    Parser (string filename);
    ~Parser ();
    bool hasMoreLines ();
    void advance ();
    TYPE commandType ();
    string arg1 ();
    int arg2 ();
};

#endif // PARSER_H