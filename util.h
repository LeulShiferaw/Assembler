#ifndef UTIL_H
#define UTIL_H

#include <string>

enum class INST_TYPE {A_INSTRUCTION, C_INSTRUCTION, L_INSTRUCTION, NONE};

struct INSTRUCTION {
    INST_TYPE type;
    std::string instr;
    INSTRUCTION() {};
    INSTRUCTION(const INST_TYPE &a, const std::string &b) :type(a), instr(b) {};
};

#endif