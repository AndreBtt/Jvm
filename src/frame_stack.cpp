#include "frame_stack.hpp"

void FrameStack::add_frame(Frame frame) {
    frame_stack.push(frame);
}

Frame FrameStack::get_top_frame() {
    if (!frame_stack.empty()) {
        return frame_stack.top();
    }
    
    // TODO avisar que esse valor é invalido
    return Frame();
}

u4 FrameStack::size() {
    return frame_stack.size();
}