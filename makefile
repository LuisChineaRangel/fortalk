#-----------------------------------------------------------------------------------
# Makefile
#-----------------------------------------------------------------------------------
# Luis Marcelo Chinea Rangel
# University of La Laguna
# Higher Polytechnic School of Engineering and Technology
# Undergraduate degree in Computer Engineering
# Contact E-mail: alu0101118116@ull.es
#-----------------------------------------------------------------------------------

CC=g++
CFLAGS=$(IDIR) -std=c++11 -g

INCLUDE_DIR =include
OBJECTS_DIR=build
SRC_DIR =src
LIB_DIR =lib
BIN_DIR =bin
IDIR=-I -Wall -Wextra

LIBS=-lm

_OBJ = main.o Socket.o
OBJ = $(patsubst %,$(OBJECTS_DIR)/%,$(_OBJ))

BIN_NAME = Talk

all: Talk

Talk: $(OBJ)
	$(CC) -o $(BIN_DIR)/$(BIN_NAME) $^ $(CFLAGS) $(LIBS)

$(OBJECTS_DIR)/Socket.o: $(SRC_DIR)/Socket.cpp
	$(CC) -c -o $@ $< $(CFLAGS)		

$(OBJECTS_DIR)/main.o: $(SRC_DIR)/main.cpp $(INCLUDE_DIR)/Socket.hpp
	$(CC) -c -o $@ $< $(CFLAGS)

run:
	./$(BIN_DIR)/$(BIN_NAME) 

.PHONY: clean

clean:
	@rm -f $(OBJECTS_DIR)/*.o *~ $(INCLUDE_DIR)/*~ $(BIN_DIR)/*.exe
	@echo
	@echo "Objects Files and Executables cleaned!"
