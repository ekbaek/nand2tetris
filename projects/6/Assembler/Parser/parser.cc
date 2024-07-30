#include "parser.h"
#include <fstream>
#include <string>

using namespace std;


Parser::Parser (string& textFile) {
    fin.open(textFile);
    if fin.fail() 
        cout << "Fail to open " << textFile << endl;
    
    commandT['@'] = 'A';
    commandT['('] = 'L';
}

bool Parser::hasMoreLines () {
    return fin.eof();
}

void Parser::advance (unsigned long& lineNum) {
    string command;
    bool commandNotFound = true;
    unsigned long cursor;

    while (getline(cin, command) && commandNotFound) {
        // 공백제거
        command.erase(remove_if(command.begin(), command.end(), ::isspace), command.end());

        // 주석제거
        cursor = command.find('//');
        if (cursor != string::npos)
            command.erase(cursor, command.length() - cursor);

        lineNum++;
        commandNotFound = command.empty();
    }
    current_command = command;
}

char Parser::instructionType (ungigned long& lineNum) {
    if (commandT.find(current_command[0]) != string::npos)
        return commandT[current_command[0]];
    else
        return 'C';
}

string Parser::symbol () {
    unsigned long start_cursor = current_command.find('(');
    unsigned long end_cursor = current_command.find(')');
    // L-command
    if (start_cursor != string::npos && end_cursor != string::npos)
        return current_command.substr(start_cursor + 1, end_cursor - start_cursor - 1);
    // A-command
    if (current_command[0] == '@')
        return current_command.substr(1, current_command.length() - 1);
    
    return "";
}

// dest = comp; jump
string Parser::dest () {
    unsigned long check = current_command.find('=');
    if (check != string::npos) {
        return current_command.substr(0, check);
    }
    return "000";
}

string Parser::comp () {
    unsigned long check1 = current_command.find('=');
    unsigned long check2 = current_command.find(';');

    if (check1 != string::npos && check2 == string::npos) {
        return current_command.substr(check1 + 1, current_command.length() - check1 - 1);
    } else if (check1 == string::npos && check2 != string::npos) {
        return current_command.substr(0, current_command.length() - check2 - 1);
    } else if (check1 != string::npos && check2 != string::npos) {
        return current_command.substr(check1 + 1, check2 - check1 - 1);
    }
    return current_command;
}

string Parser::jump () {
    unsigned long check = current_command.find(';');
    if (check != string::npos) {
        return current_command.substr(check + 1, current_command.length() - check - 1);
    }
    return "000";
}