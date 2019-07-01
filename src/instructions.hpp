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

void bipush(stack<Frame>*);

void istore_1(stack<Frame>*);

void iload_1(stack<Frame>*);

void nop(stack<Frame>*);

void aconst_null(stack<Frame>*);

void iconst_m1(stack<Frame>*);

void iconst_0(stack<Frame>*);

void iconst_1(stack<Frame>*);

void iconst_2(stack<Frame>*);

void iconst_3(stack<Frame>*);

void iconst_4(stack<Frame>*);

void iconst_5(stack<Frame>*);

void lconst_0(stack<Frame>*);

void lconst_1(stack<Frame>*);

void fconst_0(stack<Frame>*);

void fconst_1(stack<Frame>*);

void fconst_2(stack<Frame>*);

void dconst_0(stack<Frame>*);

void dconst_1(stack<Frame>*);

void sipush(stack<Frame>*);

void ldc(stack<Frame>*);

void ldc_w(stack<Frame>*);

void iload(stack<Frame>*);

void lload(stack<Frame>*);

void fload(stack<Frame>*);

void dload(stack<Frame>*);

void aload(stack<Frame>*);

void iload_0(stack<Frame>*);

void iload_2(stack<Frame>*);

void iload_3(stack<Frame>*);

void lload_0(stack<Frame>*);

void lload_1(stack<Frame>*);

void lload_2(stack<Frame>*);

void lload_3(stack<Frame>*);

void fload_0(stack<Frame>*);

void fload_1(stack<Frame>*);

void fload_2(stack<Frame>*);

void fload_3(stack<Frame>*);

void dload_0(stack<Frame>*);

void dload_1(stack<Frame>*);

void dload_2(stack<Frame>*);

void dload_3(stack<Frame>*);

void aload_0(stack<Frame>*);

void aload_1(stack<Frame>*);

void aload_2(stack<Frame>*);

void aload_3(stack<Frame>*);

void iaload(stack<Frame>*);

void laload(stack<Frame>*);

void faload(stack<Frame>*);

void daload(stack<Frame>*);

void aaload(stack<Frame>*);

void baload(stack<Frame>*);

void caload(stack<Frame>*);

void saload(stack<Frame>*);

void istore(stack<Frame>*);





 

 
