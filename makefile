main: src/main.cpp src/class_file.cpp src/utils.cpp src/reader.cpp src/attribute.cpp src/display.cpp
	g++ -std=c++11 -o bin/main src/main.cpp src/class_file.cpp src/utils.cpp src/reader.cpp src/attribute.cpp src/display.cpp

run: main
	bin/main exp/double_aritmetica.class