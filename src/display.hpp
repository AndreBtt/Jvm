#pragma once

#include "class_file.hpp"

void format_UTF8(u2, std::vector <u1>);

void display_class_name(std::vector<Constant_pool_variables>, u2);

std::vector<std::string> getAccessFlags(Class_file);

void display_general_information(Class_file);

void display_class_file(Class_file);
