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
	logObj.log(LogLevel::INFO, "testdekatron.cpp", "Testing dekatron.cpp\n");
	Dekatron dekatron;
		// Initial value must be zero, pulse and increment 
	if(dekatron.incrementState() != DekatronState::ONE){
		logObj.log(LogLevel::WARNING,"testdekatron.cpp", "Dekatron increment FAILURE\n");
		failedTests++;
	}
	else
		logObj.log(LogLevel::INFO, "testdekatron.cpp","Dekatron Test 1 SUCCESSFUL\n");
	dekatron.incrementState();
	dekatron.incrementState();
	dekatron.incrementState();
	dekatron.incrementState();
	dekatron.incrementState();
	dekatron.incrementState();
	dekatron.incrementState();
	dekatron.incrementState(); // 9
	if(dekatron.incrementState() != DekatronState::ZERO){
		logObj.log(LogLevel::WARNING,"testdekatron.cpp","Dekatron modulo increment FAILURE\n");
		failedTests++;
	}
	else
		logObj.log(LogLevel::INFO, "testdekatron.cpp","Dekatron Test 2 SUCCESSFUL\n");
	if(dekatron.getCurrentNumber() != 0 ){
		logObj.log(LogLevel::WARNING,"testdekatron.cpp", "Dekatron getCurrentNumber() FAILURE \n");
		failedTests++;
	}
	else
		logObj.log(LogLevel::INFO, "testdekatron.cpp", "Dekatron Test 3 SUCCESSFUL\n");
	dekatron.incrementState();
	if(dekatron.getCurrentNumber() != 1 ){
		logObj.log(LogLevel::WARNING,"testdekatron.cpp","Dekatron getCurrentNumber() FAILURE \n");
		failedTests++;
	}
	else
		logObj.log(LogLevel::INFO, "testdekatron.cpp","Dekatron Test 4 SUCCESSFUL\n");
	logObj.log(LogLevel::INFO, "testdekatron.cpp","FINISH dekatron.cpp TEST\n");
}

