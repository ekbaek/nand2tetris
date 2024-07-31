#include "Parser.h"
#include <fstream>
#include <iostream>

Parser::Parser (string filename) {
    filename_ = filename;
    filename = filename + ".vm";
    fin.open(filename.c_str());
    if (!fin.is_open())
    {
        std::cerr << "Could not open input file " << filename << ".\n";
        exit(1);
    }
}

Parser::~Parser () {
    if (fin.is_open())
        fin.close();
}

bool Parser::hasMoreLines () {
    return !(fin.eof());
}

void Parser::advance () {
    if (hasMoreLines()) {
        getline(fin, current_command);
        while (((current_command.substr(0,2) == "//") || (current_command.substr(0,1) == "")) && hasMoreLines())
            getline(fin, current_command);
    }
}

TYPE Parser::commandType () {
    if (current_command.substr(0, 4) == "push")
        return C_PUSH;
    else if (current_command.substr(0, 3) == "pop")
        return C_POP;
    else if (current_command.substr(0,5) == "label")
        return C_LABEL;
    else if (current_command.substr(0, 4) == "goto")
        return C_GOTO;
    else if (current_command.substr(0, 2) == "if")
        return C_IF;
    else if (current_command.substr(0, 8) == "function")
        return C_FUNCTION;
    else if (current_command.substr(0, 6) == "return")
        return C_RETURN;
    else if (current_command.substr(0, 4) == "call")
        return C_CALL;
    else 
        return C_ARITHMETIC;
}

string Parser::arg1 () {
    if (commandType() == C_ARITHMETIC) {
        return current_command;
    } else {
        if (commandType() != C_RETURN) {
            int space1 = current_command.find("", 0);
            int space2 = current_command.find("", space1 + 1);
            return current_command.substr(space1 + 1, space2 - space1 - 1);
        }
    }
    return "";
}

int Parser::arg2()
{
	TYPE ct = commandType();
	if (ct == C_PUSH || ct == C_POP || ct == C_FUNCTION || ct == C_CALL)
	{
		int firstSpace = current_command.find(" ", 0);
		int secondSpace = current_command.find(" ", firstSpace + 1);
		int thirdSpace = current_command.find(" ", secondSpace + 1);
		string a2 = current_command.substr(secondSpace + 1, thirdSpace - secondSpace - 1);
		int a2i = stoi(a2);
		return a2i;
	}
    return -1;
}