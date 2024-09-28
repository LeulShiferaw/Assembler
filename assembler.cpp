#include "assembler.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

Assembler::Assembler(const string& inname) :my_parser(inname), file_name(inname){
    fileOut.open("Prog.hack"); 
    if(!fileOut.is_open()) {
        cerr << "File Prog.hack couldn't open!" << endl;
    }

    symbol_table["R0"] = "0";
    symbol_table["R1"] = "1";
    symbol_table["R2"] = "2";
    symbol_table["R3"] = "3";
    symbol_table["R4"] = "4";
    symbol_table["R5"] = "5";
    symbol_table["R6"] = "6";
    symbol_table["R7"] = "7";
    symbol_table["R8"] = "8";
    symbol_table["R9"] = "9";
    symbol_table["R10"] = "10";
    symbol_table["R11"] = "11";
    symbol_table["R12"] = "12";
    symbol_table["R13"] = "13";
    symbol_table["R14"] = "14";
    symbol_table["R15"] = "15";
    symbol_table["SP"] = "0";
    symbol_table["LCL"] = "1";
    symbol_table["ARG"] = "2";
    symbol_table["THIS"] = "3";
    symbol_table["THAT"] = "4";
    symbol_table["SCREEN"] = "16384";
    symbol_table["KBD"] = "24576";
    symbol_table["ITSR0"] = "13";
}

string Assembler::to_binary(const string &input) {
    //Convert input to binary
    int val = stoi(input);
    string res = "";
    while(val != 0) {
        res += to_string(val%2);
        val/=2;
    }

    reverse(res.begin(), res.end()); //Don't forget to reverse

    //Add filler 0 at top to make 16 characters
    int x = res.size();
    string tmp = "";
    while(x < 16) {
        tmp += "0";
        ++x;
    }
    res = tmp + res;
    return res;
}

//-2 = predefined
//0 = invalid
//1 = integer
//-1 = variable
int valid(const string &str) {
    if(str.size() == 0) {
        cerr << "valid(str) has str size 0!" << endl;
        exit(0);
    }

    vector<string> possible = {"R0", "R1", "R2", "R3", "R4", "R5", "R6", "R7", "R8", "R9", "R10", "R11", "R12", "R13", "R14", "R15", "SP", "LCL", "ARG", "THIS", "THAT", "SCREEN", "KBD"};

    for(auto &x : possible) if(str == x) return -2;
    if(str[0] >= '0' && str[0] <= '9') {
        for(auto &c : str) {
            if(c < '0' || c > '9') return 0;
        }
        return 1;
    } else {
        for(auto &c : str) {
            if((c < 'A' || c > 'Z') && (c < 'a' || c > 'z') && (c < '0' || c > '9') && c != '_' && c != '.' && c != '$' && c != ':') return 0;
        }
        return -1;
    }
}

void Assembler::firstPass() {
    Parser test_parser(file_name);
    test_parser.advance();
    int line_num = 0;
    while(test_parser.instructionType() != INST_TYPE::NONE) {
        if(test_parser.instructionType() == INST_TYPE::L_INSTRUCTION) {
            auto my_symbol = test_parser.symbol();
            symbol_table[my_symbol] = to_string(line_num);
            --line_num;
        }
        ++line_num;
        test_parser.advance();
    }
}

//Loop to do the assemble process and print to file
void Assembler::assemble() {
    firstPass();
    my_parser.advance();
    while(my_parser.instructionType() != INST_TYPE::NONE) {
        if(my_parser.instructionType() == INST_TYPE::A_INSTRUCTION) {
            auto my_symbol = my_parser.symbol();
            auto symb = valid(my_symbol);
            if(symb == 0) {
                cerr << "Invalid symbol: " << my_symbol << "!" << endl;
                exit(0);
            } else if(symb == 1) {
                fileOut << to_binary(my_symbol) << endl;
            } else if(symb == -1) {
                if(symbol_table.find(my_symbol) == symbol_table.end()) {
                    symbol_table[my_symbol] = to_string(curr_symbol++);
                }
                fileOut << to_binary(symbol_table[my_symbol]) << endl;
            } else {
               fileOut << to_binary(symbol_table[my_symbol]) << endl;
            }
        } else if(my_parser.instructionType() == INST_TYPE::C_INSTRUCTION) {
            string res="";
            res += "111";
            res +=  my_decoder.comp(my_parser.comp()) + my_decoder.dest(my_parser.dest()) + my_decoder.jump(my_parser.jump());
            fileOut << res << endl;
        }
        my_parser.advance();
    }
}