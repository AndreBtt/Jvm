#include <iostream>
#include "base_types.hpp"
#include "reader.hpp"

bool magic_number(char* file_name) {
    Reader reader;

    FILE* fp = fopen(file_name, "rb");
    u4 magic_number = reader.read_u4(fp);
    return magic_number == 0xcafebabe;
}