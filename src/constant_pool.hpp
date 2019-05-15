#ifndef CONSTANT_POOL_H_
#define CONSTANT_POOL_H_

#include <iostream>
#include <vector>

#include "base_types.hpp"

#define CLASS 7
#define FIELDREF 9
#define METHODREF 10
#define INTERFACEMETHODREF 11
#define STRING 8
#define INTEGER 3
#define FLOAT 4
#define LONG 5
#define DOUBLE 6
#define NAMEANDTYPE 12
#define UTF8 1
#define INVALID 99

struct Constant_pool_variables{
    u1 tag;

    /* declare all possible variables 
    but not all of them will be used,
    it depends on the tag value */

    u2 name_index;
    u2 class_index;
    u2 name_and_type_index;
    u2 descriptor_index;
    u2 string_index;
    u4 integer_bytes;
    u4 float_bytes;
    u4 high_bytes;
    u4 low_bytes;
    u2 utf8_length;
    std::vector <u1> utf8_bytes;
};

std::vector<Constant_pool_variables> create_constant_pool(int, FILE*);

#endif