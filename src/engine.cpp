#include "engine.hpp"

void Engine::start(ClassFile class_file) {
    ClassRuntime class_run_time(class_file);
    stack<Frame> frame_stack;

    std::vector<Variable> arguments;

    frame_stack.push(Frame(class_run_time, "main", "([Ljava/lang/String;)V", arguments));

    // if (doesMethodExist(classRuntime, "<clinit>", "()V")) {
    //     stackFrame.addFrame(Frame(classRuntime, "<clinit>", "()V", arguments));
    // }

    while (frame_stack.size() > 0) {
        Frame curr_frame = frame_stack.top();
        u1 instruction_code = curr_frame.get_method_code(curr_frame.pc);
        execute_instruction(&frame_stack, instruction_code);
        // std::cout << std::hex << int(instruction_code) << std::endl;
    }
}

void execute_instruction(stack<Frame>* frame_stack, u1 instruction_code) {
    switch (instruction_code) {
        case 0x00:
            break;
        case 0x01:
            break;
        case 0x02:
            break;
        case 0x03:
            break;
        case 0x04:
            break;
        case 0x05:
            break;
        case 0x06:
            break;
        case 0x07:
            break;
        case 0x08:
            break;
        case 0x09:
            break;
        case 0x0a:
            break;
        case 0x0b:
            break;
        case 0x0c:
            break;
        case 0x0d:
            break;
        case 0x0e:
            break;
        case 0x0f:
            break;
        case 0x10:
            bipush(frame_stack);
            break;
        case 0x11:
            break;
        case 0x12:
            break;
        case 0x13:
            break;
        case 0x14:
            ldc2_w(frame_stack);
            break;
        case 0x15:
            break;
        case 0x16:
            break;
        case 0x17:
            break;
        case 0x18:
            dload(frame_stack);
            break;
        case 0x19:
            break;
        case 0x1a:
            break;
        case 0x1b:
            break;
        case 0x1c:
            break;
        case 0x1d:
            break;
        case 0x1e:
            break;
        case 0x1f:
            break;
        case 0x20:
            break;
        case 0x21:
            break;
        case 0x22:
            break;
        case 0x23:
            break;
        case 0x24:
            break;
        case 0x25:
            break;
        case 0x26:
            break;
        case 0x27:
            dload_1(frame_stack);
            break;
        case 0x28:
            break;
        case 0x29:
            dload_3(frame_stack);
            break;
        case 0x2a:
            break;
        case 0x2b:
            break;
        case 0x2c:
            break;
        case 0x2d:
            break;
        case 0x2e:
            break;
        case 0x2f:
            break;
        case 0x30:
            break;
        case 0x31:
            break;
        case 0x32:
            break;
        case 0x33:
            break;
        case 0x34:
            break;
        case 0x35:
            break;
        case 0x36:
            break;
        case 0x37:
            break;
        case 0x38:
            break;
        case 0x39:
            break;
        case 0x3a:
            break;
        case 0x3b:
            break;
        case 0x3c:
            break;
        case 0x3d:
            break;
        case 0x3e:
            break;
        case 0x3f:
            break;
        case 0x40:
            break;
        case 0x41:
            break;
        case 0x42:
            break;
        case 0x43:
            break;
        case 0x44:
            break;
        case 0x45:
            break;
        case 0x46:
            break;
        case 0x47:
            break;
        case 0x48:
            dstore_1(frame_stack);
            break;
        case 0x49:
            break;
        case 0x4a:
            dstore_3(frame_stack);
            break;
        case 0x4b:
            break;
        case 0x4c:
            break;
        case 0x4d:
            break;
        case 0x4e:
            break;
        case 0x4f:
            break;
        case 0x50:
            break;
        case 0x51:
            break;
        case 0x52:
            break;
        case 0x53:
            break;
        case 0x54:
            break;
        case 0x55:
            break;
        case 0x56:
            break;
        case 0x57:
            break;
        case 0x58:
            break;
        case 0x59:
            break;
        case 0x5a:
            break;
        case 0x5b:
            break;
        case 0x5c:
            break;
        case 0x5d:
            break;
        case 0x5e:
            break;
        case 0x5f:
            break;
        case 0x60:
            break;
        case 0x61:
            break;
        case 0x62:
            break;
        case 0x63:
            dadd(frame_stack);
            break;
        case 0x64:
            break;
        case 0x65:
            break;
        case 0x66:
            break;
        case 0x67:
            dsub(frame_stack);
            break;
        case 0x68:
            break;
        case 0x69:
            break;
        case 0x6a:
            break;
        case 0x6b:
            dmul(frame_stack);
            break;
        case 0x6c:
            break;
        case 0x6d:
            break;
        case 0x6e:
            break;
        case 0x6f:
            ddiv(frame_stack);
            break;
        case 0x70:
            break;
        case 0x71:
            break;
        case 0x72:
            break;
        case 0x73:
            drem(frame_stack); 
            break;
        case 0x74:
            break;
        case 0x75:
            break;
        case 0x76:
            break;
        case 0x77:
        	dneg(frame_stack);
            break;
        case 0x78:
            break;
        case 0x79:
            break;
        case 0x7a:
            break;
        case 0x7b:
            break;
        case 0x7c:
            break;
        case 0x7d:
            break;
        case 0x7e:
            break;
        case 0x7f:
            break;
        case 0x80:
            break;
        case 0x81:
            break;
        case 0x82:
            break;
        case 0x83:
            break;
        case 0x84:
            break;
        case 0x85:
            break;
        case 0x86:
            break;
        case 0x87:
            break;
        case 0x88:
            break;
        case 0x89:
            break;
        case 0x8a:
            break;
        case 0x8b:
            break;
        case 0x8c:
            break;
        case 0x8d:
            break;
        case 0x8e:
            break;
        case 0x8f:
            break;
        case 0x90:
            break;
        case 0x91:
            break;
        case 0x92:
            break;
        case 0x93:
            break;
        case 0x94:
            break;
        case 0x95:
            break;
        case 0x96:
            break;
        case 0x97:
            break;
        case 0x98:
            break;
        case 0x99:
            break;
        case 0x9a:
            break;
        case 0x9b:
            break;
        case 0x9c:
            break;
        case 0x9d:
            break;
        case 0x9e:
            break;
        case 0x9f:
            break;
        case 0xa0:
            break;
        case 0xa1:
            break;
        case 0xa2:
            break;
        case 0xa3:
            break;
        case 0xa4:
            break;
        case 0xa5:
            break;
        case 0xa6:
            break;
        case 0xa7:
            break;
        case 0xa8:
            break;
        case 0xa9:
            break;
        case 0xaa:
            break;
        case 0xab:
            break;
        case 0xac:
            break;
        case 0xad:
            break;
        case 0xae:
            break;
        case 0xaf:
            break;
        case 0xb0:
            break;
        case 0xb1:
            return_instruction(frame_stack);
            break;
        case 0xb2:
            getstatic(frame_stack);
            break;
        case 0xb3:
            break;
        case 0xb4:
            break;
        case 0xb5:
            break;
        case 0xb6:
            invokevirtual(frame_stack);
            break;
        case 0xb7:
            break;
        case 0xb8:
            break;
        case 0xb9:
            break;
        case 0xba:
            break;
        case 0xbb:
            break;
        case 0xbc:
            break;
        case 0xbd:
            break;
        case 0xbe:
            break;
        case 0xbf:
            break;
        case 0xc0:
            break;
        case 0xc1:
            break;
        case 0xc2:
            break;
        case 0xc3:
            break;
        case 0xc4:
            break;
        case 0xc5:
            break;
        case 0xc6:
            break;
        case 0xc7:
            break;
        case 0xc8:
            break;
        case 0xc9:
            break;
    }
}