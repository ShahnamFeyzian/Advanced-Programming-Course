CC = g++
BUILD_DIR = build
SRC_DIR = src
CFLAG = --std=c++11
EXECUTABLE_FILE = utaxi.out

all: $(BUILD_DIR) $(EXECUTABLE_FILE)

$(BUILD_DIR) :
	mkdir -p $(BUILD_DIR)

OBJECTS = \
	$(BUILD_DIR)/main.o \
	$(BUILD_DIR)/user.o \
	$(BUILD_DIR)/trip.o \
	$(BUILD_DIR)/location.o \
	$(BUILD_DIR)/exception.o \
	$(BUILD_DIR)/utaxi_app.o \
	$(BUILD_DIR)/response.o \
	$(BUILD_DIR)/request.o \
	$(BUILD_DIR)/template_parser.o \
	$(BUILD_DIR)/utilities.o \
	$(BUILD_DIR)/server.o \
	$(BUILD_DIR)/handlers.o \
	$(BUILD_DIR)/my_server.o \
	$(BUILD_DIR)/route.o \

$(EXECUTABLE_FILE): $(OBJECTS)
	$(CC) $(CFLAG) $(OBJECTS) -o $(EXECUTABLE_FILE)
#-------------------

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp $(SRC_DIR)/utaxi_app.hpp
	$(CC) $(CFLAG) -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/main.o
	
$(BUILD_DIR)/utaxi_app.o: $(SRC_DIR)/utaxi_app.cpp $(SRC_DIR)/utaxi_app.hpp $(SRC_DIR)/exception.hpp $(SRC_DIR)/user.hpp $(SRC_DIR)/location.hpp $(SRC_DIR)/trip.hpp
	$(CC) $(CFLAG) -c $(SRC_DIR)/utaxi_app.cpp -o $(BUILD_DIR)/utaxi_app.o


#-------------------

$(BUILD_DIR)/user.o: $(SRC_DIR)/user.cpp $(SRC_DIR)/user.hpp
	$(CC) $(CFLAG) -c $(SRC_DIR)/user.cpp -o $(BUILD_DIR)/user.o

$(BUILD_DIR)/trip.o: $(SRC_DIR)/trip.cpp $(SRC_DIR)/trip.hpp
	$(CC) $(CFLAG) -c $(SRC_DIR)/trip.cpp -o $(BUILD_DIR)/trip.o

$(BUILD_DIR)/location.o: $(SRC_DIR)/location.cpp $(SRC_DIR)/location.hpp 
	$(CC) $(CFLAG) -c $(SRC_DIR)/location.cpp -o $(BUILD_DIR)/location.o

$(BUILD_DIR)/exception.o: $(SRC_DIR)/exception.cpp $(SRC_DIR)/exception.hpp 
	$(CC) $(CFLAG) -c $(SRC_DIR)/exception.cpp -o $(BUILD_DIR)/exception.o

#-------------------

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) $(CF) -c utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) $(CF) -c utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) $(CF) -c utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/route.cpp -o $(BUILD_DIR)/route.o

#-------------------

$(BUILD_DIR)/template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp
	$(CC) $(CF) -c utils/template_parser.cpp -o $(BUILD_DIR)/template_parser.o

$(BUILD_DIR)/handlers.o: $(SRC_DIR)/handlers.cpp $(SRC_DIR)/handlers.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c $(SRC_DIR)/handlers.cpp -o $(BUILD_DIR)/handlers.o

$(BUILD_DIR)/my_server.o: $(SRC_DIR)/my_server.cpp $(SRC_DIR)/my_server.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c $(SRC_DIR)/my_server.cpp -o $(BUILD_DIR)/my_server.o




.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out
