#include "parser.h"
#include <fstream>
#include <string>

using namespace std;

Parser::Parser (string& textFile) {
    fin.open(textFile);
    if (fin.fail())
        cout << "Fail to open " << textFile << endl;
    
    commandT['@'] = 'A';
    commandT['A'] = 'C';
    commandT['D'] = 'C';
    commandT['M'] = 'C';
    commandT['0'] = 'C';
    commandT['1'] = 'C';
    commandT['-'] = 'C';
    commandT['!'] = 'C';
    commandT['('] = 'L';
}

bool Parser::hasMoreLines () {
    return !fin.eof();
}

void Parser::advance (unsigned long& lineNum) {
    string command;
    bool commandNotFound = true;
    unsigned long cursor;

    while (getline(fin, command) && commandNotFound) { 
        lineNum++;
        // 공백제거
        command.erase(remove_if(command.begin(), command.end(), ::isspace), command.end());

        // 주석제거
        cursor = command.find("//");
        if (cursor != string::npos)
            command.erase(cursor, command.length() - cursor);

        commandNotFound = command.empty();
    }
    current_command = command;
}


char Parser::instructionType (unsigned long& lineNum) {
    if (commandT.find(current_command[0]) != commandT.end())
        return commandT[current_command[0]];
    exit(1);
}

string Parser::symbol () {
    unsigned long start_cursor = current_command.find("(");
    unsigned long end_cursor = current_command.find(")");
    // L-command
    if (start_cursor != string::npos && end_cursor != string::npos)
        return current_command.substr(start_cursor + 1, end_cursor - start_cursor - 1);
    // A-command
    else if (current_command[0] == '@')
        return current_command.substr(1, current_command.length() - 1);
    
    return "";
}

// dest = comp; jump
string Parser::dest () {
    unsigned long check = current_command.find("=");
    if (check != string::npos) {
        return current_command.substr(0, check);
    }
    return "";
}

string Parser::comp() {
    unsigned long check1, check2;
    check1 = current_command.find("=");
    check2 = current_command.find(";");

    if (check1 != string::npos) {
        if (check2 != string::npos) {
            return current_command.substr(check1 + 1, check2 - check1 - 1);
        }
        return current_command.substr(check1 + 1, current_command.length() - check1 - 1);
    }
    else if (check2 != string::npos) {
        return current_command.substr(0, check2);
    }
    return "";
}

string Parser::jump () {
    unsigned long check = current_command.find(";");
    if (check != string::npos) {
        return current_command.substr(check + 1, current_command.length() - check - 1);
    }
    return "";
}