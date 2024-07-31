#ifndef CODEWRITER_H
#define CODEWRITER_H

#include <iostream>
#include <fstream>
#include <string>
#include "Parser.h"

using namespace std;

class CodeWriter {
public:
    CodeWriter ();
    CodeWriter (string FileName);
    void setFileName (string FileName);
    void init ();
    void writeArithmetic (string type);
    void writePushPop (TYPE type, string arg1, int arg2);
    void close ();

    // additional functions
    void increaseSP ();
    void decreaseSP ();
    void push (string segment, int i);
    void pop (string segment, int i);
    void popStoreToRam (int registerNum); // value in stack stores to registerNum
    void popStoreToDreg ();
    void setReturn ();
    void getReturn ();
private:
    ofstream fout;
    string filename;
    string current_command;
    int labelN;
    int start;
};

#endif // CODEWRITER_H