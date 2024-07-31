#include "code.h"

Code::Code () {
    destT[""] = "000";
    destT["M"] = "001";
    destT["D"] = "010";
    destT["MD"] = "011";
    destT["A"] = "100";
    destT["AM"] = "101";
    destT["AD"] = "110";
    destT["AMD"] = "111";

    compT["0"] = "0101010";
    compT["1"] = "0111111";
    compT["-1"] = "0111010";
    compT["D"] = "0001100";
    compT["A"] = "0110000";
    compT["!D"] = "0001101";
    compT["!A"] = "0110001";
    compT["-D"] = "0001111";
    compT["-A"] = "0110011";
    compT["D+1"] = "0011111";
    compT["A+1"] = "0110111";
    compT["D-1"] = "0001110";
    compT["A-1"] = "0110010";
    compT["D+A"] = "0000010";
    compT["D-A"] = "0010011";
    compT["A-D"] = "0000111";
    compT["D&A"] = "0000000";
    compT["D|A"] = "0010101";
    compT["M"] = "1110000";
    compT["!M"] = "1110001";
    compT["-M"] = "1110011";
    compT["M+1"] = "1110111";
    compT["M-1"] = "1110010";
    compT["D+M"] = "1000010";
    compT["D-M"] = "1010011";
    compT["M-D"] = "1000111";
    compT["D&M"] = "1000000";
    compT["D|M"] = "1010101";

    jumpT[""] = "000";
    jumpT["JGT"] = "001";
    jumpT["JEQ"] = "010";
    jumpT["JGE"] = "011";
    jumpT["JLT"] = "100";
    jumpT["JNE"] = "101";
    jumpT["JLE"] = "110";
    jumpT["JMP"] = "111";
}

string Code::comp (string type, unsigned long& lineNum) {
    if (compT.find(type) != compT.end()) 
        return compT[type];
    exit(1);
}

string Code::dest (string type, unsigned long& lineNum) {
    if (destT.find(type) != destT.end()) 
        return destT[type];
    exit(1);
}

string Code::jump (string type, unsigned long& lineNum) {
    if (jumpT.find(type) != jumpT.end())
        return jumpT[type];
    exit(1);
}
