#include "instructions.hpp"

void nop(stack<Frame>* frame_stack) {
    frame_stack->top().pc += 1;
}

void ldc2_w(stack<Frame>* frame_stack) {
    Frame curr_frame = frame_stack->top();
    
    u1 byte1 = curr_frame.get_method_code(curr_frame.pc + 1);
    u1 byte2 = curr_frame.get_method_code(curr_frame.pc + 2);
    u2 index = (byte1 << 8) | byte2;
    
    std::vector<Constant_pool_variables> constant_pool = curr_frame.class_run_time.class_file.constant_pool;
    Constant_pool_variables cp_element = constant_pool[index];

    if (cp_element.tag == CONSTANT_LONG) {
        Variable long_variable;

        u4 high_bytes = cp_element.info.long_info.high_bytes;
        u4 low_bytes = cp_element.info.long_info.low_bytes;
        
        int64_t number = ((int64_t) high_bytes << 32) + low_bytes;
        long_variable.type = VariableType::LONG;
        long_variable.data.v_long = number;

        frame_stack->top().operand_stack.push(long_variable);
        
    } else if (cp_element.tag == CONSTANT_DOUBLE) {
        Variable double_variable;

        u4 highBytes = cp_element.info.double_info.high_bytes;
        u4 lowBytes = cp_element.info.double_info.low_bytes;
        
        int64_t bytes = ((int64_t) highBytes << 32) + lowBytes;
        
        int32_t sig = ((bytes >> 63) == 0) ? 1 : -1;
        int32_t exponent = (int32_t)((bytes >> 52) & 0x7ffL);
        int64_t mantissa = (exponent == 0) ? (bytes & 0xfffffffffffffL) << 1 : (bytes & 0xfffffffffffffL) | 0x10000000000000L;
        double number = sig * mantissa * pow(2, exponent-1075);
        
        double_variable.type = VariableType::DOUBLE;
        double_variable.data.v_double = number;
        
        frame_stack->top().operand_stack.push(double_variable);
    }
    
    frame_stack->top().pc += 3;
}

void dstore_1(stack<Frame>* frame_stack) {
    Frame curr_frame = frame_stack->top();
    
    Variable variable = curr_frame.operand_stack.top();
    frame_stack->top().operand_stack.pop();

    frame_stack->top().local_variables[1] = variable;
    frame_stack->top().pc += 1;
}

void dstore_3(stack<Frame>* frame_stack) {
    Frame curr_frame = frame_stack->top();
    
    Variable variable = curr_frame.operand_stack.top();
    frame_stack->top().operand_stack.pop();

    frame_stack->top().local_variables[3] = variable;
    frame_stack->top().pc += 1;
}

void getstatic(stack<Frame>* frame_stack) {
    Frame curr_frame = frame_stack->top();

    std::vector<Constant_pool_variables> constant_pool = curr_frame.class_run_time.class_file.constant_pool;

    u1 byte1 = curr_frame.get_method_code(curr_frame.pc + 1);
    u1 byte2 = curr_frame.get_method_code(curr_frame.pc + 2);
    uint16_t field_index = (byte1 << 8) | byte2;

    Constant_pool_variables cp_field = constant_pool[field_index];

    Field_ref_info field_ref = cp_field.info.field_ref_info;

    string class_name = get_constant_pool_element(constant_pool, field_ref.class_index);

    Constant_pool_variables cp_name_and_type = constant_pool[field_ref.name_and_type_index];

    Name_and_Type_info field_name_and_type = cp_name_and_type.info.name_and_type_info;

    string field_name = get_constant_pool_element(constant_pool, field_name_and_type.name_index);
    string field_descriptor = get_constant_pool_element(constant_pool, field_name_and_type.descriptor_index);

    if (class_name == "java/lang/System" && field_descriptor == "Ljava/io/PrintStream;" ) {
        frame_stack->top().pc += 3;
        return;
    }
    
    // falta codar o else
}

void dload(stack<Frame>* frame_stack) {
    Frame curr_frame = frame_stack->top();

    u1 byte1 = curr_frame.get_method_code(curr_frame.pc + 1);
	u2 index = (u2) byte1;

    // TODO pensar como passar se o wide foi setado ou nao !!

	Variable variable = curr_frame.local_variables[index];
	frame_stack->top().operand_stack.push(variable);
    frame_stack->top().pc += 2;
}

void dload_1(stack<Frame>* frame_stack) {
    Frame curr_frame = frame_stack->top();

	Variable variable = curr_frame.local_variables[1];
	frame_stack->top().operand_stack.push(variable);

    frame_stack->top().pc += 1;
}

void dload_3(stack<Frame>* frame_stack) {
    Frame curr_frame = frame_stack->top();

	Variable variable = curr_frame.local_variables[3];
	frame_stack->top().operand_stack.push(variable);

    frame_stack->top().pc += 1;
}

void dsub(stack<Frame>* frame_stack) {
	Variable variable_2 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

	Variable variable_1 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

    Variable result;
    result.type = DOUBLE;
    result.data.v_double = (variable_1.data.v_double) - (variable_2.data.v_double);
	
    frame_stack->top().operand_stack.push(result);

    frame_stack->top().pc += 1;
}

void dadd(stack<Frame>* frame_stack) {
	Variable variable_2 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

	Variable variable_1 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

    Variable result;
    result.type = DOUBLE;
    result.data.v_double = (variable_1.data.v_double) + (variable_2.data.v_double);
	
    frame_stack->top().operand_stack.push(result);

    frame_stack->top().pc += 1;
}

