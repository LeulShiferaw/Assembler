#include "code.h"
#include <iostream>

using namespace std;

Code::Code() {
    //Initiailze map for dest
    map_dest["M"] = "001";
    map_dest["D"] = "010";
    map_dest["DM"] = "011";
    map_dest["MD"] = "011";
    map_dest["A"] = "100";
    map_dest["AM"] = "101";
    map_dest["MA"] = "101";
    map_dest["AD"] = "110";
    map_dest["DA"] = "110";
    map_dest["ADM"] = "111";
    map_dest["AMD"] = "111";
    map_dest["MAD"] = "111";
    map_dest["MDA"] = "111";
    map_dest["DAM"] = "111";
    map_dest["DMA"] = "111";

    //Initialize map for comp
    map_comp["0"] = "0101010";
    map_comp["1"] = "0111111";
    map_comp["-1"] = "0111010";
    map_comp["D"] = "0001100";
    map_comp["A"] = "0110000";
    map_comp["M"] = "1110000";
    map_comp["!D"] = "0001101";
    map_comp["!A"] = "0110001";
    map_comp["!M"] = "1110001";
    map_comp["-D"] = "0001111";
    map_comp["-A"] = "0110011";
    map_comp["-M"] = "1110011";
    map_comp["D+1"] = "0011111";
    map_comp["A+1"] = "0110111";
    map_comp["M+1"] = "1110111";
    map_comp["D-1"] = "0001110";
    map_comp["A-1"] = "0110010";
    map_comp["M-1"] = "1110010";
    map_comp["D+A"] = "0000010";
    map_comp["D+M"] = "1000010";
    map_comp["D-A"] = "0010011";
    map_comp["D-M"] = "1010011";
    map_comp["A-D"] = "0000111";
    map_comp["M-D"] = "1000111";
    map_comp["D&A"] = "0000000";
    map_comp["A&D"] = "0000000";
    map_comp["D&M"] = "1000000";
    map_comp["M&D"] = "1000000";
    map_comp["D|A"] = "0010101";
    map_comp["A|D"] = "0010101";
    map_comp["D|M"] = "1010101";
    map_comp["M|D"] = "1010101";

    //Initiailze map for jump
    map_jump["JGT"] = "001";
    map_jump["JEQ"] = "010";
    map_jump["JGE"] = "011";
    map_jump["JLT"] = "100";
    map_jump["JNE"] = "101";
    map_jump["JLE"] = "110";
    map_jump["JMP"] = "111";
}

string Code::dest(const string &dest_str) {
    if(dest_str == "") return "000";

    if(map_dest.find(dest_str) == map_dest.end()) {
        cerr << "Error: " << dest_str << " not found in map_dest!" << endl;
        return ""; 
    }

    return map_dest[dest_str];
}

string Code::comp(const string& comp_str) {
    if(map_comp.find(comp_str) == map_comp.end()) {
        cerr << "Error: " << comp_str << " not found in map_comp!" << endl;
        return "";
    }

    return map_comp[comp_str];
}

string Code::jump(const string& jump_str) {
    if(jump_str == "") return "000";

    if(map_jump.find(jump_str) == map_jump.end()) {
        cerr << "Error: " << jump_str << " not found in map_jump!" << endl;
        return "";
    }

    return map_jump[jump_str];
}