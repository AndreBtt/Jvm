#pragma once

#include "frame.hpp"

#include <stack>

void ldc2_w(stack<Frame>*);

void dstore_1(stack<Frame>*);

void dstore_3(stack<Frame>*);

void getstatic(stack<Frame>*);

void dload(stack<Frame>*);

void dload_1(stack<Frame>*);

void dload_3(stack<Frame>*);

void dsub(stack<Frame>*);

void dadd(stack<Frame>*);

void invokevirtual(stack<Frame>*);

void dmul(stack<Frame>*);

void ddiv(stack<Frame>*);

void dneg(stack<Frame>*);

void drem(stack<Frame>*);

void return_instruction(stack<Frame>*);
 
