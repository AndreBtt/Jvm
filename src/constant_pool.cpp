#include "constant_pool.hpp"
#include "reader.hpp"

std::vector<Constant_pool_variables> create_constant_pool(u2 constant_pool_length, FILE* file_pointer) {
    u2 pool_size = constant_pool_length - 1;
    
    std::vector<Constant_pool_variables> constant_pool(pool_size);

    for(u2 i = 0; i < pool_size; i++) {
        Constant_pool_variables current_variable;
        
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

    return constant_pool;
}
