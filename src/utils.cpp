#include "utils.hpp"

std::string format_UTF8(u2 utf8_length, std::vector <u1> utf8_bytes) {
    std::string formated_string = "";

	for(int i = 0; i < utf8_bytes.size(); i++){
        if (!(utf8_bytes[i] & 0x80)) { 
            // 1 byte
            // check if it is 1 byte encoded:
            // if the bit 7 is 0
            // is the same as if bit 7 is not 1
			formated_string += (char)utf8_bytes[i];
		} else {
			if (!(utf8_bytes[i+1] & 0x20)) { 
                // 2 bytes
                // check if it is 2 byte encoded:
                // if the bit 5 is 0
                // is the same as if the bit 5 is not 1
				formated_string += char(((utf8_bytes[i] & 0x1f) << 6) + (utf8_bytes[i+1] & 0x3f));
                i++;
			} else { 
                // 3 bytes
				formated_string += char(((utf8_bytes[i] & 0xf) << 12) + ((utf8_bytes[i+1] & 0x3f) << 6) + (utf8_bytes[i+2] & 0x3f));
				i += 2;
			}
		}
	}

    return formated_string;
}

void check_magic_number(u4 magic_number) {
    if(magic_number != 0xcafebabe) {
        std::cout << "missing cafe babe" << std::endl;
        exit(1);
    }
}

ExceptionTable get_exception_table(FILE *file_pointer) {
    ExceptionTable result;
    result.start_pc = Reader::read_u2(file_pointer);
    result.end_pc = Reader::read_u2(file_pointer);
    result.handler_pc = Reader::read_u2(file_pointer);
    result.catch_type = Reader::read_u2(file_pointer);
    return result;
}

CodeAttribute get_code_attribute(FILE* file_pointer, std::vector<constant_pool_variables> constant_pool) {
    CodeAttribute result;
    result.max_stack = Reader::read_u2(file_pointer);
    result.max_locals = Reader::read_u2(file_pointer);
    
    result.code_length = Reader::read_u4(file_pointer);
    
    result.code = std::vector<u1>(result.code_length);
    for (u4 i = 0; i < result.code_length; i++) {
        result.code[i] = Reader::read_u1(file_pointer);
    }
    
    result.exception_table_length = Reader::read_u2(file_pointer);
    result.exception_table = std::vector<ExceptionTable>(result.exception_table_length);
    for (u2 i = 0; i < result.exception_table_length; i++) {
        result.exception_table[i] = get_exception_table(file_pointer);
    }
    
    result.attributes_count = Reader::read_u2(file_pointer);
    result.attributes = std::vector<AttributeInfo>(result.attributes_count);
    for (u2 i = 0; i < result.attributes_count; i++) {
        result.attributes[i] = get_attribute_info(file_pointer, constant_pool);
    }
    
    return result;
}

AttributeInfo get_attribute_info(FILE* file_pointer, std::vector<constant_pool_variables> constant_pool) {
    AttributeInfo result;
    result.attribute_name_index = Reader::read_u2(file_pointer);
    result.attribute_length = Reader::read_u4(file_pointer);

    u2 utf8_length = constant_pool[result.attribute_name_index].utf8_length;
    std::vector <u1> utf8_bytes = constant_pool[result.attribute_name_index].utf8_bytes;

    std::string attribute_name = format_UTF8(utf8_length, utf8_bytes);

    std::cout << attribute_name << std::endl;

    if(attribute_name == "ConstantValue") {
    } else if(attribute_name == "Code") {
        result.code_attribute = get_code_attribute(file_pointer, constant_pool);
    } else if(attribute_name == "LineNumberTable") {

    }

    return result;
}