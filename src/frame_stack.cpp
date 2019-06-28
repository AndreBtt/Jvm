#include "frame_stack.hpp"

void FrameStack::push(Frame frame) {
    frame_stack.push(frame);
}

void FrameStack::pop() {
    frame_stack.pop();
}

Frame FrameStack::top() {
    // arrumar isso alguma hora
    // if (!frame_stack.empty()) {
    // }
    
    // // TODO avisar que esse valor é invalido
    // return Frame();

    return frame_stack.top();
}

u4 FrameStack::size() {
    return frame_stack.size();
}