void dmul(stack<Frame>* frame_stack) {
    Variable variable_2 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

	Variable variable_1 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

    Variable result;
    result.type = DOUBLE;
    result.data.v_double = (variable_1.data.v_double) * (variable_2.data.v_double);
	
    frame_stack->top().operand_stack.push(result);

    frame_stack->top().pc += 1;
}

void ddiv(stack<Frame>* frame_stack) {
    Variable variable_2 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

	Variable variable_1 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

    if(variable_2.data.v_double == 0) {
        std::cerr << "divisao por 0" << std::endl;
        exit(1);
    }

    Variable result;
    result.type = DOUBLE;
    result.data.v_double = (variable_1.data.v_double) / (variable_2.data.v_double);
	
    frame_stack->top().operand_stack.push(result);

    frame_stack->top().pc += 1;
}

void dneg(stack<Frame>* frame_stack) {
    Variable variable = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

	Variable result;
    result.type = DOUBLE;
    result.data.v_double = -(variable.data.v_double);
	
    frame_stack->top().operand_stack.push(result);
    frame_stack->top().pc += 1;
}

void drem(stack<Frame>* frame_stack) {
    Variable variable_2 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

	Variable variable_1 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

    if(variable_2.data.v_double == 0) {
        std::cerr << "divisao por 0" << std::endl;
        exit(1);
    }

    Variable result;
    result.type = DOUBLE;
    result.data.v_double = variable_1.data.v_double - ((uint64_t)(variable_1.data.v_double / variable_2.data.v_double))*variable_2.data.v_double;
	
    frame_stack->top().operand_stack.push(result);

    frame_stack->top().pc += 1;
}

void invokevirtual(stack<Frame>* frame_stack) {
    Frame curr_frame = frame_stack->top();

    std::vector<Constant_pool_variables> constant_pool = curr_frame.class_run_time.class_file.constant_pool;

    u1 byte1 = curr_frame.get_method_code(curr_frame.pc + 1);
    u1 byte2 = curr_frame.get_method_code(curr_frame.pc + 2);
    u2 method_index = (byte1 << 8) | byte2;

    Constant_pool_variables cp_method = constant_pool[method_index];
    Method_ref_info method_info = cp_method.info.method_ref_info;

    string class_name = get_constant_pool_element(constant_pool, method_info.class_index);

    Constant_pool_variables cp_name_and_type = constant_pool[method_info.name_and_type_index];
    Name_and_Type_info method_name_and_type = cp_name_and_type.info.name_and_type_info;

    string method_name = get_constant_pool_element(constant_pool, method_name_and_type.name_index);
    string method_descriptor = get_constant_pool_element(constant_pool, method_name_and_type.descriptor_index);

    if (class_name == "java/io/PrintStream" && (method_name == "print" || method_name == "println")) {
        Variable variable = frame_stack->top().operand_stack.top();
        frame_stack->top().operand_stack.pop();

        switch (variable.type) {
            case VariableType::BOOLEAN:
                printf("%s", variable.data.v_boolean == 0 ? "false" : "true");
                break;
            case VariableType::BYTE:
                printf("%d", variable.data.v_byte);
                break;
            case VariableType::CHAR:
                printf("%c", variable.data.v_char);
                break;
            case VariableType::SHORT:
                printf("%d", variable.data.v_short);
                break;
            default:
                printf("%d", variable.data.v_int);
                break;
            case VariableType::DOUBLE:
                printf("%f", variable.data.v_double);
                break;
            case VariableType::FLOAT:
                printf("%f", variable.data.v_float);
                break;
            case VariableType::LONG:
                printf("%lld", (long long) variable.data.v_long);
                break;
            case VariableType::REFERENCE:
                // TODO
                break;
        }

        if (method_name == "println") printf("\n");
    } else {
        std::cout << "nao sei implementar isso" << std::endl;
        exit(1);
    }

    frame_stack->top().pc += 3;
}

void return_instruction(stack<Frame>* frame_stack) {
    frame_stack->pop();
}

void bipush(stack<Frame>* frame_stack) {
    Frame curr_frame = frame_stack->top();

    std::vector<Constant_pool_variables> constant_pool = curr_frame.class_run_time.class_file.constant_pool;

    u1 byte = curr_frame.get_method_code(curr_frame.pc + 1);

    Variable variable;
    variable.type = VariableType::INT;
    variable.data.v_int = (u4) (u1) byte;

    frame_stack->top().operand_stack.push(variable);

    frame_stack->top().pc += 2;
}

void istore_1(stack<Frame>* frame_stack) {
    Variable variable = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

    frame_stack->top().local_variables[1] = variable;
    frame_stack->top().pc += 1;
}

void aconst_null(stack<Frame>* frame_stack) {
    Variable variable;
    variable.type = VariableType::REFERENCE;
    variable.data.object = NULL;

    frame_stack->top().operand_stack.push(variable);

    frame_stack->top().pc += 1;
}

void iconst_m1(stack<Frame>* frame_stack) {
    Variable variable;
    variable.type = VariableType::INT;
    variable.data.v_int = -1;

    frame_stack->top().operand_stack.push(variable);
    frame_stack->top().pc += 1;
}

void iconst_0(stack<Frame>* frame_stack) {
    Variable variable;
    variable.type = VariableType::INT;
    variable.data.v_int = 0;

    frame_stack->top().operand_stack.push(variable);
    frame_stack->top().pc += 1;
}

