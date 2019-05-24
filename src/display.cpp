#include "display.hpp"

void display_indentation(int indentation) {
    for(int i = 0; i < indentation; i++) {
        cout << "\t";
    }
}

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
            {
                u2 utf8_length = constant_pool[index].utf8_length;
                vector <u1> utf8_bytes = constant_pool[index].utf8_bytes;
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

void display_code_attribute(CodeAttribute attribute_info, vector<constant_pool_variables> constant_pool, int indentation) {

    CodeAttribute code = attribute_info;

    display_indentation(indentation);
    cout << "Maximum stack: " << code.max_stack << endl;
    display_indentation(indentation);
    cout << "Maximum local variables: " << code.max_locals << endl;
    display_indentation(indentation);
    cout << "Code length: " << code.code_length << endl;
    display_indentation(indentation);
    cout << "Exception table: " << endl;
    if (code.exception_table_length > 0) {
        // TODO
    } else {
        display_indentation(indentation);
        cout << "\tException table is empty" << endl;
    }


    display_indentation(indentation);
    cout << "Bytecode: " << endl;
    display_indentation(indentation+1);
    cout << "sei fazer ainda nao" << endl;

    display_indentation(indentation);
    cout << "Attributes: " << endl;
    for (u2 i = 0; i < code.attributes_count; i++) {
        display_attribute_info(code.attributes[i], constant_pool, indentation+1);
    }
}

void display_line_number_table_attribute(LineNumberTableAttribute attribute_info, vector<constant_pool_variables> constant_pool, int indentation) {
    display_indentation(indentation);        
    cout <<"\tstart_pc\tline_number" << endl;
    for (u2 i = 0; i < attribute_info.line_number_table_length; i++) {
        LineNumberTable table = attribute_info.line_number_table[i];
        display_indentation(indentation);        
        cout << "\t" << table.start_pc;
        cout << "\t\t" << table.line_number << endl;
    }
}

void display_attribute_info(AttributeInfo attribute_info, vector<constant_pool_variables> constant_pool, int indentation) {    
    string attribute_name = get_constant_pool_element(constant_pool, attribute_info.attribute_name_index);
    display_indentation(indentation);
    cout << attribute_name << endl;
    display_indentation(indentation);
    cout << "\tAttribute name index: #" << attribute_info.attribute_name_index << endl;

    if(attribute_name == "ConstantValue") {
    } else if(attribute_name == "Code") {
        display_code_attribute(attribute_info.code_attribute, constant_pool, indentation+1);
    } else if(attribute_name == "LineNumberTable") {
        display_line_number_table_attribute(attribute_info.line_number_table_attribute, constant_pool, indentation);
    }

}

void display_general_information(ClassFile class_file) {
    
    cout << "\tMinor Version: " << class_file.min_version << endl;
    cout << endl;
    
    cout << "\tMajor Version: " << class_file.major_version << endl;
    cout << endl;
    
    cout << "\tConstant pool count: " << class_file.constant_pool_length << endl;
    cout << endl;
    
    printf("\tAccess Flags: (0x%.4X) ", class_file.access_flags);
    display_access_flags(class_file.access_flags);
    cout << endl;

    string class_name = get_constant_pool_element(class_file.constant_pool, class_file.this_class);
    cout << "\tThis class: " << class_name;
    cout << "\tcp_index #" << class_file.this_class << endl;
    cout << endl;

    if(class_file.super_class == 0) {
        cout << "\tSuper class: none" << endl;
    } else {
        string super_class_name = get_constant_pool_element(class_file.constant_pool, class_file.super_class);
        cout << "\tSuper class: " << super_class_name;
        cout << "\tcp_index #" << class_file.super_class << endl;
    }
    cout << endl;

    cout << "\tInterfaces count: " << class_file.interfaces_count << endl;
    cout << endl;

    cout << "\tFields count: " <<  class_file.fields_count << endl;
    cout << endl;

    cout << "\tMethods pool count: " << class_file.methods_count << endl;
    cout << endl;
    
    cout << "\tAttributes pool count: " << class_file.attributes_count << endl;
    cout << endl;

    cout << endl;
}

void display_constant_pool(ClassFile class_file) {
    vector<constant_pool_variables> constant_pool = class_file.constant_pool;
    
    for (int i = 1; i < class_file.constant_pool_length; i++) {
        constant_pool_variables element = constant_pool[i];
        
        cout << "#" << i << " = ";

        switch (element.tag) {
            case CONSTANT_CLASS:
            {
                cout << "Class";
                cout << "\t\t #" << element.name_index;
                u2 utf8_length = constant_pool[element.name_index].utf8_length;
                vector <u1> utf8_bytes = constant_pool[element.name_index].utf8_bytes;
                cout << "\t\t // " << format_UTF8(utf8_length, utf8_bytes);
            }
            break;

            case CONSTANT_FIELD_REF:
            {
                cout << "Fieldref";
                cout << "\t\t #" << element.class_index << ".#" << element.name_and_type_index;
                
                // display class
                u2 class_index = constant_pool[element.class_index].name_index;
                u2 utf8_length = constant_pool[class_index].utf8_length;
                vector <u1> utf8_bytes = constant_pool[class_index].utf8_bytes;
                cout << "\t // " << format_UTF8(utf8_length, utf8_bytes) << ".";

                // get name and type information
                u2 name_index = constant_pool[element.name_and_type_index].name_index;
                utf8_length = constant_pool[name_index].utf8_length;
                utf8_bytes = constant_pool[name_index].utf8_bytes;
                cout << format_UTF8(utf8_length, utf8_bytes) << ":";

                u2 descriptor_index = constant_pool[element.name_and_type_index].descriptor_index;
                utf8_length = constant_pool[descriptor_index].utf8_length;
                utf8_bytes = constant_pool[descriptor_index].utf8_bytes;
                cout << format_UTF8(utf8_length, utf8_bytes);

            }
            break;

            case CONSTANT_METHOD_REF:
            {
                cout << "Methodref";
                cout << "\t\t #" << element.class_index << ".#" << element.name_and_type_index;
                
                // display class
                u2 class_index = constant_pool[element.class_index].name_index;
                u2 utf8_length = constant_pool[class_index].utf8_length;
                vector <u1> utf8_bytes = constant_pool[class_index].utf8_bytes;
                cout << "\t // " << format_UTF8(utf8_length, utf8_bytes) << ".";

                // get name and type information
                u2 name_index = constant_pool[element.name_and_type_index].name_index;
                utf8_length = constant_pool[name_index].utf8_length;
                utf8_bytes = constant_pool[name_index].utf8_bytes;
                cout << format_UTF8(utf8_length, utf8_bytes) << ":";

                u2 descriptor_index = constant_pool[element.name_and_type_index].descriptor_index;
                utf8_length = constant_pool[descriptor_index].utf8_length;
                utf8_bytes = constant_pool[descriptor_index].utf8_bytes;
                cout << format_UTF8(utf8_length, utf8_bytes);

            }
            break;

            case CONSTANT_INTERFACE_METHOD_REF:
            break;
            
            case CONSTANT_NAME_AND_TYPE:
            {
                cout << "NameAndType";
                u2 name_index = element.name_index;
                u2 descriptor_index = element.descriptor_index;

                cout << "\t #" << name_index << ":#" << descriptor_index;

                u2 utf8_length = constant_pool[name_index].utf8_length;
                vector <u1> utf8_bytes = constant_pool[name_index].utf8_bytes;
                cout << "\t // " << format_UTF8(utf8_length, utf8_bytes) << ":";

                utf8_length = constant_pool[descriptor_index].utf8_length;
                utf8_bytes = constant_pool[descriptor_index].utf8_bytes;
                cout << format_UTF8(utf8_length, utf8_bytes);
            }
            break;

            case CONSTANT_UTF8:
            {
                cout << "Utf8";
                cout << "\t\t " << format_UTF8(element.utf8_length, element.utf8_bytes);
            }
            break;

            case CONSTANT_STRING:
            {
                cout << "String";
                cout << "\t\t #" << element.string_index;


                u2 utf8_length = constant_pool[element.string_index].utf8_length;
                vector <u1> utf8_bytes = constant_pool[element.string_index].utf8_bytes;
                cout << "\t\t // " << format_UTF8(utf8_length, utf8_bytes);
            }
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

void display_interfaces(ClassFile class_file) {	
	for (u2 i = 0; i < class_file.interfaces_count; i++) {
		cout << get_constant_pool_element(class_file.constant_pool, class_file.interfaces[i]);
		
	}
}

void display_method(MethodInfo method, vector<constant_pool_variables> constant_pool, int indentation) {
    display_indentation(indentation);
    cout << "Name: " << get_constant_pool_element(constant_pool, method.name_index);;
    cout << "\tcp_index #" << method.name_index;
    cout << endl;
    
    display_indentation(indentation);
    cout << "Descriptor: " << get_constant_pool_element(constant_pool, method.descriptor_index);
    cout << "\tcp_index #" << method.descriptor_index << endl;

    display_indentation(indentation);
    printf("Access Flags: (0x%.4X) ", method.access_flags);
    display_access_flags(method.access_flags);
    
    display_indentation(indentation);
    cout << "Attributes:" << endl;
    if(method.attributes_count == 0) {
        display_indentation(indentation+1);
        cout << "Attributes is empty.";
    }
    
    for (u2 j = 0; j < method.attributes_count; j++) {
        display_attribute_info(method.attributes[j], constant_pool, indentation+1);
    }
}

void display_methods(ClassFile class_file, int indentation) {
    for (u2 i = 0; i < class_file.methods_count; i++) {
        MethodInfo method = class_file.methods[i];
        display_indentation(indentation);
        string method_name = get_constant_pool_element(class_file.constant_pool, method.name_index);
		cout << method_name << endl;
		display_method(method, class_file.constant_pool, indentation+1);
        cout << endl;
    }

}

void display_field(FieldInfo field, vector<constant_pool_variables> constant_pool, int indentation) {
    display_indentation(indentation);
    cout << "Name: " << get_constant_pool_element(constant_pool, field.name_index);
    cout << "\tcp_index #" << field.name_index << endl;

    display_indentation(indentation);
    cout << "Descriptor: " << get_constant_pool_element(constant_pool, field.descriptor_index);
    cout << "\tcp_index #" << field.descriptor_index << endl;

    display_indentation(indentation);
    printf("Access Flags: (0x%.4X) ", field.access_flags);
    display_access_flags(field.access_flags);
    
    display_indentation(indentation);
    cout << "Attributes:" << endl;
    if(field.attributes_count == 0) {
        display_indentation(indentation+1);
        cout << "Attributes is empty.";
    }
    
    for (u2 j = 0; j < field.attributes_count; j++) {
        display_attribute_info(field.attributes[j], constant_pool, indentation+1);
    }
}

void display_fields(ClassFile class_file, int indentation) {
	for (u2 i = 0; i < class_file.fields_count; i++) {
        FieldInfo field = class_file.fields[i];
        
        display_indentation(indentation);
        string field_name = get_constant_pool_element(class_file.constant_pool, field.name_index);
		cout << field_name << endl;
		display_field(field, class_file.constant_pool, indentation+1);
        cout << endl;
	}
}

void display_class_file(ClassFile class_file) {
    cout << endl;

    cout << "Informações gerais:\n" << endl; 
    display_general_information(class_file);

    cout << "Constant Pool:" << endl;
    display_constant_pool(class_file);
    cout << endl;

    cout << "Interfaces:" << endl;
    // display_interfaces(class_file);
    cout << endl;

    cout << "Fields:" << endl;
    display_fields(class_file, 1);
    cout << endl;

    cout << "Methods:" << endl;
    display_methods(class_file, 1);
    cout << endl;

}