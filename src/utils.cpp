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

std::string get_constant_pool_element(std::vector<constant_pool_variables> constant_pool, u2 index) {
    u2 tag  = constant_pool[index].tag;

    switch (tag) {
            case CONSTANT_CLASS:
            {
            // braces nescessary since we are declaring a vector inside a switch

                // constant pool index to a CONSTANT_UTF8 where the class name is located
                u2 name_index = constant_pool[index].name_index;

                u2 utf8_length = constant_pool[name_index].utf8_length;
                std::vector <u1> utf8_bytes = constant_pool[name_index].utf8_bytes;
                return format_UTF8(utf8_length, utf8_bytes);
            }

            case CONSTANT_FIELD_REF:
            case CONSTANT_METHOD_REF:
            case CONSTANT_INTERFACE_METHOD_REF:
            break;
            
            case CONSTANT_NAME_AND_TYPE:
            break;

            case CONSTANT_UTF8:
            {
                u2 utf8_length = constant_pool[index].utf8_length;
                std::vector <u1> utf8_bytes = constant_pool[index].utf8_bytes;
                return format_UTF8(utf8_length, utf8_bytes);
            }
            break;

            case CONSTANT_STRING:
            break;

            case CONSTANT_INTEGER:
            case CONSTANT_FLOAT:
            break;
            
            case CONSTANT_LONG:
            case CONSTANT_DOUBLE:
            break;
            
    }
    
}