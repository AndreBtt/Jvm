#include "engine.hpp"

void Engine::start(ClassFile class_file) {
    ClassRuntime class_run_time(class_file);
    FrameStack frame_stack;

    std::vector<Variable> arguments;

    frame_stack.add_frame(Frame(class_run_time, "main", "([Ljava/lang/String;)V", arguments));

    // PAREI NA PARTE DE ACHAR O ATRIBUTOS DO METODO NA HORA DE INSTANCIAR O FRAME 

    // if (doesMethodExist(classRuntime, "<clinit>", "()V")) {
    //     stackFrame.addFrame(new Frame(classRuntime, "<clinit>", "()V", arguments));
    // }

    // while (stackFrame.size() > 0) {
    //     Frame *topFrame = stackFrame.getTopFrame();
    //     u1 *code = topFrame->getCode(topFrame->pc);
    //     (*this.*_instructionFunctions[code[0]])();
    // }
}