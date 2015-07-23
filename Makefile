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
	  ./src/shiftcircuit.cpp\
	  ./src/accumulator.cpp\
	  ./src/alu.cpp\
	  ./src/translator.cpp\
	  ./src/lib/logger.cpp\
	  ./src/witch.cpp\

# Source Targets 
all : 
	$(CC) $(CFLAGS) $(FILES) ./src/main.cpp -o witch_sim

clean :
	rm -vf  ./src/*.out   witch_sim   ./src/*.o   ./src/*.h.gch  ./src/*.gch

#############################################
####			Testing 				#####
#############################################

# TODO : Define conditional tests
TESTFLAGS= -DTEST_DEKATRON -DTEST_DEKATRONSTORE -DTEST_TRANSFERUNIT -DTEST_SHIFTCIRCUIT -DTEST_ACCUMULATOR \
			-DTEST_ALU

# Define all test files here
# Do not Add header files here, they are to be dealt within the codes
# similarly do not include cpp files within the source
TESTS=./src/dekatron.cpp ./tests/testdekatron.cpp \
      ./src/dekatronstore.cpp ./tests/testdekatronstore.cpp \
      ./src/transferunit.cpp ./tests/testtransferunit.cpp \
      ./src/shiftcircuit.cpp ./tests/testshiftcircuit.cpp \
      ./src/accumulator.cpp ./tests/testaccumulator.cpp \
      ./src/alu.cpp ./tests/testalu.cpp\
      ./src/translator.cpp \
      ./src/lib/logger.cpp \
      ./src/witch.cpp\
      ./tests/main.cpp 

BIN=./bin/testAll \
	./bin/testDekatron \
	./bin/testDekatronStore \
	./bin/testAddition \
	./bin/testTransferUnit \
	./bin/testShiftCircuit \
	./bin/testAccumulator \
	./bin/ui_alu

testAll :
	$(CC) $(CFLAGS) $(TESTFLAGS) $(TESTS) -o ./bin/testAll
# ui_alu test
ui_alu :
	$(CC) $(CFLAGS) $(FILES)  ./tests/ui_testalu.cpp -o ./bin/ui_alu
testDekatron:
	$(CC) $(CFLAGS) -DTEST_DEKATRON $(TESTS) -o ./bin/testDekatron
testDekatronStore:
	$(CC) $(CFLAGS) -DTEST_DEKATRONSTORE $(TESTS) -o ./bin/testDekatronStore
testTransferUnit:
	$(CC) $(CFLAGS) -DTEST_TRANSFERUNIT $(TESTS) -o ./bin/testTransferUnit
testShiftCircuit:
	$(CC) $(CFLAGS) -DTEST_SHIFTCIRCUIT $(TESTS) -o ./bin/testShiftCircuit
testAccumulator:
	$(CC) $(CFLAGS) -DTEST_ACCUMULATOR $(TESTS) -o ./bin/testAccumulator
testALU:
	$(CC) $(CFLAGS) -DTEST_ALU  $(TESTS) -o ./bin/testalu
cleanTests :
	rm -rvf $(BIN) ./tests/*.o ./tests/*.out ./tests/*.gch

# TODO : add CLI files
#	 add _DEBUG_ flag

