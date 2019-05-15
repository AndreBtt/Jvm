#ifndef UTILS_H_
#define UTILS_H_

#include <iostream>
#include <vector>

#include "base_types.hpp"
#include "reader.hpp"
#include "utils.hpp"

bool magic_number(FILE*);
std::vector<u2> version(FILE*);

#endif