main: src/main.cpp src/class_file.cpp src/utils.cpp src/reader.cpp src/attribute.cpp src/display.cpp src/class_run_time.cpp src/frame_stack.cpp src/frame.cpp src/engine.cpp
	g++ -std=c++11 -o bin/main src/main.cpp src/class_file.cpp src/utils.cpp src/reader.cpp src/attribute.cpp src/display.cpp src/class_run_time.cpp src/frame_stack.cpp src/frame.cpp src/engine.cpp

run: main
	bin/main exp/double_aritmetica.class
