#pragma once

#include <iostream>
#include "types.hpp"

class Reader{
	public:
		static u1 read_u1(FILE *fp);
		static u2 read_u2(FILE *fp);
		static u4 read_u4(FILE *fp);
};