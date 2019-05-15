main: src/main.cpp src/utils.cpp src/reader.cpp src/constant_pool.cpp
	g++ -o bin/main src/main.cpp src/utils.cpp src/reader.cpp src/constant_pool.cpp

run: main
	bin/main exp/Jogador.class