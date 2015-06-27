/*
 * testdekatron.cpp
 *
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 28-May-2015
 *
 */

 #include "testdekatron.h"

TestDekatron::TestDekatron() {
	std::cout << "Testing dekatron.cpp\n";
	Dekatron dekatron;
		// Initial value must be zero, pulse and increment 
	if(dekatron.incrementState() != DekatronState::ONE){
		std::cout<<"Dekatron increment FAILURE\n";
		failedTests++;
	}
	else
		std::cout<<"Dekatron Test 1 SUCCESSFUL\n";
	dekatron.incrementState();
	dekatron.incrementState();
	dekatron.incrementState();
	dekatron.incrementState();
	dekatron.incrementState();
	dekatron.incrementState();
	dekatron.incrementState();
	dekatron.incrementState(); // 9
	if(dekatron.incrementState() != DekatronState::ZERO){
		std::cout<<"Dekatron modulo increment FAILURE\n";
		failedTests++;
	}
	else
		std::cout<<"Dekatron Test 2 SUCCESSFUL\n";
	if(dekatron.getCurrentNumber() != 0 ){
		std::cout<<"Dekatron getCurrentNumber() FAILURE \n";
		failedTests++;
	}
	else
		std::cout<<"Dekatron Test 3 SUCCESSFUL\n";
	dekatron.incrementState();
	if(dekatron.getCurrentNumber() != 1 ){
		std::cout<<"Dekatron getCurrentNumber() FAILURE \n";
		failedTests++;
	}
	else
		std::cout<<"Dekatron Test 4 SUCCESSFUL\n";
	std::cout<<"FINISH dekatron.cpp TEST\n";
}