void iconst_1(stack<Frame>* frame_stack) {
    Variable variable;
    variable.type = VariableType::INT;
    variable.data.v_int = 1;

    frame_stack->top().operand_stack.push(variable);
    frame_stack->top().pc += 1;
}

void iconst_2(stack<Frame>* frame_stack) {
    Variable variable;
    variable.type = VariableType::INT;
    variable.data.v_int = 2;

    frame_stack->top().operand_stack.push(variable);
    frame_stack->top().pc += 1;
}

void iconst_3(stack<Frame>* frame_stack) {
    Variable variable;
    variable.type = VariableType::INT;
    variable.data.v_int = 3;

    frame_stack->top().operand_stack.push(variable);
    frame_stack->top().pc += 1;
}

void iconst_4(stack<Frame>* frame_stack) {
    Variable variable;
    variable.type = VariableType::INT;
    variable.data.v_int = 4;

    frame_stack->top().operand_stack.push(variable);
    frame_stack->top().pc += 1;
}

void iconst_5(stack<Frame>* frame_stack) {
    Variable variable;
    variable.type = VariableType::INT;
    variable.data.v_int = 5;

    frame_stack->top().operand_stack.push(variable);
    frame_stack->top().pc += 1;
}

void lconst_0(stack<Frame>* frame_stack) {
    Variable variable;
    variable.type = VariableType::LONG;
    variable.data.v_long = 0;

    frame_stack->top().operand_stack.push(variable);
    frame_stack->top().pc += 1;
}

void lconst_1(stack<Frame>* frame_stack) {
    Variable variable;
    variable.type = VariableType::LONG;
    variable.data.v_long = 1;

    frame_stack->top().operand_stack.push(variable);
    frame_stack->top().pc += 1;
}

void fconst_0(stack<Frame>* frame_stack) {
    Variable variable;
    variable.type = VariableType::FLOAT;
    variable.data.v_float = 0;

    frame_stack->top().operand_stack.push(variable);
    frame_stack->top().pc += 1;
}

void fconst_1(stack<Frame>* frame_stack) {
    Variable variable;
    variable.type = VariableType::FLOAT;
    variable.data.v_float = 1;

    frame_stack->top().operand_stack.push(variable);
    frame_stack->top().pc += 1;
}

void fconst_2(stack<Frame>* frame_stack) {
    Variable variable;
    variable.type = VariableType::FLOAT;
    variable.data.v_float = 2;

    frame_stack->top().operand_stack.push(variable);
    frame_stack->top().pc += 1;
}

void dconst_0(stack<Frame>* frame_stack) {
    Variable variable;
    variable.type = VariableType::DOUBLE;
    variable.data.v_float = 0;

    frame_stack->top().operand_stack.push(variable);
    frame_stack->top().pc += 1;
}

void dconst_1(stack<Frame>* frame_stack) {
    Variable variable;
    variable.type = VariableType::DOUBLE;
    variable.data.v_float = 1;

    frame_stack->top().operand_stack.push(variable);
    frame_stack->top().pc += 1;
}

void sipush(stack<Frame>* frame_stack) {
    Frame curr_frame = frame_stack->top();

    u1 byte1 = curr_frame.get_method_code(curr_frame.pc + 1);
    u1 byte2 = curr_frame.get_method_code(curr_frame.pc + 2);
    uint16_t short_value = (byte1 << 8) | byte2;

    Variable variable;
    variable.type = VariableType::INT;
    variable.data.v_int = (int32_t) (int16_t) short_value; 

    frame_stack->top().operand_stack.push(variable);

    frame_stack->top().pc += 3;
}

void ldc(stack<Frame>* frame_stack) {
    // TODO
    std::cout << "falta implementar ldc" << std::endl;
    exit(1);
}

void ldc_w(stack<Frame>* frame_stack) {
    Frame curr_frame = frame_stack->top();
    
    u1 byte1 = curr_frame.get_method_code(curr_frame.pc + 1);
    u1 byte2 = curr_frame.get_method_code(curr_frame.pc + 2);
    u2 index = (byte1 << 8) | byte2;
    
    std::vector<Constant_pool_variables> constant_pool = curr_frame.class_run_time.class_file.constant_pool;
    Constant_pool_variables cp_element = constant_pool[index];

    Variable variable;

    if (cp_element.tag == CONSTANT_STRING) {
        Constant_pool_variables utf8_variable = constant_pool[cp_element.info.string_info.string_index];
        
        u1* bytes = utf8_variable.info.utf8_info.bytes;
        string utf8_string;

        for (int i = 0; i < utf8_variable.info.utf8_info.length; i++) {
            utf8_string += char(bytes[i]);
        }
        
        // TODO
        std::cout << "preciso transformar string em objeto" << std::endl;
        exit(1);
        
    } else if (cp_element.tag == CONSTANT_INTEGER) {
        variable.type = VariableType::INT;
        variable.data.v_int = cp_element.info.integer_info.bytes;
    } else if (cp_element.tag == CONSTANT_FLOAT) {
        u4 float_bytes = cp_element.info.float_info.bytes;
        int s = ((float_bytes >> 31) == 0) ? 1 : -1;
        int e = ((float_bytes >> 23) & 0xff);
        int m = (e == 0) ? (float_bytes & 0x7fffff) << 1 : (float_bytes & 0x7fffff) | 0x800000;
        
        float number = s*m*pow(2, e-150);
        variable.type = VariableType::FLOAT;
        variable.data.v_float = number;
    }
    
    frame_stack->top().operand_stack.push(variable);
    frame_stack->top().pc += 3;
}

