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

attribute_info get_attribute_info(FILE* file_pointer) {
    attribute_info result;
    result.attribute_name_index = Reader::read_u2(file_pointer);
    result.attribute_length = Reader::read_u4(file_pointer);

    // std::string attribute_name = format_UTF8()

    // std::cout << "PRECISO TESTAR ISSO AQUI COM ALGUMA CLASSE " << result.attribute_name_index << std::endl;
    // falta pegar os bytes desse atributo
    // exit(1);

    return result;
}