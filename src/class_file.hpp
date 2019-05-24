#pragma once

#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>

#include "types.hpp"

class Class_file{
	public:
		u4 magic_number;

		u2 min_version;
		u2 major_version;

		u2 constant_pool_length;
		std::vector<constant_pool_variables> constant_pool;
		
		u2 access_flags;
		
		u2 this_class;
		
		u2 super_class;
		
		u2 interfaces_count;
		std::vector<u2> interfaces;
		
		u2 fields_count;
		std::vector<FieldInfo> fields;
		
		u2 methods_count;
		std::vector<MethodInfo> methods;
		
		u2 attributes_count;

		void set_magic_number(FILE*);
		void set_version(FILE*);
		void set_constant_pool(FILE*);
		void set_access_flags(FILE*);
		void set_this_class(FILE*);
		void set_super_class(FILE*);
		void set_interfaces(FILE*);
		void set_fields(FILE*);
		void set_methods(FILE*);
};