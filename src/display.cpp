#include <stdio.h>

#include "class_file.hpp"

using namespace std;

vector<string> getAccessFlags(u2 accessFlags) {
    string flags[] = {"public ", "final ", "super ", "interface ", "abstract ", "private ", "protected ", "static ", "volatile ", "transient "};
    u2 masks[] = {0x0001, 0x0010, 0x0020, 0x0200, 0x0400, 0x0002, 0x0004, 0x0008, 0x0040, 0x0080};
    vector<string> access_flags;

    for (uint8_t i = 0; i < 10; i++) {
        if ((accessFlags & masks[i]) != 0) {
            access_flags.push_back(flags[i]);
        }
    }
    
    return access_flags;
}

void display_general_information(Class_file class_file) {
    
    cout << "\t Minor Version: \t\t" << class_file.min_version << endl;
    cout << "\t Major Version: \t\t" << class_file.major_version << endl;
    cout << "\t Constant pool count: \t\t" << class_file.constant_pool_length << endl;
    printf("\t Access Flags: \t\t\t0x%.4X ", class_file.access_flags);
    vector<string> flags = getAccessFlags(class_file.access_flags);
    for(int i = 0; i < flags.size(); i++) {
        cout << flags[i];
    }
    cout << endl;

    cout << endl;
}

void display_class_file (Class_file class_file) {
    cout << endl;
    cout << "Informações gerais:\n" << endl; 

    display_general_information(class_file);
}