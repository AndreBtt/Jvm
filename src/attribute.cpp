#include "attribute.hpp"

ExceptionTable get_exception_table(FILE *file_pointer) {
    ExceptionTable result;
    result.start_pc = Reader::read_u2(file_pointer);
    result.end_pc = Reader::read_u2(file_pointer);
    result.handler_pc = Reader::read_u2(file_pointer);
    result.catch_type = Reader::read_u2(file_pointer);
    return result;
}

LineNumberTable get_line_number_table(FILE *file_pointer) {
    LineNumberTable result;
    result.start_pc = Reader::read_u2(file_pointer);
    result.line_number = Reader::read_u2(file_pointer);
    return result;
}

CodeAttribute get_code_attribute(FILE* file_pointer, std::vector<constant_pool_variables> constant_pool) {
    CodeAttribute result;
    result.max_stack = Reader::read_u2(file_pointer);
    result.max_locals = Reader::read_u2(file_pointer);
    
    result.code_length = Reader::read_u4(file_pointer);
    
    result.code = std::vector<u1>(result.code_length);
    for (u4 i = 0; i < result.code_length; i++) {
        result.code[i] = Reader::read_u1(file_pointer);
    }
    
    result.exception_table_length = Reader::read_u2(file_pointer);
    result.exception_table = std::vector<ExceptionTable>(result.exception_table_length);
    for (u2 i = 0; i < result.exception_table_length; i++) {
        result.exception_table[i] = get_exception_table(file_pointer);
    }
    
    result.attributes_count = Reader::read_u2(file_pointer);
    result.attributes = std::vector<AttributeInfo>(result.attributes_count);
    for (u2 i = 0; i < result.attributes_count; i++) {
        result.attributes[i] = get_attribute_info(file_pointer, constant_pool);
    }
    
    return result;
}

LineNumberTableAttribute get_line_number_table_attribute(FILE* file_pointer, std::vector<constant_pool_variables> constant_pool) {
    LineNumberTableAttribute result;
    result.line_number_table_length = Reader::read_u2(file_pointer);
    result.line_number_table = std::vector<LineNumberTable>(result.line_number_table_length);
    for (u2 i = 0; i < result.line_number_table_length; i++) {
        result.line_number_table[i] = get_line_number_table(file_pointer);
    }

    return result;
}

SourceFileAttribute get_source_file_attribute(FILE* file_pointer, std::vector<constant_pool_variables> constant_pool) {
    SourceFileAttribute result;
    result.source_file_index = Reader::read_u2(file_pointer);
    return result;
}

ConstantValueAttribute get_constant_value_attribute(FILE* file_pointer) {
    ConstantValueAttribute result;
    result.constant_value_index = Reader::read_u2(file_pointer);
    return result;
}

AttributeInfo get_attribute_info(FILE* file_pointer, std::vector<constant_pool_variables> constant_pool) {
    AttributeInfo result;
    result.attribute_name_index = Reader::read_u2(file_pointer);
    result.attribute_length = Reader::read_u4(file_pointer);

    u2 utf8_length = constant_pool[result.attribute_name_index].utf8_length;
    std::vector <u1> utf8_bytes = constant_pool[result.attribute_name_index].utf8_bytes;

    std::string attribute_name = format_UTF8(utf8_length, utf8_bytes);

    if(attribute_name == "ConstantValue") {
        result.constant_value_attribute = get_constant_value_attribute(file_pointer);
    } else if(attribute_name == "Code") {
        result.code_attribute = get_code_attribute(file_pointer, constant_pool);
    } else if(attribute_name == "LineNumberTable") {
        result.line_number_table_attribute = get_line_number_table_attribute(file_pointer, constant_pool);
    } else if(attribute_name == "SourceFile") {
        result.source_file_attribute = get_source_file_attribute(file_pointer, constant_pool);
    }

    return result;
}