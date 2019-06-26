#pragma once

#include "types.hpp"
#include "class_run_time.hpp"

class Frame {

public:

    Frame();

    Frame(ClassRuntime, string, string, vector<Variable>);
};