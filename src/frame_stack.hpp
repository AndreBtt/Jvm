#include <stack>

#include "frame.hpp"
#include "types.hpp"

using namespace std;

class Frame_stack {
    
public:

    void add_frame(Frame frame);
    
    Frame get_top_frame();
    
    bool destroy_top_frame();
    
    u4 size();
    
    stack<Frame> frame_stack;
};