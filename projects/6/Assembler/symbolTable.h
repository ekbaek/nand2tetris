#include <map>
#include <iostream>
#include <string>

using namespace std;

class SymbolTable {
private:
    map<string, int> symbolT;
public:
    SymbolTable ();
    void addEntry (string symbol, int value);
    bool containEntry (string symbol);
    int getAddress (string symbol);
};
