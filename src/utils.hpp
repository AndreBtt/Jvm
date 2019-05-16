#pragma once

#include <iostream>
#include <vector>

#include "types.hpp"
#include "reader.hpp"
#include "utils.hpp"

bool magic_number(FILE*);
std::vector<u2> version(FILE*);

std::vector<u2> create_interfaces(u2 ,FILE*);