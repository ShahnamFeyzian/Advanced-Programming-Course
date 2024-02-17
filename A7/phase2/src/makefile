CC := g++ --std=c++11




utaxi.out: main.o cli_app_runer.o utaxi_app.o location.o user.o trip.o exception.o
	$(CC) main.o cli_app_runer.o utaxi_app.o location.o user.o trip.o exception.o -o utaxi.out

main.o: main.cpp
	$(CC) -c main.cpp -o main.o

cli_app_runer.o: cli_app_runer.cpp cli_app_runer.hpp
	$(CC) -c cli_app_runer.cpp -o cli_app_runer.o

utaxi_app.o: utaxi_app.cpp utaxi_app.hpp
	$(CC) -c utaxi_app.cpp -o utaxi_app.o

location.o: location.cpp location.hpp
	$(CC) -c location.cpp -o location.o

user.o: user.cpp user.hpp
	$(CC) -c user.cpp -o user.o

trip.o: trip.cpp trip.hpp
	$(CC) -c trip.cpp -o trip.o

exception.o: exception.cpp exception.hpp
	$(CC) -c exception.cpp -o exception.o

clean:
	rm *.o utaxi.out
