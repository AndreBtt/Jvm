#include "frame.hpp"

void Frame::get_method_by_name(ClassFile class_file, std::string method_name, std::string method_descriptor) {

    for (int i = 0; i < class_file.methods_count; i++) {
        MethodInfo curr_method = class_file.methods[i];
        string current_method_name = get_constant_pool_element(class_file.constant_pool, method.name_index);
        string current_method_descriptor = get_constant_pool_element(class_file.constant_pool, method.descriptor_index);
        
        if (current_method_name == method_name && current_method_descriptor == current_method_name) {
            method = curr_method;
            return;
        }
    }
}

void Frame::get_attributes() {
    std::vector<Constant_pool_variables> constant_pool = class_run_time.class_file.constant_pool;
    
    for (u2 i = 0; i < method.attributes_count; i++) {

        // busca no display como faz isso
        AttributeInfo attr = method.attributes[i];
        CONSTANT_Utf8_info attrName = constantPool[attr->attribute_name_index-1].info.utf8_info;
        
        if (Utils::compareUtf8WithString(attrName, "Code")) {
            _codeAttribute = &(attr->info.code_info);
            if (_exceptionsAttribute != NULL) break;
        } else if (Utils::compareUtf8WithString(attrName, "Exceptions")) {
            _exceptionsAttribute = &(attr->info.exceptions_info);
            if (_codeAttribute != NULL) break;
        }
    }
}

Frame::Frame() {}

Frame::Frame(ClassRuntime curr_class_run_time, string method_name, string method_descriptor, std::vector<Variable> arguments) : pc(0), class_run_time(curr_class_run_time) {
    
    for (int i = 0; i < arguments.size(); i++) {
        local_variables[i] = arguments[i];
    }
    
    ClassFile current_class = class_run_time.class_file;
    get_method_by_name(current_class, method_name, method_descriptor);
    
    get_attributes();
}

