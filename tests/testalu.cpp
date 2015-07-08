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

	// +ve * +ve
	source.setStoreValue("012100000",newState);
	destination.setStoreValue("012100000",newState);
	alu.multiply(&source,&destination,&accum);
	if(!accum.getStringStateInStore().compare("0146410000000000") &&
			!destination.getStringStateInStore().compare("000000000"))
		std::cout << "ALU TEST 1.1 SUCCESSFUL \n";
	else{
		failedTests++;
		std::cout << "ALU TEST 1.1 shift() FAILURE "  << accum.getStringStateInStore() << " vs 0146410000000000\n";
	}
	source.setStoreValue("099999999",newState);
	destination.setStoreValue("011111111",newState);
	accum.clearAccumulator();
	alu.multiply(&source,&destination,&accum);
	if(!accum.getStringStateInStore().compare("1111111088888889") &&
			!destination.getStringStateInStore().compare("000000000"))
		std::cout << "ALU TEST 1.2 SUCCESSFUL \n";
	else{
		failedTests++;
		std::cout << "ALU TEST 1.2 shift() FAILURE "  << accum.getStringStateInStore() << " vs 0146410000000000\n";
	}

	source.setStoreValue("099998888",newState);
	destination.setStoreValue("088889999",newState);
	accum.clearAccumulator();
	alu.multiply(&source,&destination,&accum);
	if(!accum.getStringStateInStore().compare("8888901054321112") &&
			!destination.getStringStateInStore().compare("000000000"))
		std::cout << "ALU TEST 1.3 SUCCESSFUL \n";
	else{
		failedTests++;
		std::cout << "ALU TEST 1.3 shift() FAILURE "  << accum.getStringStateInStore() << " vs 8 8888 0105 4321 112\n";
	}
	// -ve * +ve
	// -121*121 = -(1.4641) = 9 8535 8999 9999 999
	accum.clearAccumulator();
	source.setStoreValue("987899999",newState);
	destination.setStoreValue("012100000",newState);
	alu.multiply(&source,&destination,&accum);
	if(!accum.getStringStateInStore().compare("9853589999999999") &&
			!destination.getStringStateInStore().compare("000000000"))
		std::cout << "ALU TEST 2.1 SUCCESSFUL \n";
	else{
		failedTests++;
		std::cout << "ALU TEST 2.1 shift() FAILURE "  << accum.getStringStateInStore() << " vs 9 8535 8999 9999 999\n";
	}
	//- 3.0 * 4.0 = -(12.0) overflow = 8 7999 9999 9999 999
	source.setStoreValue("969999999",newState);
	destination.setStoreValue("040000000",newState);
	accum.clearAccumulator();
	alu.multiply(&source,&destination,&accum);
	if(!accum.getStringStateInStore().compare("8799999999999999") &&
			!destination.getStringStateInStore().compare("000000000"))
		std::cout << "ALU TEST 2.2 SUCCESSFUL \n";
	else{
		failedTests++;
		std::cout << "ALU TEST 2.2 shift() FAILURE "  << accum.getStringStateInStore() << " vs 8 7999 9999 9999 999\n";
	}
	// - 0000 1111 * 8888 9999 = - 0000 9875 6788 889= 9 9999 0124 3211 110
	source.setStoreValue("999998888",newState);
	destination.setStoreValue("088889999",newState);
	accum.clearAccumulator();
	alu.multiply(&source,&destination,&accum);
	if(!accum.getStringStateInStore().compare("9999901243211110") &&
			!destination.getStringStateInStore().compare("000000000"))
		std::cout << "ALU TEST 2.3 SUCCESSFUL \n";
	else{
		failedTests++;
		std::cout << "ALU TEST 2.3 shift() FAILURE "  << accum.getStringStateInStore() << " vs 9 9999 0124 3211 110\n";
	}
	std::cout << "FINISH shiftcircuit.cpp TESTS\n";
}



