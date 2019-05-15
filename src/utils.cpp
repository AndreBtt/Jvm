#include <iostream>

#include "utils.hpp"

bool magic_number(FILE* file_pointer) {
    Reader reader;

    u4 magic_number = reader.read_u4(file_pointer);
    return magic_number == 0xcafebabe;
}

std::vector<u2> version(FILE* file_pointer) {
    Reader reader;
    std::vector<u2> version;
    
    // get min version
    version.push_back(reader.read_u2(file_pointer));
    
    // get max version
    version.push_back(reader.read_u2(file_pointer));

    return version;    
}
