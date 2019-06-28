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

    ClassRuntime();
    ClassRuntime(ClassFile);

    ClassFile class_file;
};