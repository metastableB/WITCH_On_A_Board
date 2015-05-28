#
# dekatron.h
# @author Don Dennis (metastableB)
# donkdennis [at] gmail [dot] com
# 27 May,2015
#

# Variable declarations
CC=g++

CFLAGS=-std=c++11 -Wall

# Define all source definitions here
FILES=./src/dekatron.h ./src/dekatron.cpp ./src/main.cpp 

# Define all test files here
TESTS=./tests/testdekatron.cpp ./src/dekatron.cpp ./src/dekatron.h \
      ./tests/testdekatronstore.cpp ./src/dekatronstore.cpp \
      ./tests/main.cpp 

# Source Targets 
all : 
	$(CC) $(CFLAGS) $(FILES) -o witch_sim

clean :
	rm -vf  ./src/*.out   witch_sim   ./src/*.o   ./src/*.h.gch  ./src/*.gch

# Testing
testAll :
	$(CC) $(CFLAGS) $(TESTS) -o testAll
cleanTest :
	rm -vf testAll ./tests/*.o ./tests/*.out ./tests/*.gch

