#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <bitset>

using namespace std;

map<string, int> symbol_table;
map<string, string> comp_table;
map<string, string> dest_table;
map<string, string> jump_table;
int line_number = 0;
int variable_number = 16;

void add_label_symbol(const string &temp_line, int line_number);
void add_variable_symbol(const string &temp_line);
void initialize_table(map<string, int> &symbolTable, map<string, string> &compTable, map<string, string> &destTable, map<string, string> &jumpTable); 
string translate_A_inst(const string &line); 
string translate_C_inst(const string &line); 

int main() {
    string file_name;
    cout << "Enter a file name: ";
    cin >> file_name;
    
    string full_file_name = file_name + ".asm";
    ifstream ReadFile(full_file_name);
    if (!ReadFile) {
        cerr << "Error to read file name: " << file_name << endl;
        return -1;
    }
    initialize_table(symbol_table, comp_table, dest_table, jump_table);

    string line;
    while (getline(ReadFile, line)) {
        if (line.empty() || (line.size() > 1 && line[0] == '/' && line[1] == '/')) {
            continue;
        } else if (line[0] == '(' && line[line.size()-1] == ')') {
            string temp_line = line.substr(1, line.size()-2);
            add_label_symbol(temp_line, line_number);
            line_number++;
            continue;
        }
    } 

    ReadFile.clear();
    ReadFile.seekg(0, ios::beg);


    full_file_name = file_name + "1.hack";
    ofstream WriteFile(full_file_name);
    if (!WriteFile) {
        cerr << "Error to write file name: " << file_name << endl;
        return -1;
    }

    while (getline(ReadFile, line)) {
        if (line.empty()) {
            continue;
        } else if (line[0] == '@') {
            string temp_line = line.substr(1);
            add_variable_symbol(temp_line);
            line = translate_A_inst(temp_line);
        } else if (line.size() > 1 && line[0] == '/' && line[1] == '/') {
            continue;
        } else { 
            line = translate_C_inst(line);
        }
        WriteFile << line << "\n"; 
    }

    WriteFile.close();
    ReadFile.close();
    return 0;
}

void initialize_table(map<string, int> &symbolTable, map<string, string> &compTable, 
                        map<string, string> &destTable, map<string, string> &jumpTable) {
    symbolTable["SP"] = 0;
    symbolTable["LCL"] = 1;
    symbolTable["ARG"] = 2;
    symbolTable["THIS"] = 3;
    symbolTable["THAT"] = 4;
    symbolTable["R0"] = 0;
    symbolTable["R1"] = 1;
    symbolTable["R2"] = 2;
    symbolTable["R3"] = 3;
    symbolTable["R4"] = 4;
    symbolTable["R5"] = 5;
    symbolTable["R6"] = 6;
    symbolTable["R7"] = 7;
    symbolTable["R8"] = 8;
    symbolTable["R9"] = 9;
    symbolTable["R10"] = 10;
    symbolTable["R11"] = 11;
    symbolTable["R12"] = 12;
    symbolTable["R13"] = 13;
    symbolTable["R14"] = 14;
    symbolTable["R15"] = 15;
    symbolTable["SCREEN"] = 16384;
    symbolTable["KBD"] = 24576;

    compTable["0"] = "0101010";
    compTable["1"] = "0111111";
    compTable["-1"] = "0111010";
    compTable["D"] = "0001100";
    compTable["A"] = "0110000";
    compTable["M"] = "1110000";
    compTable["D+1"] = "0011111";
    compTable["A+1"] = "0110111";
    compTable["M+1"] = "1110111";
    compTable["D-1"] = "0001110";
    compTable["A-1"] = "0110010";
    compTable["M-1"] = "1110010";
    compTable["D+A"] = "0000010";
    compTable["D+M"] = "1000010";
    compTable["D-A"] = "0010011";
    compTable["D-M"] = "1010011";
    compTable["A-D"] = "0000111";
    compTable["M-D"] = "1000111";
    compTable["D&A"] = "0000000";
    compTable["D&M"] = "1000000";
    compTable["D|A"] = "0010101";
    compTable["D|M"] = "1010101";

    destTable[""] = "000";
    destTable["M"] = "001";
    destTable["D"] = "010";
    destTable["MD"] = "011";
    destTable["A"] = "100";
    destTable["AM"] = "101";
    destTable["AD"] = "110";
    destTable["AMD"] = "111";

    jumpTable[""] = "000";
    jumpTable["JGT"] = "001";
    jumpTable["JEQ"] = "010";
    jumpTable["JGE"] = "011";
    jumpTable["JLT"] = "100";
    jumpTable["JNE"] = "101";
    jumpTable["JLE"] = "110";
    jumpTable["JMP"] = "111";
}

void add_label_symbol(const string &temp_line, int line_number) {
    if (symbol_table.find(temp_line) == symbol_table.end()) {
        symbol_table[temp_line] = line_number;
    }
}

void add_variable_symbol(const string &temp_line) {
    if (symbol_table.find(temp_line) == symbol_table.end()) {
        symbol_table[temp_line] = variable_number++;
    }
}

string translate_A_inst(const string &line) {
    string partial_line = line;
    int address = stoi(partial_line);
    return bitset<16>(address).to_string();
}

string translate_C_inst(const string &line) {
    string dest = "000", comp = "0000000", jump = "000";
    string temp_line = line;  // 작업할 수 있도록 temp_line 사용

    // '='를 찾고 dest 설정
    size_t eq_pos = temp_line.find('=');
    if (eq_pos != string::npos) {
        dest = dest_table.count(temp_line.substr(0, eq_pos)) ? 
                dest_table[temp_line.substr(0, eq_pos)] : "000";
        temp_line = temp_line.substr(eq_pos + 1);  // '=' 이후 부분을 comp로 설정
    }

    // ';'를 찾고 jump 설정
    size_t sc_pos = temp_line.find(';');
    if (sc_pos != string::npos) {
        jump = jump_table.count(temp_line.substr(sc_pos + 1)) ? 
                jump_table[temp_line.substr(sc_pos + 1)] : "000";
        temp_line = temp_line.substr(0, sc_pos);  // ';' 이전 부분을 comp로 설정
    }

    // comp 필드 설정
    comp = comp_table.count(temp_line) ? comp_table[temp_line] : "0000000";
    
    // 총 명령어를 구성 (111 + comp + dest + jump)
    return "111" + comp + dest + jump;
}