void iload(stack<Frame>* frame_stack) {
    Frame curr_frame = frame_stack->top();

    u1 byte1 = curr_frame.get_method_code(curr_frame.pc + 1);
	u2 index = (u2) byte1;

    // TODO pensar como passar se o wide foi setado ou nao !!

	Variable variable = curr_frame.local_variables[index];
	frame_stack->top().operand_stack.push(variable);
    frame_stack->top().pc += 2;
}

void lload(stack<Frame>* frame_stack) {
    Frame curr_frame = frame_stack->top();

    u1 byte1 = curr_frame.get_method_code(curr_frame.pc + 1);
	u2 index = (u2) byte1;

    // TODO pensar como passar se o wide foi setado ou nao !!

	Variable variable = curr_frame.local_variables[index];
	frame_stack->top().operand_stack.push(variable);
    frame_stack->top().pc += 2;
}

void fload(stack<Frame>* frame_stack) {
    Frame curr_frame = frame_stack->top();

    u1 byte1 = curr_frame.get_method_code(curr_frame.pc + 1);
	u2 index = (u2) byte1;

    // TODO pensar como passar se o wide foi setado ou nao !!

	Variable variable = curr_frame.local_variables[index];
	frame_stack->top().operand_stack.push(variable);
    frame_stack->top().pc += 2;
}

void dload(stack<Frame>* frame_stack) {
    Frame curr_frame = frame_stack->top();

    u1 byte1 = curr_frame.get_method_code(curr_frame.pc + 1);
	u2 index = (u2) byte1;

    // TODO pensar como passar se o wide foi setado ou nao !!

	Variable variable = curr_frame.local_variables[index];
	frame_stack->top().operand_stack.push(variable);
    frame_stack->top().pc += 2;
}

void aload(stack<Frame>* frame_stack) {
    Frame curr_frame = frame_stack->top();

    u1 byte1 = curr_frame.get_method_code(curr_frame.pc + 1);
	u2 index = (u2) byte1;

    // TODO pensar como passar se o wide foi setado ou nao !!

	Variable variable = curr_frame.local_variables[index];
	frame_stack->top().operand_stack.push(variable);
    frame_stack->top().pc += 2;
}

void iload_0(stack<Frame>* frame_stack) {
    Variable variable = frame_stack->top().local_variables[0];
    frame_stack->top().operand_stack.push(variable);

    frame_stack->top().pc += 1;
}

void iload_1(stack<Frame>* frame_stack) {
    Variable variable = frame_stack->top().local_variables[1];
    frame_stack->top().operand_stack.push(variable);

    frame_stack->top().pc += 1;
}

void iload_2(stack<Frame>* frame_stack) {
    Variable variable = frame_stack->top().local_variables[2];
    frame_stack->top().operand_stack.push(variable);

    frame_stack->top().pc += 1;
}

void iload_3(stack<Frame>* frame_stack) {
    Variable variable = frame_stack->top().local_variables[3];
    frame_stack->top().operand_stack.push(variable);

    frame_stack->top().pc += 1;
}

void lload_0(stack<Frame>* frame_stack) {
    Variable variable = frame_stack->top().local_variables[0];
    frame_stack->top().operand_stack.push(variable);

    frame_stack->top().pc += 1;
}

void lload_1(stack<Frame>* frame_stack) {
    Variable variable = frame_stack->top().local_variables[1];
    frame_stack->top().operand_stack.push(variable);

    frame_stack->top().pc += 1;
}

void lload_2(stack<Frame>* frame_stack) {
    Variable variable = frame_stack->top().local_variables[2];
    frame_stack->top().operand_stack.push(variable);

    frame_stack->top().pc += 1;
}

void lload_3(stack<Frame>* frame_stack) {
    Variable variable = frame_stack->top().local_variables[3];
    frame_stack->top().operand_stack.push(variable);

    frame_stack->top().pc += 1;
}

void fload_0(stack<Frame>* frame_stack) {
    Variable variable = frame_stack->top().local_variables[0];
    frame_stack->top().operand_stack.push(variable);

    frame_stack->top().pc += 1;
}

void fload_1(stack<Frame>* frame_stack) {
    Variable variable = frame_stack->top().local_variables[1];
    frame_stack->top().operand_stack.push(variable);

    frame_stack->top().pc += 1;
}

void fload_2(stack<Frame>* frame_stack) {
    Variable variable = frame_stack->top().local_variables[2];
    frame_stack->top().operand_stack.push(variable);

    frame_stack->top().pc += 1;
}

void fload_3(stack<Frame>* frame_stack) {
    Variable variable = frame_stack->top().local_variables[3];
    frame_stack->top().operand_stack.push(variable);

    frame_stack->top().pc += 1;
}

void dload_0(stack<Frame>* frame_stack) {
    Variable variable = frame_stack->top().local_variables[0];
    frame_stack->top().operand_stack.push(variable);

    frame_stack->top().pc += 1;
}

void dload_1(stack<Frame>* frame_stack) {
    Variable variable = frame_stack->top().local_variables[1];
    frame_stack->top().operand_stack.push(variable);

    frame_stack->top().pc += 1;
}

void dload_2(stack<Frame>* frame_stack) {
    Variable variable = frame_stack->top().local_variables[2];
    frame_stack->top().operand_stack.push(variable);

    frame_stack->top().pc += 1;
}

void dload_3(stack<Frame>* frame_stack) {
    Variable variable = frame_stack->top().local_variables[3];
    frame_stack->top().operand_stack.push(variable);

    frame_stack->top().pc += 1;
}

