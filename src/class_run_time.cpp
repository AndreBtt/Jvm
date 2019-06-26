#include "class_run_time.hpp"

ClassRuntime::ClassRuntime(ClassFile class_file) : class_file(class_file) {
    
    std::vector<FieldInfo> fields = class_file.fields;

    for (u2 i = 0; i < class_file.fields_count; i++) {
        FieldInfo field = fields[i];
        u2 static_flag = 0x0008;
        u2 final_flag = 0x0010;
        
        if ((field.access_flags & static_flag) != 0 && (field.access_flags & final_flag) == 0) { // static and not final

            string field_name = get_constant_pool_element(class_file.constant_pool, field.name_index);
            string field_descriptor = get_constant_pool_element(class_file.constant_pool, field.descriptor_index);
            
            char fieldType = field_descriptor[0];
            Variable Variable;
            
            // switch (fieldType) {
            //     case 'B':
            //         value.type = ValueType::BYTE;
            //         value.data.byteValue = 0;
            //         break;
            //     case 'C':
            //         value.type = ValueType::CHAR;
            //         value.data.charValue = 0;
            //         break;
            //     case 'D':
            //         value.type = ValueType::DOUBLE;
            //         value.data.doubleValue = 0;
            //         break;
            //     case 'F':
            //         value.type = ValueType::FLOAT;
            //         value.data.floatValue = 0;
            //         break;
            //     case 'I':
            //         value.type = ValueType::INT;
            //         value.data.intValue = 0;
            //         break;
            //     case 'J':
            //         value.type = ValueType::LONG;
            //         value.data.longValue = 0;
            //         break;
            //     case 'S':
            //         value.type = ValueType::SHORT;
            //         value.data.shortValue = 0;
            //         break;
            //     case 'Z':
            //         value.type = ValueType::BOOLEAN;
            //         value.data.charValue = false;
            //         break;
            //     default:
            //         value.type = ValueType::REFERENCE;
            //         value.data.object = NULL;
            // }
            
            // putValueIntoField(value, field_name);
        }
    }
}

// void ClassRuntime::putValueIntoField(Value value, string fieldName) {
//     _staticFields[fieldName] = value;
// }

// Value ClassRuntime::getValueFromField(string fieldName) {
//     if (_staticFields.count(fieldName) ==  0) {
//         cerr << "NoSuchFieldError" << endl;
//         exit(1);
//     }
    
//     return _staticFields[fieldName];
// }


// bool ClassRuntime::fieldExists(string fieldName) {
//     return _staticFields.count(fieldName) > 0;
// }