#pragma once

#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>

#include "class_file.hpp"

void display_class_name(std::vector<constant_pool_variables>, u2);

std::vector<std::string> getAccessFlags(ClassFile);

void display_general_information(ClassFile);

void display_class_file(ClassFile);
