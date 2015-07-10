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
	std::cout << "Testing alu.cpp (mult. & div.)"<< std::endl;
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
		std::cout << "ALU TEST 1.1 multiply() FAILURE "  << accum.getStringStateInStore() << " vs 0146410000000000\n";
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
		std::cout << "ALU TEST 1.2 multiply() FAILURE "  << accum.getStringStateInStore() << " vs 0146410000000000\n";
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
		std::cout << "ALU TEST 1.3 multiply() FAILURE "  << accum.getStringStateInStore() << " vs 8 8888 0105 4321 112\n";
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
		std::cout << "ALU TEST 2.1 multiply() FAILURE "  << accum.getStringStateInStore() << " vs 9 8535 8999 9999 999\n";
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
		std::cout << "ALU TEST 2.2 multiply() FAILURE "  << accum.getStringStateInStore() << " vs 8 7999 9999 9999 999\n";
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
		std::cout << "ALU TEST 2.3 multiply() FAILURE "  << accum.getStringStateInStore() << " vs 9 9999 0124 3211 110\n";
	}

	// +ve * -ve
	source.setStoreValue("012100000",newState);
	destination.setStoreValue("987899999",newState);
	accum.clearAccumulator();
	alu.multiply(&source,&destination,&accum);
	if(!accum.getStringStateInStore().compare("9853589999999999")  &&
			!destination.getStringStateInStore().compare("999999999"))
		std::cout << "ALU TEST 3.1 SUCCESSFUL \n";
	else{
		failedTests++;
		std::cout << "ALU TEST 3.1 multiply() FAILURE "  << accum.getStringStateInStore() << " vs 9 8535 8999 9999 999\n";
	}
	source.setStoreValue("090000000",newState);
	destination.setStoreValue("909999999",newState);
	accum.clearAccumulator();
	alu.multiply(&source,&destination,&accum);
	if(!accum.getStringStateInStore().compare("1899999999999999") &&
			!destination.getStringStateInStore().compare("999999999"))
		std::cout << "ALU TEST 3.2 SUCCESSFUL \n";
	else{
		failedTests++;
		std::cout << "ALU TEST 3.2 multiply() FAILURE "  << accum.getStringStateInStore() << " vs 1 8999 9999 9999 999\n";
	}

	source.setStoreValue("099000000",newState);
	destination.setStoreValue("987654321",newState);
	accum.clearAccumulator();
	alu.multiply(&source,&destination,&accum); 
	if(!accum.getStringStateInStore().compare("8777777877999999") &&
			!destination.getStringStateInStore().compare("999999999"))
		std::cout << "ALU TEST 3.3 SUCCESSFUL \n";
	else{
		failedTests++;
		std::cout << "ALU TEST 3.3 multiply() FAILURE "  << accum.getStringStateInStore() << " vs 8 7777 7787 7999 999\n";
	}
	// -ve * -ve
	// -121*-121 = (1.4641)
	accum.clearAccumulator();
	source.setStoreValue("987899999",newState);
	destination.setStoreValue("987899999",newState);
	alu.multiply(&source,&destination,&accum); //0146410000000000
	if(!accum.getStringStateInStore().compare("0146410000000000") &&
			!destination.getStringStateInStore().compare("999999999"))
		std::cout << "ALU TEST 4.1 SUCCESSFUL \n";
	else{
		failedTests++;
		std::cout << "ALU TEST 4.1 multiply() FAILURE "  << accum.getStringStateInStore() << " vs 0 1464 1000 0000 000\n";
	}
	//- 3.0 * - 4.0 = +(12.0) overflow = 1 2000 0000
	source.setStoreValue("969999999",newState);
	destination.setStoreValue("959999999",newState);
	accum.clearAccumulator();
	alu.multiply(&source,&destination,&accum);
	if(!accum.getStringStateInStore().compare("1200000000000000") &&
			!destination.getStringStateInStore().compare("999999999"))
		std::cout << "ALU TEST 4.2 SUCCESSFUL \n";
	else{
		failedTests++;
		std::cout << "ALU TEST 4.2 multiply() FAILURE "  << accum.getStringStateInStore() << " vs 1 2000 0000 0000 000\n";
	}
	// - 0000 1111 * - 8888 9999 = + 0000 9875 6788 889
	source.setStoreValue("999998888",newState);
	destination.setStoreValue("911110000",newState);
	accum.clearAccumulator();
	alu.multiply(&source,&destination,&accum);
	if(!accum.getStringStateInStore().compare("0000098756788889")&&
			!destination.getStringStateInStore().compare("999999999"))
		std::cout << "ALU TEST 4.3 SUCCESSFUL \n";
	else{
		failedTests++;
		std::cout << "ALU TEST 4.3 multiply() FAILURE "  << accum.getStringStateInStore() << " vs 0 0000 9875 6788 889\n";
	}
	std::cout << "FINISH multiplycircuit.cpp TESTS\n";
}



