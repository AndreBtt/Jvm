#include "display.hpp"

void display::class_file(ClassFile class_file) {
    printf("\n");

    printf("Informações gerais:\n");
    display::general_information(class_file);

    printf("\nConstant Pool:\n");
    display::constant_pool(class_file);

    printf("\nInterfaces:\n");
    display::interfaces(class_file);

    printf("\nFields:\n");
    display::fields(class_file, 1);

    printf("\nMethods:\n");
    display::methods(class_file, 1);

    printf("\nAttributes:\n");
    display::attributes(class_file, 1);
}

void display::general_information(ClassFile class_file) {
    display::indentation(1);
    printf("%-23s %d\n", "Minor Version:", class_file.min_version);

    display::indentation(1);
    printf("%-23s %d\n", "Major Version:", class_file.major_version);

    display::indentation(1);
    printf("%-23s %d\n", "Constant pool count:", class_file.constant_pool_length);

    display::indentation(1);
    printf("%-23s (0x%.4X)\n", "Access Flags:", class_file.access_flags);
    display::indentation(2);
    display::access_flags(class_file.access_flags);
    printf("\n");

    string class_name = get_constant_pool_element(class_file.constant_pool, class_file.this_class);
    display::indentation(1);
    printf("%-23s %-30s cp_index #%d\n", "This class:", class_name.c_str(), class_file.this_class);

    display::indentation(1);
    if(class_file.super_class == 0) {
        printf("%-23s %-30s\n", "Super class:", "none");
    } else {
        string super_class_name = get_constant_pool_element(class_file.constant_pool, class_file.super_class);
        printf("%-23s %-30s cp_index #%d\n", "Super class: ", super_class_name.c_str(), class_file.super_class);
    }

    display::indentation(1);
    printf("%-23s %d\n", "Interfaces count:", class_file.interfaces_count);

    display::indentation(1);
    printf("%-23s %d\n", "Fields count:", class_file.fields_count);

    display::indentation(1);
    printf("%-23s %d\n", "Methods pool count:", class_file.methods_count);

    display::indentation(1);
    printf("%-23s %d\n", "Attributes pool count:", class_file.attributes_count);
}

void display::access_flags(u2 accessFlags) {
    string flags[] = {"ACC_PUBLIC ", "ACC_FINAL ", "ACC_SUPER ", "ACC_INTERFACE ", "ACC_ABSTRACT ", "ACC_PRIVATE ", "ACC_PROTECTED ", "ACC_STATIC ", "ACC_VOLATILE ", "ACC_TRANSIENT "};
    u2 masks[] = {0x0001, 0x0010, 0x0020, 0x0200, 0x0400, 0x0002, 0x0004, 0x0008, 0x0040, 0x0080};

    for (uint8_t i = 0; i < 10; i++) {
        if ((accessFlags & masks[i]) != 0) {
            printf("%s ", flags[i].c_str());
        }
    }
    printf("\n");
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
                printf("NameAndType\n");
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
                printf("Utf8\n");
                display::indentation(2);
                printf("%-15s %-30d\n", "Utf8 Length:", element.utf8_length);
                display::indentation(2);
                printf("%-15s %-30s\n", "Value:", format_UTF8(element.utf8_length, element.utf8_bytes).c_str());
            }
            break;

            case CONSTANT_STRING:
            {
                printf("String\n");
                u2 utf8_length = constant_pool[element.string_index].utf8_length;
                vector <u1> utf8_bytes = constant_pool[element.string_index].utf8_bytes;
                display::indentation(2);
                printf("%-15s %-30s cp_index #%d\n", "String: ", format_UTF8(utf8_length, utf8_bytes).c_str(), element.string_index);
            }
            break;

            case CONSTANT_INTEGER:
            {
                printf("Integer\n");
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

                printf("Float\n");
                display::indentation(2);
                printf("%-15s 0x%-30.8X\n", "Bytes:", element.bytes);
                display::indentation(2);
                printf("%-15s %-30f\n", "Float:", number);
            }
            break;

            case CONSTANT_LONG:
            {
                int64_t number = ((int64_t) element.high_bytes << 32) + element.low_bytes;
                printf("Long\n");
                display::indentation(2);
                printf("%-15s 0x%-30.8X\n", "High Bytes:", element.high_bytes);
                display::indentation(2);
                printf("%-15s 0x%-30.8X\n", "Low Bytes:", element.low_bytes);
                display::indentation(2);
                printf("%-15s %-30ld\n", "Long:", number);

                i++;
                display::indentation(1);
                printf("#%d Long continued\n", i);
            }
            break;

            case CONSTANT_DOUBLE:
            {
                int64_t bytes = ((int64_t) element.high_bytes << 32) + element.low_bytes;

                int32_t sig = ((bytes >> 63) == 0) ? 1 : -1;
                int32_t exponent = (int32_t)((bytes >> 52) & 0x7ffL);
                int64_t mantissa = (exponent == 0) ? (bytes & 0xfffffffffffffL) << 1 : (bytes & 0xfffffffffffffL) | 0x10000000000000L;
                double number = sig * mantissa * pow(2, exponent-1075);

                printf("Double\n");
                display::indentation(2);
                printf("%-15s 0x%-30.8X\n", "High Bytes:", element.high_bytes);
                display::indentation(2);
                printf("%-15s 0x%-30.8X\n", "Low Bytes:", element.low_bytes);
                display::indentation(2);
                printf("%-15s %-30f\n", "Double:", number);

                i++;
                printf("\n");
                display::indentation(1);
                printf("#%d Double continued\n", i);

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
    printf("%-15s %-30s cp_index #%d\n", "Name:", get_constant_pool_element(constant_pool, method.name_index).c_str(), method.name_index);

    display::indentation(indentation);
    printf("%-15s %-30s cp_index #%d\n", "Descriptor:", get_constant_pool_element(constant_pool, method.descriptor_index).c_str(), method.descriptor_index);

    display::indentation(indentation);
    printf("%-15s (0x%.4X)\n", "Access Flags:", method.access_flags);
    display::indentation(indentation+1);
    display::access_flags(method.access_flags);

    display::indentation(indentation);
    printf("%s\n", "Attributes:");
    if(method.attributes_count == 0) {
        display::indentation(indentation+1);
        printf("%s\n", "Attributes is empty.");
    }

    for (u2 j = 0; j < method.attributes_count; j++) {
        display::attribute_info(method.attributes[j], constant_pool, indentation+1);
    }
}

void display::methods(ClassFile class_file, int indentation) {
    for (u2 i = 0; i < class_file.methods_count; i++) {
        MethodInfo method = class_file.methods[i];
        string method_name = get_constant_pool_element(class_file.constant_pool, method.name_index);
        display::indentation(indentation);
		printf("%s\n", method_name.c_str());
		display::method(method, class_file.constant_pool, indentation+1);
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
        printf("\n");
	}
}

void display::attributes(ClassFile class_file, int indentation) {
    for (u2 i = 0; i < class_file.attributes_count; i++) {
        display::attribute_info(class_file.attributes[i], class_file.constant_pool, indentation);
        printf("\n");
    }
}

void display::indentation(int indentation) {
    for(int i = 0; i < indentation; i++) {
        printf("\t");
    }
}
