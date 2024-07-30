#include "parser.h"

Parser::Parser (string File) {
    fin.open(File.c_str());
    if (fin.fail())
        cout << "Fail to open " << File << endl;
}

bool Parser::hasMoreLines () {
    return !(fin.eof());
}

string Parser::advance () {
    if (hasMoreLines()) {
        getline(fin, current_command);
        while (current_command.substr(0,2) == "//" || (current_command.substr(0,1) == "" && hasMoreLines()))
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
    if (commandType() == "C_ARITHMETIC") {
        return current_command;
    } else {
        if (commandType() != "C_RETURN") {
            int space1 = current_command.find('', 0);
            int space2 = current_command.find('', space1 + 1);
            return current_command.substr(space1 + 1, space2 - space1 - 1);
        }
    }
}

int Parser::arg2 () {
    if (commandType() == ("C_PUSH" || "C_POP" || "C_FUNCTION" || "C_CALL")) {
        int space1 = current_command.find('', 0);
        int space2 = current_command.find('', space1 + 1);
        string temp = current_command.substr(space2 + 1, current_command.length() - space2 - 1);
        return stoi(temp);
    }
}
