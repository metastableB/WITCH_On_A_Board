/*
 * testalu.cpp
 *
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 27-Jun-2015
 * 
 */
#include "testalu.h"

TestALU::TestALU(){
	std::cout << "Testing alu.cpp"<< std::endl;
	DekatronStore source,destination;
	Dekatron newState[9];
	Accumulator accum;

	source.setStoreValue("012100000",newState);
	destination.setStoreValue("012100000",newState);
	alu.multiply(&source,&destination,&accum);
	if(!accum.getStringStateInStore().compare("0146410000000000"))
		std::cout << "ALU TEST 1.1 SUCCESSFUL \n";
	else{
		failedTests++;
		std::cout << "ALU TEST 1.1 shift() FAILURE "  << accum.getStringStateInStore() << " vs 0146410000000000\n";
	}
	std::cout << "FINISH shiftcircuit.cpp TESTS\n";
}



