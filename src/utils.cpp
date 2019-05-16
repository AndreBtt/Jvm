#include <iostream>

#include "utils.hpp"

bool magic_number(FILE* file_pointer) {
    u4 magic_number = Reader::read_u4(file_pointer);
    return magic_number == 0xcafebabe;
}

std::vector<u2> version(FILE* file_pointer) {
    std::vector<u2> version;
    
    // get min version
    version.push_back(Reader::read_u2(file_pointer));
    
    // get max version
    version.push_back(Reader::read_u2(file_pointer));

    return version;    
}

std::vector<u2> create_interfaces(u2 interface_size, FILE* file_pointer) {
    std::vector<u2> interface(interface_size);
    for (u2 i = 0; i < interface_size; i++) {
        interface[i] = Reader::read_u2(file_pointer);
    }
    return interface;
}