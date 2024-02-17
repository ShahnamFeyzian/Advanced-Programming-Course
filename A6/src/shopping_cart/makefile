CC := g++ --std=c++11

main: main.o Object.o CartManager.o Error.hpp
	$(CC) main.o Object.o CartManager.o -o main

main.o: main.cpp
	$(CC) -c main.cpp -o main.o

CartManager: CartManager.cpp CartManager.hpp Error.hpp
	$(CC) -c CartManager.cpp -o CartManager.o

Object.o: Object.cpp Object.hpp Error.hpp
	$(CC) -c Object.cpp -o Object.o

clean:
	rm *.o main