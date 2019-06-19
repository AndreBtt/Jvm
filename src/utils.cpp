#include "utils.hpp"

std::string format_UTF8(u2 utf8_length, u1 *utf8_bytes) {
    std::string formated_string = "";

	for(int i = 0; i < utf8_length; i++){
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

// std::string get_constant_pool_element(std::vector<Constant_pool_variables> constant_pool, u2 index) {
//     u2 tag  = constant_pool[index].tag;

//     switch (tag) {
//         case CONSTANT_CLASS:
//         {
//             u2 name_index = constant_pool[index].info.class_info.name_index;

//             u2 utf8_length = constant_pool[name_index].utf8_info.length;
//             std::vector <u1> utf8_bytes = constant_pool[name_index].utf8_info.bytes;
//             return format_UTF8(utf8_length, utf8_bytes);
//         }

//         case CONSTANT_FIELD_REF:
//         {
//             Field_ref_info field_ref_info = constant_pool[index].info.field_ref_info;
//             Name_and_Type_info name_and_type_info = constant_pool[field_ref_info.name_and_type_index].info.name_and_type_info;
            
//             std::string class_name = get_constant_pool_element(constant_pool, field_ref_info.class_index);
//             std::string name = get_constant_pool_element(constant_pool, name_and_type_info.name_index);
            
//             return class_name + "." + name;
//         }
//         break;

//         case CONSTANT_METHOD_REF:
//         {
//             Method_ref_info method_ref_info = constant_pool[index].info.method_ref_info;
//             Name_and_Type_info name_and_type_info = constant_pool[method_ref_info.name_and_type_index].info.name_and_type_info;
            
//             std::string class_name = get_constant_pool_element(constant_pool, method_ref_info.class_index);
//             std::string name = get_constant_pool_element(constant_pool, name_and_type_info.name_index);
            
//             return class_name + "." + name;
//         }
//         break;

//         case CONSTANT_INTERFACE_METHOD_REF:
//         {
//             Interface_Method_ref_info interface_method_ref_info = constant_pool[index].info.interface_method_ref_info;
//             Name_and_Type_info name_and_type_info = constant_pool[interface_method_ref_info.name_and_type_index].info.name_and_type_info;
            
//             std::string class_name = get_constant_pool_element(constant_pool, interface_method_ref_info.class_index);
//             std::string name = get_constant_pool_element(constant_pool, name_and_type_info.name_index);
            
//             return class_name + "." + name;
//         }
//         break;
        
//         case CONSTANT_NAME_AND_TYPE:
//         {
//             Name_and_Type_info name_and_type_info = constant_pool[index].info.name_and_type_info;
        
//             std::string name = get_constant_pool_element(constant_pool, name_and_type_info.name_index);
//             std::string descriptor = get_constant_pool_element(constant_pool, name_and_type_info.descriptor_index);
            
//             return name + descriptor;
//         }
//         break;

//         case CONSTANT_UTF8:
//         {
//             u2 utf8_length = constant_pool[index].utf8_info.length;
//             std::vector <u1> utf8_bytes = constant_pool[index].utf8_info.bytes;
//             return format_UTF8(utf8_length, utf8_bytes);
//         }
//         break;

//         case CONSTANT_STRING:
//         {
//             String_info string_info = constant_pool[index].info.string_info;
//             return get_constant_pool_element(constant_pool, string_info.string_index);
//         }
//         break;

//         case CONSTANT_INTEGER:
//         {
//             Integer_info int_info = constant_pool[index].info.integer_info;
//             int32_t number = int_info.bytes;
//             return std::to_string(number);
//         }
//         break;

//         case CONSTANT_FLOAT:
//         {
//             Float_info float_info = constant_pool[index].info.float_info;
//             int32_t s = ((float_info.bytes >> 31) == 0) ? 1 : -1;
//             int32_t e = ((float_info.bytes >> 23) & 0xff);
//             int32_t m = (e == 0) ? (float_info.bytes & 0x7fffff) << 1 : (float_info.bytes & 0x7fffff) | 0x800000;
//             float number = s * m * pow(2, e-150);
            
//             return std::to_string(number);
//         }
//         break;
        
//         case CONSTANT_LONG:
//         {
//             Long_info long_info = constant_pool[index].info.long_info;
//             int64_t number = ((int64_t) long_info.high_bytes << 32) + long_info.low_bytes;
            
//             return std::to_string(number);
//         }
//         break;
        
//         case CONSTANT_DOUBLE:
//         {
//             Double_info double_info = constant_pool[index].info.double_info;
//             int64_t bytes = ((int64_t) double_info.high_bytes << 32) + double_info.low_bytes;
            
//             int32_t s = ((bytes >> 63) == 0) ? 1 : -1;
//             int32_t e = (int32_t)((bytes >> 52) & 0x7ffL);
//             int64_t m = (e == 0) ? (bytes & 0xfffffffffffffL) << 1 : (bytes & 0xfffffffffffffL) | 0x10000000000000L;
//             double number = s * m * pow(2, e-1075);
            
//             return std::to_string(number);
//         }
//         break;
//     }
// }