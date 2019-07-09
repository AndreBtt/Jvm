#pragma once

#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>
#include <math.h>

#include "types.hpp"
#include "reader.hpp"
#include "attribute.hpp"

using namespace std;

void check_magic_number(u4);

string format_UTF8(u2, u1*);

string get_constant_pool_element(vector<Constant_pool_variables>, u2);

