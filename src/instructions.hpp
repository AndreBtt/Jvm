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

void lstore(stack<Frame>*);

void fstore(stack<Frame>*);

void dstore(stack<Frame>*);

void astore(stack<Frame>*);

void istore_0(stack<Frame>*);

void istore_2(stack<Frame>*);

void istore_3(stack<Frame>*);

void lstore_0(stack<Frame>*);

void lstore_1(stack<Frame>*);

void lstore_2(stack<Frame>*);

void lstore_3(stack<Frame>*);

void fstore_0(stack<Frame>*);

void fstore_1(stack<Frame>*);

void fstore_2(stack<Frame>*);

void fstore_3(stack<Frame>*);

void dstore_0(stack<Frame>*);

void dstore_2(stack<Frame>*);

void astore_0(stack<Frame>*);

void astore_1(stack<Frame>*);

void astore_2(stack<Frame>*);

void astore_3(stack<Frame>*);

void iastore(stack<Frame>*);

void lastore(stack<Frame>*);

void fastore(stack<Frame>*);

void dastore(stack<Frame>*);

void aastore(stack<Frame>*);

void bastore(stack<Frame>*);

void castore(stack<Frame>*);

void sastore(stack<Frame>*);

void pop(stack<Frame>*);

void pop2(stack<Frame>*);

void dup(stack<Frame>*);

void dup_x1(stack<Frame>*);

void dup_x2(stack<Frame>*);

void dup2(stack<Frame>*);

void dup2_x1(stack<Frame>*);

void dup2_x2(stack<Frame>*);

void swap(stack<Frame>*);

void iadd(stack<Frame>*);

void ladd(stack<Frame>*);

void fadd(stack<Frame>*);

void isub(stack<Frame>*);

void lsub(stack<Frame>*);

void fsub(stack<Frame>*);

void imul(stack<Frame>*);

void lmul(stack<Frame>*);

void fmul(stack<Frame>*);

void idiv(stack<Frame>*);

void ldiv_instruction(stack<Frame>*);

void fdiv(stack<Frame>*);

void irem(stack<Frame>*);

void lrem(stack<Frame>*);

void frem(stack<Frame>*);

void ineg(stack<Frame>*);

void lneg(stack<Frame>*);

void fneg(stack<Frame>*);

void ishl(stack<Frame>*);

void lshl(stack<Frame>*);

void ishr(stack<Frame>*);

void lshr(stack<Frame>*);

void iushr(stack<Frame>*);

void lushr(stack<Frame>*);

void iand(stack<Frame>*);

void land(stack<Frame>*);

void ior(stack<Frame>*);

void lor(stack<Frame>*);

void ixor(stack<Frame>*);

void lxor(stack<Frame>*);