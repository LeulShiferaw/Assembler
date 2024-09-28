#include "assembler.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
    if(argc != 2) {
        cerr << "Usage: assem ProgName.asm!" << endl;
        return 0;
    }

    Assembler my_assemb(argv[1]);
    my_assemb.assemble();
    return 0;
}
