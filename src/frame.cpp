#include "frame.hpp"

void Frame::get_method_by_name(ClassFile class_file, std::string method_name, std::string method_descriptor) {

    for (int i = 0; i < class_file.methods_count; i++) {
        MethodInfo curr_method = class_file.methods[i];
        string current_method_name = get_constant_pool_element(class_file.constant_pool, curr_method.name_index);
        // string current_method_descriptor = get_constant_pool_element(class_file.constant_pool, curr_method.descriptor_index);
        
        // if (current_method_name == method_name && current_method_descriptor == current_method_name) {
        //     method = curr_method;
        //     return;
        // }

        // a string do descriptor é a msm mas ele nao reconhece wtf ?

        if (current_method_name == method_name) {
            method = curr_method;
            return;
        }
    }
}

void Frame::get_attributes() {
    std::vector<Constant_pool_variables> constant_pool = class_run_time.class_file.constant_pool;
    
    bool code_attr_find = false;
    bool exceptions_attr_find = false;

    for (u2 i = 0; i < method.attributes_count; i++) {
        AttributeInfo attr = method.attributes[i];

        u2 utf8_length = constant_pool[attr.attribute_name_index].info.utf8_info.length;
        u1 *utf8_bytes = constant_pool[attr.attribute_name_index].info.utf8_info.bytes;

        std::string attribute_name = format_UTF8(utf8_length, utf8_bytes);

        if(attribute_name == "Code") {
            code_attribute = attr.code_attribute;
            code_attr_find = true;
            if(exceptions_attr_find) break;
        } else if(attribute_name == "Exceptions") {
            exceptions_attribute = attr.exceptions_attribute;
            exceptions_attr_find = true;
            if(code_attr_find) break;
        } 
    }
}

Frame::Frame(ClassRuntime curr_class_run_time, string method_name, string method_descriptor, std::vector<Variable> arguments) : pc(0), class_run_time(curr_class_run_time) {
    for (int i = 0; i < arguments.size(); i++) {
        local_variables[i] = arguments[i];
    }
    
    ClassFile current_class = class_run_time.class_file;
    get_method_by_name(current_class, method_name, method_descriptor);
    
    get_attributes();
}

u1 Frame::get_method_code(u4 index) {
    return code_attribute.code[index];
}

