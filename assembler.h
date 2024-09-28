#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "code.h"
#include "parser.h"
#include <string>
#include <fstream>
#include <unordered_map>
 
class Assembler {
    private:
        Code my_decoder;
        Parser my_parser;
        std::ofstream fileOut;
        std::string to_binary(const std::string&);
        std::string file_name;
        void firstPass();
        std::unordered_map<std::string, std::string> symbol_table;
        int curr_symbol = 16;
    public:
        Assembler(const std::string&);
        void assemble();
};

#endif