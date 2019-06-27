#pragma once

#include <map>

#include "types.hpp"
#include "class_run_time.hpp"
#include "utils.hpp"

class Frame {

public:

    Frame();
    Frame(ClassRuntime, string, string, vector<Variable>);

    u4 pc;
    MethodInfo method;
    map<u4, Variable> local_variables;
    ClassRuntime class_run_time;
    CodeAttribute code_attribute;
    ExceptionsAttribute exceptions_attribute;

private:

    void get_method_by_name(ClassFile, std::string, std::string);
    void get_attributes();

};