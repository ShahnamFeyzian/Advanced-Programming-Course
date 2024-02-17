CC := g++ --std=c++11




main: main.o Document.o Loan.o Person.o Library.o Error.hpp
	$(CC) main.o Document.o Loan.o Person.o Library.o -o main

main.o: main.cpp
	$(CC) -c main.cpp -o main.o

Library.o: Library.cpp Library.hpp Error.hpp
	$(CC) -c Library.cpp -o Library.o

Person.o: Person.cpp Person.hpp Error.hpp
	$(CC) -c Person.cpp -o Person.o

Loan.o: Loan.cpp Loan.hpp Error.hpp
	$(CC) -c Loan.cpp -o Loan.o

Document.o: Document.cpp Document.hpp Error.hpp
	$(CC) -c Document.cpp -o Document.o

clean:
	rm *.o main