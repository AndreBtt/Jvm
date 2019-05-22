#include <stdio.h>

#include "class_file.hpp"
#include "utils.hpp"

using namespace std;

string get_constant_pool_element(vector<constant_pool_variables> constant_pool, u2 index) {
    u2 tag  = constant_pool[index].tag;
    
    switch (tag) {
            case CONSTANT_CLASS:
            {
            // braces nescessary since we are declaring a vector inside a switch

                // constant pool index to a CONSTANT_UTF8 where the class name is located
                u2 name_index = constant_pool[index].name_index;

                u2 utf8_length = constant_pool[name_index].utf8_length;
                vector <u1> utf8_bytes = constant_pool[name_index].utf8_bytes;
                return format_UTF8(utf8_length, utf8_bytes);
            }

            case CONSTANT_FIELD_REF:
            case CONSTANT_METHOD_REF:
            case CONSTANT_INTERFACE_METHOD_REF:
            break;
            
            case CONSTANT_NAME_AND_TYPE:
            break;

            case CONSTANT_UTF8:
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
    string class_name = get_constant_pool_element(class_file.constant_pool, class_file.this_class);
    cout << "\t // " << class_name << endl;
    cout << endl;

    if(class_file.super_class == 0) {
        cout << "\t Super class: none" << endl;
    } else {
        cout << "\t Super class: #" << class_file.super_class;
        string super_class_name = get_constant_pool_element(class_file.constant_pool, class_file.super_class);
        cout << "\t // " << super_class_name << endl;
        cout << endl;
    }

    cout << "\t Interfaces count: " << class_file.interfaces_count << endl;
    cout << endl;

    cout << "\t Fields count: " <<  class_file.fields_count << endl;
    cout << endl;

    // cout << "\t Methods pool count: " << class_file.methods_count << endl;
    // cout << "\t Attributes pool count: " << class_file.attributes_count << endl;


    cout << endl;
}

void display_constant_pool(Class_file class_file) {

    vector<constant_pool_variables> constant_pool = class_file.constant_pool;
    
    for (int i = 1; i < class_file.constant_pool_length; i++) {
        constant_pool_variables element = constant_pool[i];
        
        cout << "#" << i << " = ";

        switch (element.tag) {
            case CONSTANT_CLASS:
            {
                cout << "Class";
                cout << "\t #" << element.name_index;
                u2 utf8_length = constant_pool[element.name_index].utf8_length;
                vector <u1> utf8_bytes = constant_pool[element.name_index].utf8_bytes;
                cout << "\t // " << format_UTF8(utf8_length, utf8_bytes) << endl;
            }
            break;

            case CONSTANT_FIELD_REF:
            case CONSTANT_METHOD_REF:
            case CONSTANT_INTERFACE_METHOD_REF:
            {
                cout << "Fieldref";
                cout << "\t #" << element.class_index << ".#" << element.name_and_type_index;
                
                u2 utf8_length = constant_pool[element.class_index].utf8_length;
                vector <u1> utf8_bytes = constant_pool[element.class_index].utf8_bytes;
                cout << "\t // " << format_UTF8(utf8_length, utf8_bytes) << ".";

                utf8_length = constant_pool[element.name_and_type_index].utf8_length;
                utf8_bytes = constant_pool[element.name_and_type_index].utf8_bytes;
                cout << "\t // " << format_UTF8(utf8_length, utf8_bytes) << endl;

            }
            break;
            
            case CONSTANT_NAME_AND_TYPE:
            break;

            case CONSTANT_UTF8:
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
        cout << endl;
    }

}

void display_class_file(Class_file class_file) {
    cout << endl;
    cout << "Informações gerais:\n" << endl; 
    display_general_information(class_file);

    cout << "Constant Pool:" << endl;
    display_constant_pool(class_file);
}