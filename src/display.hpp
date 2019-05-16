#pragma once

#include "class_file.hpp"

std::vector<std::string> getAccessFlags(Class_file);

void display_general_information(Class_file);

void display_class_file(Class_file);
