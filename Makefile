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
      ./src/translator.cpp\
      ./src/lib/logger.cpp \
      ./tests/main.cpp 


testAll :
	$(CC) $(CFLAGS) $(TESTFLAGS) $(TESTS) -o testAll
# ui_alu test
ui_alu :
	$(CC) $(CFLAGS) $(FILES)  ./tests/ui_testalu.cpp -o ui_alu
testTransferUnit:
	$(CC) $(CFLAGS) -DTEST_TRANSFERUNIT $(TESTS) -o testTransferUnit
testShiftCircuit:
	$(CC) $(CFLAGS) -DTEST_SHIFTCIRCUIT $(TESTS) -o testShiftCircuit
testAccumulator:
	$(CC) $(CFLAGS) -DTEST_ACCUMULATOR $(TESTS) -o testaccumulator
testALU:
	$(CC) $(CFLAGS) -DTEST_ALU  $(TESTS) -o testalu
cleanTests :
	rm -vf testAll testAddition testTransferUnit testShiftCircuit testaccumulator ./tests/*.o ./tests/*.out ./tests/*.gch