void aload_0(stack<Frame>* frame_stack) {
    Variable variable = frame_stack->top().local_variables[0];
    frame_stack->top().operand_stack.push(variable);

    frame_stack->top().pc += 1;
}

void aload_1(stack<Frame>* frame_stack) {
    Variable variable = frame_stack->top().local_variables[1];
    frame_stack->top().operand_stack.push(variable);

    frame_stack->top().pc += 1;
}

void aload_2(stack<Frame>* frame_stack) {
    Variable variable = frame_stack->top().local_variables[2];
    frame_stack->top().operand_stack.push(variable);

    frame_stack->top().pc += 1;
}

void aload_3(stack<Frame>* frame_stack) {
    Variable variable = frame_stack->top().local_variables[3];
    frame_stack->top().operand_stack.push(variable);

    frame_stack->top().pc += 1;
}

void iaload(stack<Frame>* frame_stack) {
    // TODO
    std::cout << "iaload nao implementado" << std::endl;
    exit(1);
}

void laload(stack<Frame>* frame_stack) {
    // TODO
    std::cout << "laload nao implementado" << std::endl;
    exit(1);
}

void faload(stack<Frame>* frame_stack) {
    // TODO
    std::cout << "faload nao implementado" << std::endl;
    exit(1);
}

void daload(stack<Frame>* frame_stack) {
    // TODO
    std::cout << "daload nao implementado" << std::endl;
    exit(1);
}

void aaload(stack<Frame>* frame_stack) {
    // TODO
    std::cout << "aaload nao implementado" << std::endl;
    exit(1);
}

void baload(stack<Frame>* frame_stack) {
    // TODO
    std::cout << "baload nao implementado" << std::endl;
    exit(1);
}

void caload(stack<Frame>* frame_stack) {
    // TODO
    std::cout << "caload nao implementado" << std::endl;
    exit(1);
}

void saload(stack<Frame>* frame_stack) {
    // TODO
    std::cout << "saload nao implementado" << std::endl;
    exit(1);
}

void istore(stack<Frame>* frame_stack) {
    Frame curr_frame = frame_stack->top();

	Variable variable = curr_frame.operand_stack.top(); 
    frame_stack->top().operand_stack.pop();

    u1 byte = curr_frame.get_method_code(curr_frame.pc + 1);
    u2 index = (u2) byte;

    frame_stack->top().local_variables[index] = variable;
    
    // TODO pensar como passar se o wide foi setado ou nao !!

    frame_stack->top().pc += 2;
}

void lstore(stack<Frame>* frame_stack) {
    Frame curr_frame = frame_stack->top();

	Variable variable = curr_frame.operand_stack.top(); 
    frame_stack->top().operand_stack.pop();

    u1 byte = curr_frame.get_method_code(curr_frame.pc + 1);
    u2 index = (u2) byte;

    frame_stack->top().local_variables[index] = variable;
    
    // TODO pensar como passar se o wide foi setado ou nao !!

    frame_stack->top().pc += 2;
}

void fstore(stack<Frame>* frame_stack) {
    Frame curr_frame = frame_stack->top();

	Variable variable = curr_frame.operand_stack.top(); 
    frame_stack->top().operand_stack.pop();

    u1 byte = curr_frame.get_method_code(curr_frame.pc + 1);
    u2 index = (u2) byte;

    frame_stack->top().local_variables[index] = variable;
    
    // TODO pensar como passar se o wide foi setado ou nao !!

    frame_stack->top().pc += 2;
}

void dstore(stack<Frame>* frame_stack) {
    Frame curr_frame = frame_stack->top();

	Variable variable = curr_frame.operand_stack.top(); 
    frame_stack->top().operand_stack.pop();

    u1 byte = curr_frame.get_method_code(curr_frame.pc + 1);
    u2 index = (u2) byte;

    frame_stack->top().local_variables[index] = variable;
    
    // TODO pensar como passar se o wide foi setado ou nao !!

    frame_stack->top().pc += 2;
}

void astore(stack<Frame>* frame_stack) {
    Frame curr_frame = frame_stack->top();

	Variable variable = curr_frame.operand_stack.top(); 
    frame_stack->top().operand_stack.pop();

    u1 byte = curr_frame.get_method_code(curr_frame.pc + 1);
    u2 index = (u2) byte;

    frame_stack->top().local_variables[index] = variable;
    
    // TODO pensar como passar se o wide foi setado ou nao !!

    frame_stack->top().pc += 2;
}

void istore_0(stack<Frame>* frame_stack) {
    Variable variable = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

    frame_stack->top().local_variables[0] = variable;
    frame_stack->top().pc += 1;
}

void istore_2(stack<Frame>* frame_stack) {
    Variable variable = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

    frame_stack->top().local_variables[2] = variable;
    frame_stack->top().pc += 1;
}

void istore_3(stack<Frame>* frame_stack) {
    Variable variable = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

    frame_stack->top().local_variables[3] = variable;
    frame_stack->top().pc += 1;
}

void lstore_0(stack<Frame>* frame_stack) {
    Variable variable = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

    frame_stack->top().local_variables[0] = variable;
    frame_stack->top().pc += 1;
}

void lstore_1(stack<Frame>* frame_stack) {
    Variable variable = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

    frame_stack->top().local_variables[1] = variable;
    frame_stack->top().pc += 1;
}

void lstore_2(stack<Frame>* frame_stack) {
    Variable variable = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

    frame_stack->top().local_variables[2] = variable;
    frame_stack->top().pc += 1;
}

