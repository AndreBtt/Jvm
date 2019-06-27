#include "frame_stack.hpp"

void FrameStack::add_frame(Frame frame) {
    frame_stack.push(frame);
}

Frame FrameStack::get_top_frame() {
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