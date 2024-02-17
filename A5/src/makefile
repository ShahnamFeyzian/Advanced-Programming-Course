CC := g++ --std=c++11
CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer

starwars.out: main.o game.o ships.o base_ship.o fire.o power.o rsdl.o
	$(CC) main.o game.o ships.o base_ship.o fire.o power.o rsdl.o $(CCFLAGS) -o starwars.out

main.o: main.cpp ships.hpp
	$(CC) -c main.cpp -o main.o

game.o: game.cpp ships.hpp constance.hpp
	$(CC) -c game.cpp -o game.o

ships.o: ships.cpp base_ship.hpp constance.hpp
	$(CC) -c ships.cpp -o ships.o

base_ship.o: base_ship.cpp fire.hpp constance.hpp
	$(CC) -c base_ship.cpp -o base_ship.o

fire.o: fire.cpp constance.hpp
	$(CC) -c fire.cpp -o fire.o

power.o: power.cpp constance.hpp
	$(CC) -c power.cpp -o power.o

rsdl.o:
	$(CC) -c rsdl.cpp -o rsdl.o

clean:
	rm *.o starwars.out

