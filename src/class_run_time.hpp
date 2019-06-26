#pragma once

#include "types.hpp"
#include "class_file.hpp"
#include "utils.hpp"

#include <map>
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

class ClassRuntime {

public:

    ClassRuntime(ClassFile);

    ClassFile class_file;
    map<string, Variable> static_fields;
    
    void put_variable_field(Variable, string field_name);
    Variable get_variable_field(string field_name);
    bool field_exists(string field_name);
};