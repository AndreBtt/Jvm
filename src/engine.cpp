#include "engine.hpp"

void Engine::start(ClassFile class_file) {
    ClassRuntime class_run_time(class_file);
    FrameStack frame_stack;

    std::vector<Variable> arguments;

    frame_stack.add_frame(Frame(class_run_time, "main", "([Ljava/lang/String;)V", arguments));

    // if (doesMethodExist(classRuntime, "<clinit>", "()V")) {
    //     stackFrame.addFrame(new Frame(classRuntime, "<clinit>", "()V", arguments));
    // }

    // PENSAR AGORA NAS INSTRUCOES EM COMO IMPLEMENTAR !!

    while (frame_stack.size() > 0) {
        Frame curr_frame = frame_stack.get_top_frame();
        std::cout << int(curr_frame.get_method_code(3));
        break;
        // u1 code = curr_frame.get_method_code(curr_frame.pc);
        // std::cout << int(code) << std::endl;
    }
}