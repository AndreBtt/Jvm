#include <iostream>

#include "base_types.hpp"
#include "reader.hpp"


void read(char* file_name) {

    Reader reader;

    FILE* fp = fopen(file_name, "rb");
    u4 magic_number = reader.read_u4(fp);
    std::cout << std::hex << magic_number << std::endl;
}

int main(int argc, char* argv[]) {
    char* file_name = argv[1];
    read(file_name);
}