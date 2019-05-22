#pragma once

#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>

#include "class_file.hpp"

void display_class_name(std::vector<constant_pool_variables>, u2);

std::vector<std::string> getAccessFlags(Class_file);

void display_general_information(Class_file);

void display_class_file(Class_file);
