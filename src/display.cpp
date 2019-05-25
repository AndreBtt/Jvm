#include "display.hpp"

void display::class_file(ClassFile class_file) {
    cout << endl;

    cout << "Informações gerais:\n" << endl;
    display::general_information(class_file);

    cout << "Constant Pool:" << endl;
    display::constant_pool(class_file);
    cout << endl;

    cout << "Interfaces:" << endl;
    display::interfaces(class_file);
    cout << endl;

    cout << "Fields:" << endl;
    display::fields(class_file, 1);
    cout << endl;

    cout << "Methods:" << endl;
    display::methods(class_file, 1);
    cout << endl;

    cout << "Attributes:" << endl;
    display::attributes(class_file, 1);
    cout << endl;
}

void display::general_information(ClassFile class_file) {
    cout << "\tMinor Version: " << class_file.min_version << endl;
    cout << endl;

    cout << "\tMajor Version: " << class_file.major_version << endl;
    cout << endl;

    cout << "\tConstant pool count: " << class_file.constant_pool_length << endl;
    cout << endl;

    printf("\tAccess Flags: (0x%.4X) ", class_file.access_flags);
    display::access_flags(class_file.access_flags);
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

void display::access_flags(u2 accessFlags) {
    string flags[] = {"ACC_PUBLIC ", "ACC_FINAL ", "ACC_SUPER ", "ACC_INTERFACE ", "ACC_ABSTRACT ", "ACC_PRIVATE ", "ACC_PROTECTED ", "ACC_STATIC ", "ACC_VOLATILE ", "ACC_TRANSIENT "};
    u2 masks[] = {0x0001, 0x0010, 0x0020, 0x0200, 0x0400, 0x0002, 0x0004, 0x0008, 0x0040, 0x0080};

    for (uint8_t i = 0; i < 10; i++) {
        if ((accessFlags & masks[i]) != 0) {
            cout << flags[i];
        }
    }
    cout << endl;
}

void display::code_attribute(CodeAttribute attribute_info, vector<constant_pool_variables> constant_pool, int indentation) {
    CodeAttribute code = attribute_info;

    display::indentation(indentation);
    cout << "Maximum stack: " << code.max_stack << endl;
    display::indentation(indentation);
    cout << "Maximum local variables: " << code.max_locals << endl;
    display::indentation(indentation);
    cout << "Code length: " << code.code_length << endl;
    display::indentation(indentation);
    cout << "Exception table: " << endl;
    if (code.exception_table_length > 0) {
        // TODO
    } else {
        display::indentation(indentation);
        cout << "\tException table is empty" << endl;
    }


    display::indentation(indentation);
    cout << "Bytecode: " << endl;
    // TODO
    display::indentation(indentation+1);
    cout << "sei fazer ainda nao" << endl;

    display::indentation(indentation);
    cout << "Attributes: " << endl;
    for (u2 i = 0; i < code.attributes_count; i++) {
        display::attribute_info(code.attributes[i], constant_pool, indentation+1);
    }
}

void display::line_number_table_attribute(LineNumberTableAttribute attribute_info, vector<constant_pool_variables> constant_pool, int indentation) {
    display::indentation(indentation);
    cout <<"\tstart_pc\tline_number" << endl;
    for (u2 i = 0; i < attribute_info.line_number_table_length; i++) {
        LineNumberTable table = attribute_info.line_number_table[i];
        display::indentation(indentation);
        cout << "\t" << table.start_pc;
        cout << "\t\t" << table.line_number << endl;
    }
}

void display::source_file_attribute(SourceFileAttribute attribute_info, vector<constant_pool_variables> constant_pool, int indentation) {
    display::indentation(indentation);
    cout << "SourceFile: " << get_constant_pool_element(constant_pool, attribute_info.source_file_index);
    cout << "\tcp_index #" << attribute_info.source_file_index << endl;
}

void display::constant_value_attribute(ConstantValueAttribute attribute_info, vector<constant_pool_variables> constant_pool, int indentation) {
    display::indentation(indentation);
    cout << "Constant value: " << get_constant_pool_element(constant_pool, attribute_info.constant_value_index);
    cout << "\tcp_index #" << attribute_info.constant_value_index << endl;
}

void display::exceptions_attribute(ExceptionsAttribute attribute_info, vector<constant_pool_variables> constant_pool, int indentation) {
    display::indentation(indentation);
    cout <<"\texception\tverbose" << endl;
    for (u2 i = 0; i < attribute_info.number_of_exceptions; i++) {
        display::indentation(indentation);
        cout << "\tcp_index #" << attribute_info.exception_index_table[i];
        cout << "\t\t" << get_constant_pool_element(constant_pool, attribute_info.exception_index_table[i]) << endl;
    }
}

void display::attribute_info(AttributeInfo attribute_info, vector<constant_pool_variables> constant_pool, int indentation) {
    string attribute_name = get_constant_pool_element(constant_pool, attribute_info.attribute_name_index);
    display::indentation(indentation);
    cout << attribute_name << endl;
    display::indentation(indentation);
    cout << "\tAttribute name index: #" << attribute_info.attribute_name_index << endl;
    display::indentation(indentation);
    cout << "\tAttribute length: " << attribute_info.attribute_length << endl;

    if(attribute_name == "ConstantValue") {
        display::constant_value_attribute(attribute_info.constant_value_attribute, constant_pool, indentation+1);
    } else if(attribute_name == "Code") {
        display::code_attribute(attribute_info.code_attribute, constant_pool, indentation+1);
    } else if(attribute_name == "LineNumberTable") {
        display::line_number_table_attribute(attribute_info.line_number_table_attribute, constant_pool, indentation+1);
    } else if(attribute_name == "SourceFile") {
        display::source_file_attribute(attribute_info.source_file_attribute, constant_pool, indentation+1);
    } else if(attribute_name == "Exceptions") {
        display::exceptions_attribute(attribute_info.exceptions_attribute, constant_pool, indentation+1);
    }

}

void display::constant_pool(ClassFile class_file) {
    vector<constant_pool_variables> constant_pool = class_file.constant_pool;

    for (int i = 1; i < class_file.constant_pool_length; i++) {
        constant_pool_variables element = constant_pool[i];

        cout << endl;
        display::indentation(1);
        cout << "#" << i << " ";

        switch (element.tag) {
            case CONSTANT_CLASS:
            {
                cout << "Class" << endl;
                display::indentation(2);
                u2 utf8_length = constant_pool[element.name_index].utf8_length;
                vector <u1> utf8_bytes = constant_pool[element.name_index].utf8_bytes;
                printf("%-15s %-30s cp_index #%d\n", "Class name: ", format_UTF8(utf8_length, utf8_bytes).c_str(), element.name_index);
            }
            break;

            case CONSTANT_FIELD_REF:
            {
                cout << "Fieldref" << endl;

                // display class
                u2 class_index = constant_pool[element.class_index].name_index;
                u2 utf8_length = constant_pool[class_index].utf8_length;
                vector <u1> utf8_bytes = constant_pool[class_index].utf8_bytes;
                display::indentation(2);
                printf("%-15s %-30s cp_index #%d\n", "Class name: ", format_UTF8(utf8_length, utf8_bytes).c_str(), element.class_index);


                // get name and type information
                u2 name_index = constant_pool[element.name_and_type_index].name_index;
                utf8_length = constant_pool[name_index].utf8_length;
                utf8_bytes = constant_pool[name_index].utf8_bytes;
                string name = format_UTF8(utf8_length, utf8_bytes);

                u2 descriptor_index = constant_pool[element.name_and_type_index].descriptor_index;
                utf8_length = constant_pool[descriptor_index].utf8_length;
                utf8_bytes = constant_pool[descriptor_index].utf8_bytes;
                name += format_UTF8(utf8_length, utf8_bytes); // descriptor

                display::indentation(2);
                printf("%-15s %-30s cp_index #%d\n", "Name and type: ", name.c_str(), element.name_and_type_index);
            }
            break;

            case CONSTANT_METHOD_REF:
            {
                printf("Methodref\n");

                // display class
                u2 class_index = constant_pool[element.class_index].name_index;
                u2 utf8_length = constant_pool[class_index].utf8_length;
                vector <u1> utf8_bytes = constant_pool[class_index].utf8_bytes;
                display::indentation(2);
                printf("%-15s %-30s cp_index #%d\n", "Class name: ", format_UTF8(utf8_length, utf8_bytes).c_str(), element.class_index);

                // get name and type information
                u2 name_index = constant_pool[element.name_and_type_index].name_index;
                utf8_length = constant_pool[name_index].utf8_length;
                utf8_bytes = constant_pool[name_index].utf8_bytes;
                string name = format_UTF8(utf8_length, utf8_bytes);

                u2 descriptor_index = constant_pool[element.name_and_type_index].descriptor_index;
                utf8_length = constant_pool[descriptor_index].utf8_length;
                utf8_bytes = constant_pool[descriptor_index].utf8_bytes;
                name += format_UTF8(utf8_length, utf8_bytes); // descriptor

                display::indentation(2);
                printf("%-15s %-30s cp_index #%d\n", "Name and type: ", name.c_str(), element.name_and_type_index);
            }
            break;

            case CONSTANT_INTERFACE_METHOD_REF:
            {
                cout << "Interface Method ref" << endl;
                u2 class_index = constant_pool[element.class_index].name_index;
                u2 utf8_length = constant_pool[class_index].utf8_length;
                vector <u1> utf8_bytes = constant_pool[class_index].utf8_bytes;
                display::indentation(2);
                printf("%-15s %-30s cp_index #%d\n", "Class name: ", format_UTF8(utf8_length, utf8_bytes).c_str(), element.class_index);

                u2 name_index = constant_pool[element.name_and_type_index].name_index;
                utf8_length = constant_pool[name_index].utf8_length;
                utf8_bytes = constant_pool[name_index].utf8_bytes;
                string name = format_UTF8(utf8_length, utf8_bytes);

                u2 descriptor_index = constant_pool[element.name_and_type_index].descriptor_index;
                utf8_length = constant_pool[descriptor_index].utf8_length;
                utf8_bytes = constant_pool[descriptor_index].utf8_bytes;
                name += format_UTF8(utf8_length, utf8_bytes); // descriptor

                display::indentation(2);
                printf("%-15s %-30s cp_index #%d\n", "Name and type: ", name.c_str(), element.name_and_type_index);
            }
            break;

            case CONSTANT_NAME_AND_TYPE:
            {
                cout << "NameAndType" << endl;
                u2 name_index = element.name_index;
                u2 descriptor_index = element.descriptor_index;

                u2 utf8_length = constant_pool[name_index].utf8_length;
                vector <u1> utf8_bytes = constant_pool[name_index].utf8_bytes;
                display::indentation(2);
                printf("%-15s %-30s cp_index #%d\n", "Name: ", format_UTF8(utf8_length, utf8_bytes).c_str(), name_index);

                utf8_length = constant_pool[descriptor_index].utf8_length;
                utf8_bytes = constant_pool[descriptor_index].utf8_bytes;
                display::indentation(2);
                printf("%-15s %-30s cp_index #%d\n", "Descriptor: ", format_UTF8(utf8_length, utf8_bytes).c_str(), name_index);
            }
            break;

            case CONSTANT_UTF8:
            {
                cout << "Utf8" << endl;
                display::indentation(2);
                cout << "Utf8 Length: \t" << element.utf8_length << endl;
                display::indentation(2);
                cout << "Value: \t\t" << format_UTF8(element.utf8_length, element.utf8_bytes) << endl;
            }
            break;

            case CONSTANT_STRING:
            {
                cout << "String" << endl;

                u2 utf8_length = constant_pool[element.string_index].utf8_length;
                vector <u1> utf8_bytes = constant_pool[element.string_index].utf8_bytes;
                display::indentation(2);
                printf("%-15s %-30s cp_index #%d\n", "String: ", format_UTF8(utf8_length, utf8_bytes).c_str(), element.string_index);
            }
            break;

            case CONSTANT_INTEGER:
            {
                cout << "Integer" << endl;
                display::indentation(2);
                printf("Bytes: \t\t0x%.8X\n", element.bytes);
                display::indentation(2);
                cout << "Integer: \t" << int32_t(element.bytes) << endl;
            }
            break;

            case CONSTANT_FLOAT:
            {
                int32_t sig = ((element.bytes >> 31) == 0) ? 1 : -1;
                int32_t exponent = ((element.bytes >> 23) & 0xff);
                int32_t mantissa = (exponent == 0) ? (element.bytes & 0x7fffff) << 1 : (element.bytes & 0x7fffff) | 0x800000;
                float number = sig * mantissa * pow(2, exponent-150);

                cout << "Float" << endl;
                display::indentation(2);
                printf("Bytes: \t\t0x%.8X\n", element.bytes);
                display::indentation(2);
                printf("Float: \t\t%f\n", number);
            }
            break;

            case CONSTANT_LONG:
            {
                int64_t number = ((int64_t) element.high_bytes << 32) + element.low_bytes;
                cout << "Long" << endl;
                display::indentation(2);
                printf("High Bytes: \t0x%.8X\n", element.high_bytes);
                display::indentation(2);
                printf("Low Bytes: \t0x%.8X\n", element.low_bytes);
                display::indentation(2);
                cout << "Long: \t\t" << number << endl;

                i++;
                cout << endl;
                display::indentation(1);
                cout << "#" << i << " Long continued" << endl;
            }
            break;

            case CONSTANT_DOUBLE:
            {
                int64_t bytes = ((int64_t) element.high_bytes << 32) + element.low_bytes;

                int32_t sig = ((bytes >> 63) == 0) ? 1 : -1;
                int32_t exponent = (int32_t)((bytes >> 52) & 0x7ffL);
                int64_t mantissa = (exponent == 0) ? (bytes & 0xfffffffffffffL) << 1 : (bytes & 0xfffffffffffffL) | 0x10000000000000L;
                double number = sig * mantissa * pow(2, exponent-1075);

                cout << "Double" << endl;
                display::indentation(2);
                printf("High Bytes: \t0x%.8X\n", element.high_bytes);
                display::indentation(2);
                printf("Low Bytes: \t0x%.8X\n", element.low_bytes);
                display::indentation(2);
                cout << "Double: \t" << number << endl;

                i++;
                cout << endl;
                display::indentation(1);
                cout << "#" << i << " Double continued" << endl;

            }
            break;
		}
    }

}

void display::interfaces(ClassFile class_file) {
	for (u2 i = 0; i < class_file.interfaces_count; i++) {
        display::indentation(1);
        cout << "Interface " << i << endl;
        display::indentation(2);
        string class_name = get_constant_pool_element(class_file.constant_pool, class_file.interfaces[i]);
		cout << "Interface: " << class_name;
        cout << "\tcp_index #" << class_file.interfaces[i] << endl;
	}
}

void display::method(MethodInfo method, vector<constant_pool_variables> constant_pool, int indentation) {
    display::indentation(indentation);
    cout << "Name: " << get_constant_pool_element(constant_pool, method.name_index);;
    cout << "\tcp_index #" << method.name_index;
    cout << endl;

    display::indentation(indentation);
    cout << "Descriptor: " << get_constant_pool_element(constant_pool, method.descriptor_index);
    cout << "\tcp_index #" << method.descriptor_index << endl;

    display::indentation(indentation);
    printf("Access Flags: (0x%.4X) ", method.access_flags);
    display::access_flags(method.access_flags);

    display::indentation(indentation);
    cout << "Attributes:" << endl;
    if(method.attributes_count == 0) {
        display::indentation(indentation+1);
        cout << "Attributes is empty.";
    }

    for (u2 j = 0; j < method.attributes_count; j++) {
        display::attribute_info(method.attributes[j], constant_pool, indentation+1);
    }
}

void display::methods(ClassFile class_file, int indentation) {
    for (u2 i = 0; i < class_file.methods_count; i++) {
        MethodInfo method = class_file.methods[i];
        display::indentation(indentation);
        string method_name = get_constant_pool_element(class_file.constant_pool, method.name_index);
		cout << method_name << endl;
		display::method(method, class_file.constant_pool, indentation+1);
        cout << endl;
    }

}

void display::field(FieldInfo field, vector<constant_pool_variables> constant_pool, int indentation) {
    display::indentation(indentation);
    cout << "Name: " << get_constant_pool_element(constant_pool, field.name_index);
    cout << "\tcp_index #" << field.name_index << endl;

    display::indentation(indentation);
    cout << "Descriptor: " << get_constant_pool_element(constant_pool, field.descriptor_index);
    cout << "\tcp_index #" << field.descriptor_index << endl;

    display::indentation(indentation);
    printf("Access Flags: (0x%.4X) ", field.access_flags);
    display::access_flags(field.access_flags);

    display::indentation(indentation);
    cout << "Attributes:" << endl;
    if(field.attributes_count == 0) {
        display::indentation(indentation+1);
        cout << "Attributes is empty.";
    }

    for (u2 j = 0; j < field.attributes_count; j++) {
        display::attribute_info(field.attributes[j], constant_pool, indentation+1);
    }
}

void display::fields(ClassFile class_file, int indentation) {
	for (u2 i = 0; i < class_file.fields_count; i++) {
        FieldInfo field = class_file.fields[i];

        display::indentation(indentation);
        string field_name = get_constant_pool_element(class_file.constant_pool, field.name_index);
		cout << field_name << endl;
		display::field(field, class_file.constant_pool, indentation+1);
        cout << endl;
	}
}

void display::attributes(ClassFile class_file, int indentation) {
    for (u2 i = 0; i < class_file.attributes_count; i++) {
        display::attribute_info(class_file.attributes[i], class_file.constant_pool, indentation);
        cout << endl;
    }
}

void display::indentation(int indentation) {
    for(int i = 0; i < indentation; i++) {
        printf("\t");
    }
}
