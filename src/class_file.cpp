#include "class_file.hpp"
#include "reader.hpp"
#include "utils.hpp"

void ClassFile::set_magic_number(FILE* file_pointer) {
    magic_number = Reader::read_u4(file_pointer);
    check_magic_number(magic_number);
}

void ClassFile::set_version(FILE* file_pointer) {
    // get min version
    min_version = Reader::read_u2(file_pointer);
    
    // get max version
    major_version = Reader::read_u2(file_pointer);
}

void ClassFile::set_constant_pool(FILE* file_pointer) {
    // get constant pool length
    constant_pool_length = Reader::read_u2(file_pointer);
    constant_pool = std::vector<constant_pool_variables>(constant_pool_length);

    // create constant pool
    for(u2 i = 1; i < constant_pool_length; i++) {
        constant_pool_variables current_variable;
        
        current_variable.tag = Reader::read_u1(file_pointer);

        switch (current_variable.tag) {
            case CONSTANT_CLASS:
                current_variable.name_index = Reader::read_u2(file_pointer);
            break;

            case CONSTANT_FIELD_REF:
            case CONSTANT_METHOD_REF:
            case CONSTANT_INTERFACE_METHOD_REF:
                current_variable.class_index = Reader::read_u2(file_pointer);
                current_variable.name_and_type_index = Reader::read_u2(file_pointer);
            break;
            
            case CONSTANT_NAME_AND_TYPE:
                current_variable.name_index = Reader::read_u2(file_pointer);
                current_variable.descriptor_index = Reader::read_u2(file_pointer);
            break;

            case CONSTANT_UTF8:
                current_variable.utf8_length = Reader::read_u2(file_pointer);
                current_variable.utf8_bytes.resize(current_variable.utf8_length);
                for (u2 i = 0; i < current_variable.utf8_length; i++) {
                    current_variable.utf8_bytes[i] = Reader::read_u1(file_pointer);
                }
            break;

            case CONSTANT_STRING:
                current_variable.string_index = Reader::read_u2(file_pointer);
            break;

            case CONSTANT_INTEGER:
            case CONSTANT_FLOAT:
                current_variable.bytes = Reader::read_u4(file_pointer);
            break;
            
            case CONSTANT_LONG:
            case CONSTANT_DOUBLE:
                current_variable.high_bytes = Reader::read_u4(file_pointer);
                current_variable.low_bytes = Reader::read_u4(file_pointer);
            break;
            default:
                std::cout << "Tag invalida no pool de constantes" << std::endl;
                exit(1);
		}

        constant_pool[i] = current_variable;
    }

}

void ClassFile::set_access_flags(FILE* file_pointer) {
    access_flags = Reader::read_u2(file_pointer);
}

void ClassFile::set_this_class(FILE* file_pointer) {
    this_class = Reader::read_u2(file_pointer);
}

void ClassFile::set_super_class(FILE* file_pointer) {
    super_class = Reader::read_u2(file_pointer);
}

void ClassFile::set_interfaces(FILE* file_pointer) {
    // get interface size
    interfaces_count = Reader::read_u2(file_pointer);

    // create each interface
    interfaces = std::vector<u2>(interfaces_count);
    for (u2 i = 0; i < interfaces_count; i++) {
        interfaces[i] = Reader::read_u2(file_pointer);
    }
}

void ClassFile::set_fields(FILE* file_pointer) {
    // get field size
    fields_count = Reader::read_u2(file_pointer);
    fields = std::vector<FieldInfo>(fields_count);

    // create each field
    for (u2 i = 0; i < fields_count; i++) {
        FieldInfo field;
        
        field.access_flags = Reader::read_u2(file_pointer);
        field.name_index = Reader::read_u2(file_pointer);
        field.descriptor_index = Reader::read_u2(file_pointer);
        field.attributes_count = Reader::read_u2(file_pointer);

        field.attributes = std::vector<AttributeInfo>(field.attributes_count);
        
        for (u2 j = 0; j < field.attributes_count; j++) {
            field.attributes[j] = get_attribute_info(file_pointer, constant_pool);
        }
        
        fields[i] = field;
    }
}

void ClassFile::set_methods(FILE* file_pointer) {
    // get method size
    methods_count = Reader::read_u2(file_pointer);
    methods = std::vector<MethodInfo>(methods_count);

    // create each method
    for (u2 i = 0; i < methods_count; i++) {
        MethodInfo method;
        
        method.access_flags = Reader::read_u2(file_pointer);
        method.name_index = Reader::read_u2(file_pointer);
        method.descriptor_index = Reader::read_u2(file_pointer);
        method.attributes_count = Reader::read_u2(file_pointer);

        method.attributes = std::vector<AttributeInfo>(method.attributes_count);
        
        for (u2 j = 0; j < method.attributes_count; j++) {
            method.attributes[j] = get_attribute_info(file_pointer, constant_pool);
        }
        
        methods[i] = method;
    }
}

void ClassFile::set_attributes(FILE* file_pointer) {
    // get attributes size
    attributes_count = Reader::read_u2(file_pointer);
    attributes = std::vector<AttributeInfo>(attributes_count);

    // create each attribute
    for (u2 i = 0; i < attributes_count; i++) {
        attributes[i] = get_attribute_info(file_pointer, constant_pool);
    }
}