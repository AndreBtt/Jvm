#pragma once

#include <stdint.h>
#include <vector>

typedef uint8_t u1;
typedef uint16_t u2;
typedef uint32_t u4;

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
    // Constant value attribute
    u2 attribute_name_index;
    u4 attribute_length;
    
    // Code attribute
    u2 constant_value_index;
    u2 attributes_count;
	std::vector<attribute_info> attributes;
    Code_attribute code_info;

    // Exceptions attribute
    u2 number_of_exceptions;
	std::vector<u2>exception_index_table;

    // Inner Classes attribute
    u2 number_of_classes;
	Class *classes;

    // Source File attribute
    u2 source_file_index;

    // Line Number Table attribute
    u2 line_number_table_length;
	std::vector<Line_number_table> line_number_table;

    // Local Variable Table attribute
    u2 local_variable_table_length;
    std::vector<Local_variable_table> localVariableTable;
};

struct field_info {
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    std::vector<attribute_info> attributes;
};

