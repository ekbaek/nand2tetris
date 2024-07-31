#include <iostream>
#include <map>
#include <fstream>

using namespace std;

class Parser {
private:
    ifstream fin;
    map<char, char> commandT;
    string current_command;
public:
    Parser (string& textFile);
    bool hasMoreLines();
    void advance (unsigned long& lineNum);
    char instructionType(unsigned long& lineNum);  
    string symbol();  
    string dest();  
    string comp();  
    string jump();  
};
