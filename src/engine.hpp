#pragma once

#include "types.hpp"
#include "class_file.hpp"
#include "class_run_time.hpp"
#include "instructions.hpp"

class Engine {

public:
    void start(ClassFile);
    
};

void execute_instruction(stack<Frame>*, u1);