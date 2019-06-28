#pragma once

#include <stack>
#include <iostream>
#include <cstdlib>

#include "frame.hpp"
#include "types.hpp"

using namespace std;

class FrameStack {
    
public:
    stack<Frame> frame_stack;

    void push(Frame);
    Frame top();
    void pop();
    u4 size();
};