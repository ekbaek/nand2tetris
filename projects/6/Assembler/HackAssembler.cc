#include <iostream>
#include <fstream>
#include <bitset>
#include "parser.h"
#include "code.h"
#include "symbolTable.h"

using namespace std;

int main(int argc, char* argv[]) {
    string inputfile, outputfile;
    ofstream output;
    
    if (argc < 2 || argc > 3) {
        cout << "Retry to write input and output files.\n";
        exit(1);
    } else {
        inputfile = argv[1];
        outputfile = inputfile.substr(0, inputfile.length() - 4) + ".hack";
        if (argc == 3)
            outputfile = argv[2];
    }

    output.open(outputfile);
    if (output.fail()) {
        cout << "Failed to create output file." << endl;
        exit(1);
    }

    // 1 pass
    Parser source_1(inputfile);
    SymbolTable symboltable;

    unsigned long lineN = 0;
    int lineN_ReadOnly = 0;

    while (true) {
        source_1.advance(lineN);
        if (!source_1.hasMoreLines())
            break;
        if (source_1.instructionType(lineN) == 'A' || source_1.instructionType(lineN) == 'C')
            lineN_ReadOnly++;
        if (source_1.instructionType(lineN) == 'L' && !symboltable.containEntry(source_1.symbol()))
            symboltable.addEntry(source_1.symbol(), lineN_ReadOnly);
    }

    // 2-pass
    Code code;
    Parser source_2(inputfile);
    lineN = 0;
    int address_cnt = 16;

    // deal with A and C instruction
    while (true) {
        source_2.advance(lineN);
        if (!source_2.hasMoreLines())
            break;

        if (source_2.instructionType(lineN) == 'A') {
            output << '0';
            if (source_2.symbol().find_first_not_of("0123456789") == string::npos) {
                output << bitset<15>(stoull(source_2.symbol(), nullptr)).to_string();
            }
            // if symbol doesn't exist
            else {
                if (!symboltable.containEntry(source_2.symbol())) {
                    symboltable.addEntry(source_2.symbol(), address_cnt++);
                }
                output << bitset<15>(static_cast<unsigned long long>(symboltable.getAddress(source_2.symbol()))).to_string();
            } 
            output << endl;
        } else if (source_2.instructionType(lineN) == 'C') {
            output << "111";
            output << code.comp(source_2.comp(), lineN);
            output << code.dest(source_2.dest(), lineN);
            output << code.jump(source_2.jump(), lineN);
            output << endl;
        }
    }
    output.close();
    return 0;
}