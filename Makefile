#
# dekatron.h
# @author Don Dennis (metastableB)
# donkdennis [at] gmail [dot] com
# 27 May,2015
#

# Variable declarations
CC=g++

CFLAGS=-std=c++11 -Wall

# Define all header definitions here
FILES=./src/dekatron.h ./src/dekatron.cpp ./src/main.cpp 
# Targets 
all : 
	$(CC) $(CFLAGS) $(FILES) -o witch_sim

clean :
	rm -vf src./*.out *witch_sim src/*.o src/*.h.gch src/*.gch