void lstore_3(stack<Frame>* frame_stack) {
    Variable variable = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

    frame_stack->top().local_variables[3] = variable;
    frame_stack->top().pc += 1;
}

void fstore_0(stack<Frame>* frame_stack) {
    Variable variable = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

    frame_stack->top().local_variables[0] = variable;
    frame_stack->top().pc += 1;
}

void fstore_1(stack<Frame>* frame_stack) {
    Variable variable = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

    frame_stack->top().local_variables[1] = variable;
    frame_stack->top().pc += 1;
}

void fstore_2(stack<Frame>* frame_stack) {
    Variable variable = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

    frame_stack->top().local_variables[2] = variable;
    frame_stack->top().pc += 1;
}

void fstore_3(stack<Frame>* frame_stack) {
    Variable variable = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

    frame_stack->top().local_variables[3] = variable;
    frame_stack->top().pc += 1;
}

void dstore_0(stack<Frame>* frame_stack) {
    Variable variable = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

    frame_stack->top().local_variables[0] = variable;
    frame_stack->top().pc += 1;
}

void dstore_2(stack<Frame>* frame_stack) {
    Variable variable = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

    frame_stack->top().local_variables[2] = variable;
    frame_stack->top().pc += 1;
}

void astore_0(stack<Frame>* frame_stack) {
    Variable variable = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

    frame_stack->top().local_variables[0] = variable;
    frame_stack->top().pc += 1;
}

void astore_1(stack<Frame>* frame_stack) {
    Variable variable = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

    frame_stack->top().local_variables[1] = variable;
    frame_stack->top().pc += 1;
}

void astore_2(stack<Frame>* frame_stack) {
    Variable variable = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

    frame_stack->top().local_variables[2] = variable;
    frame_stack->top().pc += 1;
}

void astore_3(stack<Frame>* frame_stack) {
    Variable variable = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

    frame_stack->top().local_variables[3] = variable;
    frame_stack->top().pc += 1;
}

void iastore(stack<Frame>* frame_stack) {
    std::cout << "instrucao iastore nao implementada" << std::endl;
    exit(1);   
}

void lastore(stack<Frame>* frame_stack) {
    std::cout << "instrucao lastore nao implementada" << std::endl;
    exit(1);   
}

void fastore(stack<Frame>* frame_stack) {
    std::cout << "instrucao fastore nao implementada" << std::endl;
    exit(1);   
}

void dastore(stack<Frame>* frame_stack) {
    std::cout << "instrucao dastore nao implementada" << std::endl;
    exit(1);   
}

void aastore(stack<Frame>* frame_stack) {
    std::cout << "instrucao aastore nao implementada" << std::endl;
    exit(1);   
}

void bastore(stack<Frame>* frame_stack) {
    std::cout << "instrucao bastore nao implementada" << std::endl;
    exit(1);   
}

void castore(stack<Frame>* frame_stack) {
    std::cout << "instrucao castore nao implementada" << std::endl;
    exit(1);   
}

void sastore(stack<Frame>* frame_stack) {
    std::cout << "instrucao sastore nao implementada" << std::endl;
    exit(1);   
}

void pop(stack<Frame>* frame_stack) {
    frame_stack->top().operand_stack.pop();
    frame_stack->top().pc += 1;
}

void pop2(stack<Frame>* frame_stack) {
    frame_stack->top().operand_stack.pop();
    frame_stack->top().pc += 1;
}

void dup(stack<Frame>* frame_stack) {
    Variable top_variable = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.push(top_variable);
    
    frame_stack->top().pc += 1;
}

void dup_x1(stack<Frame>* frame_stack) {
    Variable variable_1 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();
    Variable variable_2 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();
    
    frame_stack->top().operand_stack.push(variable_1);
    frame_stack->top().operand_stack.push(variable_2);
    frame_stack->top().operand_stack.push(variable_1);
    
    frame_stack->top().pc += 1;
}

void dup_x2(stack<Frame>* frame_stack) {
    Variable variable_1 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();
    Variable variable_2 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();
    
    frame_stack->top().operand_stack.push(variable_1);
    frame_stack->top().operand_stack.push(variable_2);
    frame_stack->top().operand_stack.push(variable_1);
    
    frame_stack->top().pc += 1;
}

void dup2(stack<Frame>* frame_stack) {
    std::cout << "instrucao dup2 nao implementada" << std::endl;
    exit(1);

    // Variable variable_1 = frame_stack->top().operand_stack.top();
    // frame_stack->top().operand_stack.pop();
    // if(variable_1.type == VariableType::LONG || variable_1.type == VariableType::DOUBLE) {
    //     frame_stack->top().operand_stack.push(variable_1);
    // } else {
    //     Variable variable_2 = frame_stack->top().operand_stack.top();
    //     frame_stack->top().operand_stack.pop();
    //     frame_stack->top().operand_stack.push(variable_2);
    //     frame_stack->top().operand_stack.push(variable_1);
    // }
}

void dup2_x1(stack<Frame>* frame_stack) {
    std::cout << "instrucao dup2_x1 nao implementada" << std::endl;
    exit(1);
}

void dup2_x2(stack<Frame>* frame_stack) {
    std::cout << "instrucao dup2_x2 nao implementada" << std::endl;
    exit(1);
}

void swap(stack<Frame>* frame_stack) {
    Variable variable_1 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();
    Variable variable_2 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();
    
    frame_stack->top().operand_stack.push(variable_1);
    frame_stack->top().operand_stack.push(variable_2);
    
    frame_stack->top().pc += 1;
}

