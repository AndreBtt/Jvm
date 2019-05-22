#pragma once

#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>

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

typedef uint8_t u1;
typedef uint16_t u2;
typedef uint32_t u4;

struct constant_pool_variables{
    u1 tag;

    /* declare all possible variables 
    but not all of them will be used,
    it depends on the tag value */

    // Class info --- Name and Type
    u2 name_index;
    // descriptor just to Name and Type
    u2 descriptor_index;

    // Field ref info --- Method ref info --- Interface Method ref info
    u2 class_index;
    u2 name_and_type_index;

    // String
    u2 string_index;

    // Integer --- Float
    u4 bytes;

    // Long --- Double    
    u4 high_bytes;
    u4 low_bytes;

    // UTF8
    u2 utf8_length;
    std::vector <u1> utf8_bytes;
};

struct Exception_table {
    u2 start_pc;
    u2 end_pc;
    u2 handler_pc;
    u2 catch_type;
};

struct Class {
    u2 inner_class_info_index;	     
    u2 outer_class_info_index;	     
    u2 inner_name_index;	     
    u2 inner_class_access_flags;	
};

struct Line_number_table {
    u2 start_pc;	     
    u2 line_number;
};

struct Local_variable_table {
    u2 start_pc;
    u2 length;
    u2 name_index;
    u2 descriptor_index;
    u2 index;
};

struct Code_attribute {
	u2 max_stack;
	u2 max_locals;
	u4 code_length;
	std::vector<u1> code;
	u2 exception_table_length;
    std::vector<Exception_table> exception_table;
};

struct attribute_info {
    u2 attribute_name_index;
    u4 attribute_length;
    std::vector<u1> info;
};

struct field_info {
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    std::vector<attribute_info> attributes;
};

struct method_info {
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    std::vector<attribute_info> attributes;
};