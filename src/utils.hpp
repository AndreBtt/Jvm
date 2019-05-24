#pragma once

#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>

#include "types.hpp"
#include "reader.hpp"
#include "utils.hpp"

void check_magic_number(u4);

std::string format_UTF8(u2, std::vector <u1> );

AttributeInfo get_attribute_info(FILE*, std::vector<constant_pool_variables>);
std::vector<MethodInfo> create_methods(u2, FILE*);