#pragma once

#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>
#include <math.h>

#include "class_file.hpp"
#include "utils.hpp"
#include "attribute.hpp"

using namespace std;

namespace display{
    void class_file(ClassFile);
    void general_information(ClassFile);
    void access_flags(u2);
    void constant_pool(ClassFile);

    // display attributes
    void attributes(ClassFile, int);
    void attribute_info(AttributeInfo, vector<constant_pool_variables>, int);
    void code_attribute(CodeAttribute, vector<constant_pool_variables>, int);
    void line_number_table_attribute(LineNumberTableAttribute, vector<constant_pool_variables>, int);
    void source_file_attribute(SourceFileAttribute, vector<constant_pool_variables>, int);
    void constant_value_attribute(ConstantValueAttribute, vector<constant_pool_variables>, int);


    // display interfaces
    void interfaces(ClassFile);


    // display methods
    void methods(ClassFile, int);
    void method(MethodInfo, vector<constant_pool_variables>, int);


    // display fields
    void fields(ClassFile, int);
    void field(FieldInfo, vector<constant_pool_variables>, int);


    // display utils
    void indentation(int);
}