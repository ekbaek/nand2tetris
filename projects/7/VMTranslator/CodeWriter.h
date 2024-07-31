#ifndef _CODEWRITER_
#define _CODEWRITER_

#include <iostream>
#include <string>
#include <fstream>
#include "Parser.h"
using namespace std;

class CodeWriter
{
public:
	CodeWriter(string filename); 
	CodeWriter();
	~CodeWriter();

	void setFileName(string filename);
	void writeArithmetic(string command);
	void writePushPop(VMcommand pushOrPop, string segment, int index); 
	void close(void); 

	void popD(void); 
	void popGPR(int regNum); 
	void decSP(void); 
	void incSP(void);
	void setReturn(void); 
	void getReturn(void); 
	void init(void); 
	void push(string loc, int i); 
	void pop(string loc, int i); 
	
private:
	string filename_;
	ofstream outf;
	int labelnum_;
	int start_;
};

#endif