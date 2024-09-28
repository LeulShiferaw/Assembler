#ifndef PARSER_H
#define PARSER_H

#include "util.h"
#include <fstream>

class Parser {
    private:
        std::ifstream file;
        INSTRUCTION curr_instr;
    public:
        Parser(const std::string &filename);
        bool hasMoreLines();
        void advance();
        INST_TYPE instructionType();
        std::string instructionStr();
        std::string symbol();
        std::string dest();
        std::string comp();
        std::string jump();
};

#endif