#
# Makefile
# @author Don Dennis (metastableB)
# donkdennis [at] gmail [dot] com
# 27 May,2015
#

# Variable declarations
CC=g++
CFLAGS=-std=c++11 -Wall
ifeq ($(debug), 1)   
	CFLAGS += -g	
endif

# Define all source definitions here
FILES=./src/dekatron.cpp \
	  ./src/dekatronstore.cpp \
	  ./src/transferunit.cpp \
	  ./src/main.cpp 



# Source Targets 
all : 
	$(CC) $(CFLAGS) $(FILES) -o witch_sim

clean :
	rm -vf  ./src/*.out   witch_sim   ./src/*.o   ./src/*.h.gch  ./src/*.gch

#############################################
####			Testing 				#####
#############################################

# TODO : Define conditional tests
TESTFLAGS= -DTEST_DEKATRON -DTEST_DEKATRONSTORE -DTEST_TRANSFERUNIT

# Define all test files here
# Do not Add header files here, they are to be dealt within the codes
# similarly do not include cpp files within the source
TESTS=./src/dekatron.cpp ./tests/testdekatron.cpp \
      ./src/dekatronstore.cpp ./tests/testdekatronstore.cpp \
      ./src/transferunit.cpp ./tests/testtransferunit.cpp \
      ./tests/main.cpp 

testAll :
	$(CC) $(CFLAGS) $(TESTFLAGS) $(TESTS) -o testAll
cleanTest :
	rm -vf testAll ./tests/*.o ./tests/*.out ./tests/*.gch