void iadd(stack<Frame>* frame_stack) {
    Variable variable_2 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

	Variable variable_1 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

    Variable result;
    result.type = INT;
    result.data.v_int = (variable_1.data.v_int) + (variable_2.data.v_int);
	
    frame_stack->top().operand_stack.push(result);

    frame_stack->top().pc += 1;
}

void ladd(stack<Frame>* frame_stack) {
    Variable variable_2 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

	Variable variable_1 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

    Variable result;
    result.type = LONG;
    result.data.v_long = (variable_1.data.v_long) + (variable_2.data.v_long);
	
    frame_stack->top().operand_stack.push(result);

    frame_stack->top().pc += 1;
}

void fadd(stack<Frame>* frame_stack) {
    Variable variable_2 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

	Variable variable_1 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

    Variable result;
    result.type = FLOAT;
    result.data.v_float = (variable_1.data.v_float) + (variable_2.data.v_float);
	
    frame_stack->top().operand_stack.push(result);

    frame_stack->top().pc += 1;
}

void isub(stack<Frame>* frame_stack) {
    Variable variable_2 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

	Variable variable_1 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

    Variable result;
    result.type = INT;
    result.data.v_int = (variable_1.data.v_int) - (variable_2.data.v_int);
	
    frame_stack->top().operand_stack.push(result);

    frame_stack->top().pc += 1;
}

void lsub(stack<Frame>* frame_stack) {
    Variable variable_2 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

	Variable variable_1 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

    Variable result;
    result.type = LONG;
    result.data.v_long = (variable_1.data.v_long) - (variable_2.data.v_long);
	
    frame_stack->top().operand_stack.push(result);

    frame_stack->top().pc += 1;
}

void fsub(stack<Frame>* frame_stack) {
    Variable variable_2 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

	Variable variable_1 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

    Variable result;
    result.type = FLOAT;
    result.data.v_float = (variable_1.data.v_float) - (variable_2.data.v_float);
	
    frame_stack->top().operand_stack.push(result);

    frame_stack->top().pc += 1;
}

void imul(stack<Frame>* frame_stack) {
    Variable variable_2 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

	Variable variable_1 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

    Variable result;
    result.type = INT;
    result.data.v_int = (variable_1.data.v_int) * (variable_2.data.v_int);
	
    frame_stack->top().operand_stack.push(result);

    frame_stack->top().pc += 1;
}

void lmul(stack<Frame>* frame_stack) {
    Variable variable_2 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

	Variable variable_1 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

    Variable result;
    result.type = LONG;
    result.data.v_long = (variable_1.data.v_long) * (variable_2.data.v_long);
	
    frame_stack->top().operand_stack.push(result);

    frame_stack->top().pc += 1;
}

void fmul(stack<Frame>* frame_stack) {
    Variable variable_2 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

	Variable variable_1 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

    Variable result;
    result.type = FLOAT;
    result.data.v_float = (variable_1.data.v_float) * (variable_2.data.v_float);
	
    frame_stack->top().operand_stack.push(result);

    frame_stack->top().pc += 1;
}

void idiv(stack<Frame>* frame_stack) {
    Variable variable_2 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

	Variable variable_1 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

    if(variable_2.data.v_int == 0) {
        std::cerr << "divisao por 0" << std::endl;
        exit(1);
    }

    Variable result;
    result.type = INT;
    result.data.v_int = (variable_1.data.v_int) / (variable_2.data.v_int);
	
    frame_stack->top().operand_stack.push(result);

    frame_stack->top().pc += 1;
}

void ldiv_instruction(stack<Frame>* frame_stack) {
    Variable variable_2 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

	Variable variable_1 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

    if(variable_2.data.v_long == 0) {
        std::cerr << "divisao por 0" << std::endl;
        exit(1);
    }

    Variable result;
    result.type = LONG;
    result.data.v_long = (variable_1.data.v_long) / (variable_2.data.v_long);
	
    frame_stack->top().operand_stack.push(result);

    frame_stack->top().pc += 1;
}

void fdiv(stack<Frame>* frame_stack) {
    Variable variable_2 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

	Variable variable_1 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

    if(variable_2.data.v_float == 0) {
        std::cerr << "divisao por 0" << std::endl;
        exit(1);
    }

    Variable result;
    result.type = FLOAT;
    result.data.v_float = (variable_1.data.v_float) / (variable_2.data.v_float);
	
    frame_stack->top().operand_stack.push(result);

    frame_stack->top().pc += 1;
}

void irem(stack<Frame>* frame_stack) {
    Variable variable_2 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

	Variable variable_1 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

    if(variable_2.data.v_int == 0) {
        std::cerr << "divisao por 0" << std::endl;
        exit(1);
    }

    Variable result;
    result.type = INT;
    result.data.v_int = (variable_1.data.v_int) % (variable_2.data.v_int);
	
    frame_stack->top().operand_stack.push(result);

    frame_stack->top().pc += 1;
}

void lrem(stack<Frame>* frame_stack) {
    Variable variable_2 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

	Variable variable_1 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

    if(variable_2.data.v_long == 0) {
        std::cerr << "divisao por 0" << std::endl;
        exit(1);
    }

    Variable result;
    result.type = LONG;
    result.data.v_long = (variable_1.data.v_long) % (variable_2.data.v_long);
	
    frame_stack->top().operand_stack.push(result);

    frame_stack->top().pc += 1;
}

