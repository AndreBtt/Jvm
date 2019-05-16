#pragma once

#include <iostream>
#include <vector>

#include "types.hpp"

#define CONSTANT_CLASS 7
#define CONSTANT_FIELD_REF 9
#define CONSTANT_METHOD_REF 10
#define CONSTANT_INTERFACE_METHOD_REF 11
#define CONSTANT_STRING 8
#define CONSTANT_INTEGER 3
#define CONSTANT_FLOAT 4
#define CONSTANT_LONG 5
#define CONSTANT_DOUBLE 6
#define CONSTANT_NAME_AND_TYPE 12
#define CONSTANT_UTF8 1

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
    u4 bytes;
    u4 high_bytes;
    u4 low_bytes;
    u2 utf8_length;
    std::vector <u1> utf8_bytes;
};

std::vector<Constant_pool_variables> create_constant_pool(u2, FILE*);