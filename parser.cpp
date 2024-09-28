#include "parser.h"
#include <iostream>

using namespace std;

Parser::Parser(const string &filename) {
    curr_instr.type = INST_TYPE::NONE;

    file.open(filename);
    if(!file.is_open()) {
        cerr << "File not found!" << endl;
        exit(0);
    }
}

bool Parser::hasMoreLines() {
    char c;
    while(file.get(c)) {
        if(!isspace(c)) {
            if(c == '/') {
                if(file.get(c)) {
                    if(c != '/') cerr << "Invalid character: " << c << "!" << endl;
                    while(file.get(c))  {
                        if(c == '\n') {
                            break;
                        }
                    }
                } else {
                    cerr << "Error: just a '/'!" << endl;
                }
                continue;
            }
            file.putback(c);
            return true;
        }
    }
    return false;
}

void Parser::advance() {
    if(!hasMoreLines()) {
        curr_instr.type = INST_TYPE::NONE;
        return;
    }

    char c;
    string res = "";
    while(file.get(c)) {
        if(c == '\n') {
            break;
        } else if(isspace(c)) continue;
        else if(c == '/') { //Comment
            file.putback(c);
            break;
        }
        else {
            res += c;
        }
    }
    
    curr_instr.instr = res;
    if(res[0] == '@') curr_instr.type = INST_TYPE::A_INSTRUCTION;
    else if(res[0] == '(') curr_instr.type = INST_TYPE::L_INSTRUCTION;
    else curr_instr.type = INST_TYPE::C_INSTRUCTION;
}

INST_TYPE Parser::instructionType() {
    return curr_instr.type;
}

std::string Parser::instructionStr() {
    return curr_instr.instr;
}

std::string Parser::symbol() {
    if(curr_instr.type == INST_TYPE::A_INSTRUCTION) {
        return curr_instr.instr.substr(1, curr_instr.instr.size()-1);
    } else if(curr_instr.type == INST_TYPE::L_INSTRUCTION) {
        if(curr_instr.instr.size() <= 2) {
            cerr << "Error: symbol() size <= 2!" << endl;
            return "";
        }
        if(curr_instr.instr.back() != ')') {
            cerr << "Error: L_INSTRUCTION DOESN'T END WITH ')'!" << endl;
        }
        return curr_instr.instr.substr(1, curr_instr.instr.size()-2);
    }
    return "";
}

std::string Parser::dest() {
    if(curr_instr.type == INST_TYPE::C_INSTRUCTION) {
        if(curr_instr.instr.find('=') != string::npos) {
            string res = "";
            for(auto &c : curr_instr.instr) {
                if(c == '=') return res;
                res += c;
            }
        } return "";
    }
    return "";
}

std::string Parser::comp() {
    if(curr_instr.type != INST_TYPE::C_INSTRUCTION) {
        return "";
    }

    auto equal_pos = curr_instr.instr.find('=');
    auto semi_pos = curr_instr.instr.find(';');

    if(equal_pos != string::npos) {
        if(semi_pos != string::npos) {
            if(semi_pos-equal_pos < 0) {
                cerr << "Error: ';' exists before '='!" << endl;
                return "";
            }
            return curr_instr.instr.substr(equal_pos+1, semi_pos-equal_pos-1);
        } else {
            return curr_instr.instr.substr(equal_pos+1, curr_instr.instr.size() - equal_pos - 1);
        }
    } else if(semi_pos != string::npos) {
        return curr_instr.instr.substr(0, semi_pos);
    } else return curr_instr.instr;
}

std::string Parser::jump() {
    if(curr_instr.type != INST_TYPE::C_INSTRUCTION) {
        return "";
    }

    auto semi_pos = curr_instr.instr.find(';');
    if(semi_pos != string::npos) {
        return curr_instr.instr.substr(semi_pos+1, curr_instr.instr.size()-semi_pos-1);
    } else return "";
}

