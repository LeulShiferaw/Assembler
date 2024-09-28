#ifndef CODE_H
#define CODE_H

#include <string>
#include <unordered_map>

class Code {
    private:
        std::unordered_map<std::string, std::string> map_dest;
        std::unordered_map<std::string, std::string> map_comp;
        std::unordered_map<std::string, std::string> map_jump;
    public:
        Code();
        std::string dest(const std::string&);
        std::string comp(const std::string&);
        std::string jump(const std::string&);
};

#endif