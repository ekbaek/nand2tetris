#include "CodeWriter.h"
#include <iostream>

CodeWriter::CodeWriter () {
    labelN = 0;
    start = 0;
}

CodeWriter::CodeWriter (std::string FileName) {
    labelN = 0;
    start = 0;
    filename = FileName;
    FileName += ".asm";
    fout.open(FileName.c_str());
    if (fout.fail())    
        std::cout << "Fail to open " << FileName << std::endl;
    init();
}

void CodeWriter::setFileName (std::string FileName) {
	if (fout.is_open())
		fout.close();
	filename = FileName;
	FileName = FileName + ".asm";
	fout.open(FileName.c_str());
	if (!fout.is_open())
		cerr << "Could not open output file " << filename << ".\n";
	init();

}

void CodeWriter::init () {
    fout << "@START" << start << std::endl << "0;JMP" << std::endl << "(MAKETRUE)" << std::endl;
    decreaseSP();
    fout << "M=-1" << std::endl;
    increaseSP();
    getReturn();
    fout << "(START" << start << ")" << std::endl;
    start++;
}

void CodeWriter::writeArithmetic (std::string type) {
    if (type == "add") {
        popStoreToDreg ();
        decreaseSP ();
        fout << "M=M+D" << std::endl;
        increaseSP ();
    } else if (type == "sub") {
        popStoreToDreg ();
        decreaseSP ();
        fout << "M=M-D" << std::endl;
        increaseSP ();
    } else if (type == "neg") {
        decreaseSP ();
        fout << "M=-M" << std::endl;
        increaseSP ();
    } else if (type == "eq") {
        setReturn ();
        popStoreToDreg ();
        decreaseSP ();
        fout << "D=D-M" << std::endl << "M=0" << std::endl;
        increaseSP();
        fout << "@MAKETRUE" << std::endl << "D;JEQ" << std::endl << "(RETURN" << labelN << ")"<< std::endl;
        labelN++;
    } else if (type == "gt") {
        setReturn ();
        popStoreToDreg ();
        decreaseSP ();
        fout << "D=D-M" << std::endl << "M=0" << std::endl;
        increaseSP();
        fout << "@MAKETRUE" << std::endl << "D;JLT" << std::endl << "(RETURN" << labelN << ")"<< std::endl;
        labelN++;        
    } else if (type == "lt") {
        setReturn ();
        popStoreToDreg ();
        decreaseSP ();
        fout << "D=D-M" << std::endl << "M=0" << std::endl;
        increaseSP();
        fout << "@MAKETRUE" << std::endl << "D;JGT" << std::endl << "(RETURN" << labelN << ")"<< std::endl;
        labelN++;        
    } else if (type == "and") {
        popStoreToDreg ();
        decreaseSP ();
        fout << "M=M&D" << std::endl;
        increaseSP ();
    } else if (type == "or") {
        popStoreToDreg ();
        decreaseSP ();
        fout << "M=M|D" << std::endl;
        increaseSP ();        
    } else if (type == "not") {
        decreaseSP ();
        fout << "M=!M" << std::endl;
        increaseSP ();
    }
}

void CodeWriter::writePushPop (TYPE type, std::string segment, int arg2) {
    if (type == C_PUSH) {
        if (segment == "constant") {
            fout << "@" << arg2 << std::endl << "D=A" << std::endl;
            fout << "@SP" << std::endl << "A=M" << std::endl << "M=D" << std::endl;
            increaseSP ();
        } else if (segment == "local") {
            push ("LCL", arg2);
        } else if (segment == "argument") {
            push ("ARG", arg2);
        } else if (segment == "this") {
            push ("THIS", arg2);
        } else if (segment == "that") {
            push ("THAT", arg2);
        } else if (segment == "static") {
            fout << "@" << filename << "." << arg2 << std::endl << "D=M" << std::endl << "@SP" << std::endl << "A=M" << std::endl << "M=D" << std::endl;
            increaseSP ();
        } else if (segment == "temp") {
            push ("5", arg2);
        } else if (segment == "pointer") {
            if (arg2 == 0)
                push ("THIS", arg2);
            else if (arg2 == 1)
                push ("THAT", arg2);
        }
    } else if (type == C_POP) {
        if (segment == "local") {
            pop ("LCL", arg2);
        } else if (segment == "argument") {
            pop ("ARG", arg2);
        } else if (segment == "this") {
            pop ("THIS", arg2);
        } else if (segment == "that") {
            pop ("THAT", arg2);
        } else if (segment == "static") {
            fout << "@" << filename << "." << arg2 << std::endl << "D=A" << std::endl << "@R13" << std::endl << "M=D" << std::endl << "@SP"  << std::endl << "M=M-1" << std::endl << "A=M" << std::endl << "D=M" << std::endl << "@R13" << std::endl << "A=M" << std::endl << "M=D" << std::endl;        
        } else if (segment == "temp") {
            pop ("5", arg2);
        } else if (segment == "pointer") {
            if (arg2 == 0) // 이것도 확인
                pop ("THIS", arg2);
            else if (arg2 == 1)
                pop ("THAT", arg2);            
        }
    }
}

void CodeWriter::close () {
    if (fout.is_open())
        fout.close();   
}

void CodeWriter::increaseSP () {
    fout << "@SP" << std::endl << "AM=M+1" << std::endl;
}

void CodeWriter::decreaseSP () {
    fout << "@SP" << std::endl << "AM=M-1" << std::endl;
}

void CodeWriter::push (std::string segment, int i) {
    if (segment == "3" || segment == "5") {
        fout << "@" << segment << std::endl << "D=A" << std::endl << "@" << i << std::endl << "A=D+A" << std::endl << "D=M" << std::endl << "@SP" << std::endl << "A=M" << std::endl << "M=D" << std::endl;
        increaseSP ();
    } else {
        fout << "@" << segment << std::endl << "D=M" << std::endl << "@" << i << std::endl << "A=D+A" << std::endl << "D=M" << std::endl << "@SP" << std::endl << "A=M" << std::endl << "M=D" << std::endl;
        increaseSP ();
    }
}

void CodeWriter::pop (std::string segment, int i) {
    if (segment == "3" || segment == "5") {
        fout << "@" << segment << std::endl << "D=A" << std::endl << "@" << i << std::endl << "D=D+A" << std::endl;
        popStoreToRam (13);
        decreaseSP ();
        fout << "D=M" << std::endl << "@R13" << std::endl << "A=M" << std::endl << "M=D" << std::endl;
    } else {
        fout << "@" << segment << std::endl << "D=M" << std::endl << "@" << i << std::endl << "D=D+A" << std::endl;
        popStoreToRam (13);
        decreaseSP ();
        fout << "D=M" << std::endl << "@R13" << std::endl << "A=M" << std::endl << "M=D" << std::endl;
    }
}

void CodeWriter::popStoreToRam (int registerNum) {
    if (registerNum >= 13 && registerNum <= 15) {
        fout << "@" << registerNum << std::endl << "M=D" << std::endl;
    }
}

void CodeWriter::popStoreToDreg () {
    fout << "@SP" << std::endl << "AM=M-1" << std::endl << "D=M" << std::endl;
}

void CodeWriter::setReturn () {
    fout << "@RETURN" << labelN << std::endl << "D=A" << std::endl << "@R15" << std::endl << "M=D" << std::endl;
}

void CodeWriter::getReturn () {
    fout << "@R15" << std::endl << "A=M" << std::endl << "0;JMP" << std::endl;
}
