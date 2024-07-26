#ifndef CODE_H
#define CODE_H

#include <iostream>
#include <map>

using namespace std;

class Code {
private:
    map<string, string> compT;
    map<string, string> destT;
    map<string, string> jumpT;
    string 
public:
    Code ();
    string comp (string type, long& lineNum);
    string dest (string type, long& lineNum);
    string jump (string type, long& lienNum);
}
#endif CODE_H