void frem(stack<Frame>* frame_stack) {
    Variable variable_2 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

	Variable variable_1 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

    if(variable_2.data.v_float == 0) {
        std::cerr << "divisao por 0" << std::endl;
        exit(1);
    }

    Variable result;
    result.type = FLOAT;
    result.data.v_float = variable_1.data.v_float - ((uint64_t)(variable_1.data.v_float / variable_2.data.v_float))*variable_2.data.v_float;
	
    frame_stack->top().operand_stack.push(result);

    frame_stack->top().pc += 1;
}

void ineg(stack<Frame>* frame_stack) {
    Variable variable = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

	Variable result;
    result.type = INT;
    result.data.v_int = -(variable.data.v_int);
	
    frame_stack->top().operand_stack.push(result);
    frame_stack->top().pc += 1;
}

void lneg(stack<Frame>* frame_stack) {
    Variable variable = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

	Variable result;
    result.type = LONG;
    result.data.v_long = -(variable.data.v_long);
	
    frame_stack->top().operand_stack.push(result);
    frame_stack->top().pc += 1;
}

void fneg(stack<Frame>* frame_stack) {
    Variable variable = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

	Variable result;
    result.type = FLOAT;
    result.data.v_float = -(variable.data.v_float);
	
    frame_stack->top().operand_stack.push(result);
    frame_stack->top().pc += 1;
}

void ishl(stack<Frame>* frame_stack) {
    Variable variable_2 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

	Variable variable_1 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

    Variable result;

    variable_2.data.v_int = 0x1f & variable_2.data.v_int;
	result.type = INT;
    result.data.v_int = variable_1.data.v_int << variable_2.data.v_int;
    frame_stack->top().operand_stack.push(result);

    frame_stack->top().pc += 1;
}

void lshl(stack<Frame>* frame_stack) {
    Variable variable_2 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

	Variable variable_1 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

    Variable result;

    variable_2.data.v_long = 0x3f & variable_2.data.v_long;
	result.type = LONG;
    result.data.v_long = variable_1.data.v_long << variable_2.data.v_long;
    frame_stack->top().operand_stack.push(result);

    frame_stack->top().pc += 1;
}

void ishr(stack<Frame>* frame_stack) {
    Variable variable_2 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

	Variable variable_1 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

    Variable result;

    variable_2.data.v_int = 0x1f & variable_2.data.v_int;
	result.type = INT;
    result.data.v_int = variable_1.data.v_int >> variable_2.data.v_int;
    frame_stack->top().operand_stack.push(result);

    frame_stack->top().pc += 1;
}

void lshr(stack<Frame>* frame_stack) {
    Variable variable_2 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

	Variable variable_1 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

    Variable result;

    variable_2.data.v_int = 0x1f & variable_2.data.v_int;
	result.type = LONG;
    result.data.v_long = variable_1.data.v_long >> variable_2.data.v_long;
    frame_stack->top().operand_stack.push(result);

    frame_stack->top().pc += 1;
}

void iushr(stack<Frame>* frame_stack) {
    std::cout << "falta implementar iushr" << std::endl;
    exit(1);
}

void lushr(stack<Frame>* frame_stack) {
    std::cout << "falta implementar lushr" << std::endl;
    exit(1);
}

void iand(stack<Frame>* frame_stack) {
    Variable variable_2 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

	Variable variable_1 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

    Variable result;

    variable_2.data.v_int = 0x1f & variable_2.data.v_int;
	result.type = INT;
    result.data.v_int = variable_1.data.v_int & variable_2.data.v_int;
    frame_stack->top().operand_stack.push(result);

    frame_stack->top().pc += 1;
}

void land(stack<Frame>* frame_stack) {
    Variable variable_2 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

	Variable variable_1 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

    Variable result;

    variable_2.data.v_long = 0x1f & variable_2.data.v_long;
	result.type = LONG;
    result.data.v_long = variable_1.data.v_long & variable_2.data.v_long;
    frame_stack->top().operand_stack.push(result);

    frame_stack->top().pc += 1;
}

void ior(stack<Frame>* frame_stack) {
    Variable variable_2 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

	Variable variable_1 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

    Variable result;

    variable_2.data.v_int = 0x1f & variable_2.data.v_int;
	result.type = INT;
    result.data.v_int = variable_1.data.v_int | variable_2.data.v_int;
    frame_stack->top().operand_stack.push(result);

    frame_stack->top().pc += 1;   
}

void lor(stack<Frame>* frame_stack) {
    Variable variable_2 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

	Variable variable_1 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

    Variable result;

    variable_2.data.v_long = 0x1f & variable_2.data.v_long;
	result.type = LONG;
    result.data.v_long = variable_1.data.v_long | variable_2.data.v_long;
    frame_stack->top().operand_stack.push(result);

    frame_stack->top().pc += 1;   
}

void ixor(stack<Frame>* frame_stack) {
    Variable variable_2 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

	Variable variable_1 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

    Variable result;

    variable_2.data.v_int = 0x1f & variable_2.data.v_int;
	result.type = INT;
    result.data.v_int = variable_1.data.v_int ^ variable_2.data.v_int;
    frame_stack->top().operand_stack.push(result);

    frame_stack->top().pc += 1;   
}

void lxor(stack<Frame>* frame_stack) {
    Variable variable_2 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

	Variable variable_1 = frame_stack->top().operand_stack.top();
    frame_stack->top().operand_stack.pop();

    Variable result;

    variable_2.data.v_int = 0x1f & variable_2.data.v_int;
	result.type = INT;
    result.data.v_int = variable_1.data.v_int ^ variable_2.data.v_int;
    frame_stack->top().operand_stack.push(result);

    frame_stack->top().pc += 1;   
}