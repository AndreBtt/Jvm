main: src/main.cpp src/utils.cpp src/reader.cpp
	g++ -o bin/main src/main.cpp src/utils.cpp src/reader.cpp

run: main
	bin/main exp/Jogador.class