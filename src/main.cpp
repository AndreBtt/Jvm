#include <iostream>
#include <vector>

#include "class_file.hpp"
#include "base_types.hpp"
#include "utils.hpp"
#include "reader.hpp"

int main(int argc, char* argv[]) {
    char* file_name = argv[1];
    FILE* file_pointer = fopen(file_name, "rb");

    // check if class has 0xcafebabe
    if(magic_number(file_pointer) == false) {
        return 0;
    }

    // this variable holds all the information about .class file
    Class_file class_file;

    // get versions
    std::vector<u2> versions = version(file_pointer);
    class_file.min_version = versions[0];
    class_file.max_version = versions[1];

    // get constant pool length and create it
    class_file.constant_pool_length = Reader::read_u2(file_pointer);
    class_file.constant_pool = create_constant_pool(class_file.constant_pool_length, file_pointer);

}