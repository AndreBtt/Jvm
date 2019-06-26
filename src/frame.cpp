#include "frame.hpp"

MethodInfo get_method_by_name(ClassFile class_file, std::string method_name, std::string method_descriptor) {
    
    MethodInfo method;

    for (int i = 0; i < class_file.methods_count; i++) {
        method = class_file.methods[i];
        string current_method_name = get_constant_pool_element(class_file.constant_pool, method.name_index);
        string current_method_descriptor = get_constant_pool_element(class_file.constant_pool, method.descriptor_index);
        
        if (current_method_name == method_name && current_method_descriptor == current_method_name) {
            break;
        }
    }

    return method;
}

Frame::Frame() {}

Frame::Frame(ClassRuntime class_run_time, string method_name, string method_descriptor, std::vector<Variable> arguments) : pc(0) {
    
    for (int i = 0; i < arguments.size(); i++) {
        local_variables[i] = arguments[i];
    }
    
    ClassFile current_class = class_run_time.class_file;
    method = get_method_by_name(current_class, method_name, method_descriptor);
    
    // findAttributes();
}

