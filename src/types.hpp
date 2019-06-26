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

class Object;

enum VariableType {
    BOOLEAN,
    BYTE,
    CHAR,
    SHORT,
    INT,
    FLOAT,
    LONG,
    DOUBLE,
    RETURN_ADDR,
    REFERENCE,
    PADDING // usado quando o Value anterior (em uma lista) ou o Value abaixo (em uma pilha) é um long/double
};

struct Variable {
    VariableType printType; // usado para printar o valor de maneira correta (somente para int, short, byte, boolean)
    VariableType type;
    union {
        bool booleanValue;
        int8_t byteValue;
        uint8_t charValue;
        int16_t shortValue;
        int32_t intValue;
        float floatValue;
        int64_t longValue;
        double doubleValue;
        u4 returnAddress;
        Object *object;
    } data;
};

struct Class_info {
	u2 name_index;
};

struct Field_ref_info {
    u2 class_index;
    u2 name_and_type_index;
};

struct Method_ref_info {
    u2 class_index;
    u2 name_and_type_index;
};

struct Interface_Method_ref_info {
    u2 class_index;
    u2 name_and_type_index;
};

struct String_info {
    u2 string_index;
};

struct Integer_info {
    u4 bytes;
};

struct Float_info {
    u4 bytes;
};

struct Long_info {
    u4 high_bytes;
    u4 low_bytes;
};

struct Double_info {
    u4 high_bytes;
    u4 low_bytes;
};

struct Name_and_Type_info {
	u2 name_index;
	u2 descriptor_index;
};

struct Utf8_info {
    u2 length;
    u1 *bytes;
};

struct Constant_pool_variables {
    u1 tag;
    union {
        Class_info class_info;
        Field_ref_info field_ref_info;
        Method_ref_info method_ref_info;
        Interface_Method_ref_info interface_method_ref_info;
        String_info string_info;
        Integer_info integer_info;
        Float_info float_info;
        Long_info long_info;
        Double_info double_info;
        Name_and_Type_info name_and_type_info;
        Utf8_info utf8_info;
    } info;
};

// declare here since some attributes will use it inside of their declarations
typedef struct AttributeInfo AttributeInfo;

struct ExceptionTable {
    u2 start_pc;
    u2 end_pc;
    u2 handler_pc;
    u2 catch_type;
};

struct LineNumberTable {
    u2 start_pc;
    u2 line_number;
};

struct ExceptionsAttribute {
    u2 number_of_exceptions;
    std::vector<u2> exception_index_table;
};

struct LineNumberTableAttribute {
    u2 attribute_name_index;
    u4 attribute_length;
    u2 line_number_table_length;
    std::vector<LineNumberTable> line_number_table;
};

struct CodeAttribute {
	u2 max_stack;
	u2 max_locals;
	u4 code_length;
	std::vector<u1> code;
	u2 exception_table_length;
    std::vector<ExceptionTable> exception_table;
    u2 attributes_count;
    std::vector<AttributeInfo> attributes;
};

struct SourceFileAttribute {
  	u2 source_file_index;
};

struct ConstantValueAttribute {
    u2 constant_value_index;
};

struct StackMapFrame {

};

struct StackMapTableAttribute {
    u2 number_of_entries;
    std::vector<StackMapFrame> entries;
};

struct AttributeInfo {
    u2 attribute_name_index;
    u4 attribute_length;

    CodeAttribute code_attribute;
    LineNumberTableAttribute line_number_table_attribute;
    SourceFileAttribute source_file_attribute;
    ConstantValueAttribute constant_value_attribute;
    ExceptionsAttribute exceptions_attribute;
    StackMapTableAttribute stack_map_table_attribute;
};

struct FieldInfo {
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    std::vector<AttributeInfo> attributes;
};

struct MethodInfo {
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    std::vector<AttributeInfo> attributes;
};

