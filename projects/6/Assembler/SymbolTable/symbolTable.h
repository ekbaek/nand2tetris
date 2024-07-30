#include <map>
#include <iostream>
#include <string>

using namespace std;

class SymbolTable {
private:
    map<string, int> symbolT;
public:
    SymbolTable ();
    void addEntry (const string& symbol, int value);
    bool containEntry (const string& symbol);
    int getAddress (const string& symbol);
};
