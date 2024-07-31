#include <iostream>
#include <string>
#include "Parser.h"
#include "CodeWriter.h"

using namespace std;

int main (int argc, char* argv[]) {
    CodeWriter codewriter;
    for (int i = 1; i < argc; i++) {
        string filename = argv[i];
        int dot = filename.find(".", 0);
        filename = filename.substr(0, dot);
        Parser parser(filename);
        codewriter.setFileName(filename);
        while (parser.hasMoreLines()) {
            parser.advance ();
            if (parser.commandType() == C_ARITHMETIC) 
                codewriter.writeArithmetic(parser.arg1());
            else if (parser.commandType() == C_POP || parser.commandType() == C_PUSH)
                codewriter.writePushPop(parser.commandType(), parser.arg1(), parser.arg2());

        }
    }
    return 0;
}