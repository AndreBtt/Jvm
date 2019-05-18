#include <stdio.h>

#include "class_file.hpp"

using namespace std;

string format_UTF8(u2 utf8_length, vector <u1> utf8_bytes) {
    string formated_string = "";

	for(int i = 0; i < utf8_bytes.size(); i++){
        if (!(utf8_bytes[i] & 0x80)) { 
            // 1 byte
            // check if it is 1 byte encoded:
            // if the bit 7 is 0
            // is the same as if bit 7 is not 0
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

void display_class_name(vector<Constant_pool_variables> constant_pool, u2 index) {
    // constant pool index to a CONSTANT_UTF8 where the class name is located
    u2 name_index = constant_pool[index].name_index;

    u2 utf8_length = constant_pool[name_index].utf8_length;
    vector <u1> utf8_bytes = constant_pool[name_index].utf8_bytes;

    cout << "\t // " << format_UTF8(utf8_length, utf8_bytes) << endl;
}

void display_access_flags(u2 accessFlags) {
    string flags[] = {"ACC_PUBLIC ", "ACC_FINAL ", "ACC_SUPER ", "ACC_INTERFACE ", "ACC_ABSTRACT ", "ACC_PRIVATE ", "ACC_PROTECTED ", "ACC_STATIC ", "ACC_VOLATILE ", "ACC_TRANSIENT "};
    u2 masks[] = {0x0001, 0x0010, 0x0020, 0x0200, 0x0400, 0x0002, 0x0004, 0x0008, 0x0040, 0x0080};

    for (uint8_t i = 0; i < 10; i++) {
        if ((accessFlags & masks[i]) != 0) {
            cout << flags[i];
        }
    }
    cout << endl;
}

void display_general_information(Class_file class_file) {
    
    cout << "\t Minor Version: " << class_file.min_version << endl;
    cout << endl;
    
    cout << "\t Major Version: " << class_file.major_version << endl;
    cout << endl;
    
    cout << "\t Constant pool count: " << class_file.constant_pool_length << endl;
    cout << endl;
    
    printf("\t Access Flags: (0x%.4X) ", class_file.access_flags);
    display_access_flags(class_file.access_flags);
    cout << endl;
    

    cout << "\t This class: #" << class_file.this_class;
    display_class_name(class_file.constant_pool, class_file.this_class);

    cout << endl;
}

void display_class_file (Class_file class_file) {
    cout << endl;
    cout << "Informações gerais:\n" << endl; 

    display_general_information(class_file);
}