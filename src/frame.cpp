#include "frame.hpp"

Frame::Frame() {}

// Frame::Frame(ClassRuntime *classRuntime, string methodName, string methodDescriptor, vector<Value> arguments) : pc(0), _object(NULL) {
    
//     for (int i = 0; i < arguments.size(); i++) {
//         _localVariables[i] = arguments[i];
//     }
    
//     method_info *method = getMethodNamed(classRuntime, methodName, methodDescriptor);
//     assert(method != NULL);
//     _method = *method;
//     assert((_method.access_flags & 0x0008) != 0); // o método precisa ser estático
    
//     findAttributes();
// }