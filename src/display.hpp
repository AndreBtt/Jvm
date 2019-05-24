#pragma once

#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>

#include "class_file.hpp"
#include "utils.hpp"
#include "attribute.hpp"

using namespace std;

// display utils
string get_constant_pool_element(vector<constant_pool_variables>, u2);
void display_indentation(int);


void display_class_file(ClassFile);
void display_general_information(ClassFile);


void display_access_flags(u2);
void display_constant_pool(ClassFile);

// display attributes
void display_attribute_info(AttributeInfo, vector<constant_pool_variables>, int);
void display_code_attribute(CodeAttribute, vector<constant_pool_variables>, int);
void display_line_number_table_attribute(LineNumberTableAttribute, vector<constant_pool_variables>, int);

// display interfaces
void display_interfaces(ClassFile);

// display methods
void display_methods(ClassFile, int);
void display_method(MethodInfo, vector<constant_pool_variables>, int);

// display fields
void display_fields(ClassFile, int);
void display_field(FieldInfo, vector<constant_pool_variables>, int);



