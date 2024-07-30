#include <iostream>
#include <map>

using namespace std;

class Code {
private:
    map<string, string> compT;
    map<string, string> destT;
    map<string, string> jumpT;
public:
    Code ();
    string comp (string type, unsigned long& lineNum);
    string dest (string type, unsigned long& lineNum);
    string jump (string type, unsigned long& lienNum);
};
