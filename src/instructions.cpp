#include "instructions.hpp"

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
    curr_frame.operand_stack.pop();

    frame_stack->top().local_variables[1] = variable;
    frame_stack->top().pc += 1;
}

void dstore_3(stack<Frame>* frame_stack) {
    Frame curr_frame = frame_stack->top();
    
    Variable variable = curr_frame.operand_stack.top();
    curr_frame.operand_stack.pop();

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
