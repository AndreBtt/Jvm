#pragma once

#include "types.hpp"
#include "constant_pool.hpp"

class Class_file{
	public:
		u4 magic_number;

		u2 min_version;
		u2 major_version;

		u2 constant_pool_length;
		std::vector<Constant_pool_variables> constant_pool;
		
		u2 access_flags;
		
		u2 this_class;
		
		u2 super_class;
		
		u2 interfaces_count;
		std::vector<u2> interfaces;
		
		u2 fields_count;
		std::vector<field_info> fields;
		
		u2 methods_count;
		
		u2 attributes_count;
};