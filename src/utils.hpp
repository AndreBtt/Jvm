#pragma once

#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>
#include <math.h>

#include "types.hpp"
#include "reader.hpp"

void check_magic_number(u4);

std::string format_UTF8(u2, std::vector <u1> );

std::string get_constant_pool_element(std::vector<Constant_pool_variables>, u2);