main: src/main.cpp src/utils.cpp src/reader.cpp src/constant_pool.cpp src/display.cpp
	g++ -std=c++11 -o bin/main src/main.cpp src/utils.cpp src/reader.cpp src/constant_pool.cpp src/display.cpp

run: main
	bin/main exp/Jogador.class