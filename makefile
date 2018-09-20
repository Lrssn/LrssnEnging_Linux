CXXFLAGS=-lGL -lGLEW -lglfw -lassimp -lSOIL -std=c++11

all: engine

engine: main.o camera.o mesh.o model.o shader.o texture.o window.o terrainCreator.o player.o controller.o
	g++ main.o camera.o mesh.o model.o shader.o texture.o window.o terrainCreator.o player.o controller.o -o output $(CXXFLAGS)

main.o: main.cpp
	g++ -c main.cpp

camera.o: camera.cpp camera.h
	g++ -c camera.cpp

mesh.o: mesh.cpp mesh.h
	g++ -c mesh.cpp

model.o: model.cpp model.h
	g++ -c model.cpp

shader.o: shader.cpp shader.h
	g++ -c shader.cpp

texture.o: texture.cpp texture.h
	g++ -c texture.cpp

window.o: window.cpp window.h
	g++ -c window.cpp

terrainCreator.o: terrainCreator.cpp terrainCreator.h
	g++ -c terrainCreator.cpp

player.o: player.cpp player.h
	g++ -c player.cpp

controller.o: controller.cpp controller.h
	g++ -c controller.cpp

clean:
	rm -f *.o *.out output
