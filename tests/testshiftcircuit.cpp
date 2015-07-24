/*
 * testshiftcircuit.cpp
 *
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 13-Jun-2015
 * 
 */

#include "testshiftcircuit.h"

TestShiftCircuit::TestShiftCircuit () {
	logObj.log(LogLevel::INFO,"testshiftcircuit.cpp","Testing shiftcircuit.cpp\n");
	Dekatron bufferDekatron[9];
	DekatronStore source, destination;
	TransferUnit transferUnit;
	ShiftCircuit shiftCircuit;

	source.setStoreValue("023456789",bufferDekatron);
	transferUnit.transfer(&source,&destination,-1);
	if(!destination.getStringStateInStore().compare("034567890"))
		logObj.log(LogLevel::INFO,"testshiftcircuit.cpp","ShiftCircuit TEST 1.1 SUCCESSFUL \n");
	else{
		failedTests++;
		logObj.log(LogLevel::WARNING,"testshiftcircuit.cpp", "ShiftCircuit TEST 1.1 shift() FAILURE "  + destination.getStringStateInStore() + " vs 034567890\n");
	}
	destination.setStoreValue("000000000",bufferDekatron);
	transferUnit.transfer(&source,&destination);
	if(!destination.getStringStateInStore().compare("023456789"))
			logObj.log(LogLevel::INFO,"testshiftcircuit.cpp","ShiftCircuit TEST 1.2 SUCCESSFUL\n");
	else{
		failedTests++;
		logObj.log(LogLevel::WARNING,"testshiftcircuit.cpp", "ShiftCircuit TEST 1.2 shift() FAILURE \n");
	}
	destination.setStoreValue("000000000",bufferDekatron);
	transferUnit.transfer(&source,&destination,0);
	if(!destination.getStringStateInStore().compare("023456789"))
			logObj.log(LogLevel::INFO,"testshiftcircuit.cpp","ShiftCircuit TEST 1.3 SUCCESSFUL\n");
	else{
		failedTests++;
		logObj.log(LogLevel::WARNING,"testshiftcircuit.cpp", "ShiftCircuit TEST 1.3 shift() FAILURE " + destination.getStringStateInStore()+" vs 023456789\n");
	}
	destination.setStoreValue("000000000",bufferDekatron);
	transferUnit.transfer(&source,&destination,1);
	if(!destination.getStringStateInStore().compare("002345678"))
			logObj.log(LogLevel::INFO,"testshiftcircuit.cpp","ShiftCircuit TEST 1.4 SUCCESSFUL\n");
	else{
		failedTests++;
		logObj.log(LogLevel::WARNING,"testshiftcircuit.cpp", "ShiftCircuit TEST 1.4 shift() FAILURE "+destination.getStringStateInStore()+" vs 002345678\n");
	}
	destination.setStoreValue("000000000",bufferDekatron);
	transferUnit.transfer(&source,&destination,3);
	if(!destination.getStringStateInStore().compare("000023456"))
			logObj.log(LogLevel::INFO,"testshiftcircuit.cpp","ShiftCircuit TEST 1.5 SUCCESSFUL\n");
	else{
		failedTests++;
		logObj.log(LogLevel::WARNING,"testshiftcircuit.cpp", "ShiftCircuit TEST 1.5 shift() FAILURE " +destination.getStringStateInStore() +" vs 000023456\n");
	}
	destination.setStoreValue("000000000",bufferDekatron);
	source.setStoreValue("912345678",bufferDekatron);
	transferUnit.transfer(&source,&destination,7);
	if(!destination.getStringStateInStore().compare("999999991"))
			logObj.log(LogLevel::INFO,"testshiftcircuit.cpp","ShiftCircuit TEST 1.6 SUCCESSFUL\n");
	else{
		failedTests++;
		logObj.log(LogLevel::WARNING,"testshiftcircuit.cpp", "ShiftCircuit TEST 1.6 shift() FAILURE " + destination.getStringStateInStore() + " vs 999999991\n");
	}

	// Adding both zeros
	source.setStoreValue("000000000",bufferDekatron);
	destination.setStoreValue("000000000",bufferDekatron);
	transferUnit.transfer(&source,&destination,7);
	if(!destination.getStringStateInStore().compare("000000000"))
		logObj.log(LogLevel::INFO,"testshiftcircuit.cpp","ShiftCircuit TEST 2.1 SUCCESSFUL\n"); 
	else{
		failedTests++;
		logObj.log(LogLevel::WARNING,"testshiftcircuit.cpp",  "ShiftCircuit TEST 2.1 shift() FAILURE\n");
	}
	transferUnit.transfer(&destination, &source);
	if(!source.getStringStateInStore().compare("000000000"))
		logObj.log(LogLevel::INFO,"testshiftcircuit.cpp","ShiftCircuit TEST 2.2 SUCCESSFUL\n"); 
	else{
		failedTests++;
		logObj.log(LogLevel::WARNING,"testshiftcircuit.cpp", "ShiftCircuit TEST 2.2 shift() FAILURE\n");
	}

	// Performing simple additions by pulsing
	int pulse[9] = {1,1,1,1,1,1,1,1,1};
	source.pulseStore(pulse, bufferDekatron);
	source.pulseStore(pulse, bufferDekatron);
	transferUnit.transfer(&source,&destination,7);
	if(!destination.getStringStateInStore().compare("222222222"))
		logObj.log(LogLevel::INFO,"testshiftcircuit.cpp","ShiftCircuit TEST 3.1 SUCCESSFUL\n"); 
	else{
		failedTests++;
		logObj.log(LogLevel::WARNING,"testshiftcircuit.cpp","ShiftCircuit TEST 3.1 shift() FAILURE " + destination.getStringStateInStore() + " vs 222222222\n");
	}
	transferUnit.transfer(&destination, &source,-1);
	if(!source.getStringStateInStore().compare("444444444"))
		logObj.log(LogLevel::INFO,"testshiftcircuit.cpp","ShiftCircuit TEST 3.2 SUCCESSFUL\n"); 
	else{
		failedTests++;
		logObj.log(LogLevel::WARNING,"testshiftcircuit.cpp","ShiftCircuit TEST 3.2 shift() FAILURE " + source.getStringStateInStore() + " vs 444444444\n");
	}

	source.setStoreValue("977777977",bufferDekatron);
	destination.setStoreValue("200000002",bufferDekatron);
	
	// source is  9 7777 7977, dest is 2 0000 0002
	transferUnit.transfer(&source,&destination,-1);
	if(!destination.getStringStateInStore().compare("177779782"))
		logObj.log(LogLevel::INFO,"testshiftcircuit.cpp","ShiftCircuit TEST 4.1 SUCCESSFUL\n"); 
	else{
		failedTests++;
		logObj.log(LogLevel::WARNING,"testshiftcircuit.cpp","ShiftCircuit TEST 4.1 shift() FAILURE " +  destination.getStringStateInStore() + " vs 177779782\n");
	}
	transferUnit.transfer(&destination, &source,5);
	if(!source.getStringStateInStore().compare("088889755"))
		logObj.log(LogLevel::INFO,"testshiftcircuit.cpp","ShiftCircuit TEST 4.2 SUCCESSFUL\n"); 
	else{
		failedTests++;
		logObj.log(LogLevel::WARNING,"testshiftcircuit.cpp","ShiftCircuit TEST 4.2 shift() FAILURE " + source.getStringStateInStore()+" vs 088889755\n");
	}

	// Performing multiple addition tests
	source.setStoreValue("555555555", bufferDekatron);
	destination.setStoreValue("444444444", bufferDekatron);
	transferUnit.transfer(&source, &destination,3);
	if(!destination.getStringStateInStore().compare("999999999"))
		logObj.log(LogLevel::INFO,"testshiftcircuit.cpp","ShiftCircuit TEST 5.1 SUCCESSFUL\n"); 
	else{
		failedTests++;
		logObj.log(LogLevel::WARNING,"testshiftcircuit.cpp","ShiftCircuit TEST 5.1 shift() FAILURE " +  destination.getStringStateInStore() + " vs 999999999\n");
	}
	transferUnit.transfer(&destination, &source,7);
	if(!source.getStringStateInStore().compare("555555555"))
		logObj.log(LogLevel::INFO,"testshiftcircuit.cpp","ShiftCircuit TEST 5.2 SUCCESSFUL\n"); 
	else{
		failedTests++;
		logObj.log(LogLevel::WARNING,"testshiftcircuit.cpp","ShiftCircuit TEST 5.2 shift() FAILURE " +  source.getStringStateInStore() + " vs 555555555\n");
	}

	source.setStoreValue("012345678", bufferDekatron);
	destination.setStoreValue("991111111", bufferDekatron);
	transferUnit.transfer(&source, &destination,4);
	if(!destination.getStringStateInStore().compare("991112345"))
		logObj.log(LogLevel::INFO,"testshiftcircuit.cpp","ShiftCircuit TEST 5.3 SUCCESSFUL\n"); 
	else{
		failedTests++;
		logObj.log(LogLevel::WARNING,"testshiftcircuit.cpp","ShiftCircuit TEST 5.3 shift() FAILURE\n");
	}
	transferUnit.transfer(&destination, &source,1);
	if(!source.getStringStateInStore().compare("011456913"))
		logObj.log(LogLevel::INFO,"testshiftcircuit.cpp","ShiftCircuit TEST 5.4 SUCCESSFUL\n"); 
	else{
		failedTests++;
		logObj.log(LogLevel::WARNING,"testshiftcircuit.cpp","ShiftCircuit TEST 5.4 shift() FAILURE" + source.getStringStateInStore() + " vs 011456913\n");
	}

	source.setStoreValue("000000000", bufferDekatron);
	destination.setStoreValue("000000000", bufferDekatron);
	// Subtracting both zeros
	transferUnit.transferComplement(&source,&destination,7);
	if(!destination.getStringStateInStore().compare("999999999"))
		logObj.log(LogLevel::INFO,"testshiftcircuit.cpp","ShiftCircuit TEST 6.1 SUCCESSFUL\n"); 
	else{
		failedTests++;
		logObj.log(LogLevel::WARNING,"testshiftcircuit.cpp","ShiftCircuit TEST 6.1 shift() FAILURE " + source.getStringStateInStore() +" d: " + destination.getStringStateInStore() + "\n" );
	}
	transferUnit.transferComplement(&destination, &source);
	if(!source.getStringStateInStore().compare("000000000"))
		logObj.log(LogLevel::INFO,"testshiftcircuit.cpp","ShiftCircuit TEST 6.2 SUCCESSFUL\n"); 
	else{
		failedTests++;
		logObj.log(LogLevel::WARNING,"testshiftcircuit.cpp","ShiftCircuit TEST 6.2 shift() FAILURE " + source.getStringStateInStore() +" d: " + destination.getStringStateInStore() + "\n" );
	}

	// Performing simple subtractions after pulsing
	source.pulseStore(pulse, bufferDekatron);
	source.pulseStore(pulse, bufferDekatron);
	transferUnit.transferComplement(&source,&destination,-1);
	if(!destination.getStringStateInStore().compare("777777777"))
		logObj.log(LogLevel::INFO,"testshiftcircuit.cpp","ShiftCircuit TEST 7.1 SUCCESSFUL\n"); 
	else{
		failedTests++;
		logObj.log(LogLevel::WARNING,"testshiftcircuit.cpp","ShiftCircuit TEST 7.1 shift() FAILURE " +  destination.getStringStateInStore() + " vs 777777777\n" );
	}
	transferUnit.transferComplement(&destination, &source,4);
	if(!source.getStringStateInStore().compare("444444444"))
		logObj.log(LogLevel::INFO,"testshiftcircuit.cpp","ShiftCircuit TEST 7.2 SUCCESSFUL\n"); 
	else{
		failedTests++;
		logObj.log(LogLevel::WARNING,"testshiftcircuit.cpp","ShiftCircuit TEST 7.2 shift() FAILURE " + source.getStringStateInStore() +" vs 444444444\n");
	}

	source.pulseStore(pulse, bufferDekatron);
	source.pulseStore(pulse, bufferDekatron);
	source.pulseStore(pulse, bufferDekatron);
	destination.pulseStore(pulse, bufferDekatron);
	destination.pulseStore(pulse, bufferDekatron);
	destination.pulseStore(pulse, bufferDekatron);
	transferUnit.transferComplement(&source,&destination);
	if(!destination.getStringStateInStore().compare("222222222"))
		logObj.log(LogLevel::INFO,"testshiftcircuit.cpp","ShiftCircuit TEST 8.1 SUCCESSFUL\n"); 
	else {
		failedTests++;
		logObj.log(LogLevel::WARNING,"testshiftcircuit.cpp","ShiftCircuit TEST 8.1 shift() FAILURE " + destination.getStringStateInStore() +" vs 222222222\n");
	}
	transferUnit.transferComplement(&destination, &source,3);
	if(!source.getStringStateInStore().compare("555555555"))
		logObj.log(LogLevel::INFO,"testshiftcircuit.cpp","ShiftCircuit TEST 8.2 SUCCESSFUL\n"); 
	else {
		failedTests++;
		logObj.log(LogLevel::WARNING,"testshiftcircuit.cpp","ShiftCircuit TEST 8.2 shift() FAILURE " + source.getStringStateInStore() +" vs 555555555\n");
	}

	// Performing multiple subtraction tests
	source.setStoreValue("000000005", bufferDekatron);
	destination.setStoreValue("000000004", bufferDekatron);
	transferUnit.transferComplement(&source, &destination,-1);
	// -46 : 9 9999 9953
	if(!destination.getStringStateInStore().compare("999999953"))
		logObj.log(LogLevel::INFO,"testshiftcircuit.cpp","ShiftCircuit TEST 9.1 SUCCESSFUL\n"); 
	else {
		failedTests++;
		logObj.log(LogLevel::WARNING,"testshiftcircuit.cpp","ShiftCircuit TEST 9.1 shift() FAILURE " + source.getStringStateInStore()
		+" d: " + destination.getStringStateInStore() + "\n");
	}
	transferUnit.transferComplement(&destination, &source,-1);
	// 5 - -460 = 465
	if(!source.getStringStateInStore().compare("000000465"))
		logObj.log(LogLevel::INFO,"testshiftcircuit.cpp","ShiftCircuit TEST 9.2 SUCCESSFUL\n"); 
	else {
		failedTests++;
		logObj.log(LogLevel::WARNING,"testshiftcircuit.cpp","ShiftCircuit TEST 9.2 shift() FAILURE " + source.getStringStateInStore()
		+" d: " + destination.getStringStateInStore() + " \n");
	}

	source.setStoreValue("000000000", bufferDekatron);
	destination.setStoreValue("991111111", bufferDekatron);
	// - 0 0888 8888 - 0 = 0 0888 8888 = 9 9111 1111
	transferUnit.transferComplement(&source, &destination);
	if(!destination.getStringStateInStore().compare("991111111"))
		logObj.log(LogLevel::INFO,"testshiftcircuit.cpp","ShiftCircuit TEST 9.3 SUCCESSFUL\n"); 
	else {
		failedTests++;
		logObj.log(LogLevel::WARNING,"testshiftcircuit.cpp","ShiftCircuit TEST 9.3 shift() FAILURE " + source.getStringStateInStore()
		+" d: " + destination.getStringStateInStore() + "\n");
	}
	source.setStoreValue("991111111", bufferDekatron);
	transferUnit.transferComplement(&destination, &source,7);
	if(!source.getStringStateInStore().compare("991111111"))
		logObj.log(LogLevel::INFO,"testshiftcircuit.cpp","ShiftCircuit TEST 9.4 SUCCESSFUL\n"); 
	else {
		failedTests++;
		logObj.log(LogLevel::WARNING,"testshiftcircuit.cpp","ShiftCircuit TEST 9.4 shift() FAILURE " + source.getStringStateInStore()
		+" d: " + destination.getStringStateInStore() + "\n");
	}

	source.setStoreValue("088448800", bufferDekatron);
	destination.setStoreValue("991001234", bufferDekatron);
	transferUnit.transferComplement(&destination, &source,0);
	if(!source.getStringStateInStore().compare("097447565"))
		logObj.log(LogLevel::INFO,"testshiftcircuit.cpp","ShiftCircuit TEST 9.5 SUCCESSFUL\n"); 
	else {
		failedTests++;
		logObj.log(LogLevel::WARNING,"testshiftcircuit.cpp","ShiftCircuit TEST 9.5 shift() FAILURE " + source.getStringStateInStore()
		+" d: " + destination.getStringStateInStore() + "\n");
	}
	transferUnit.transferComplement(&source, &destination,2);
	if(!destination.getStringStateInStore().compare("990026759"))
		logObj.log(LogLevel::INFO,"testshiftcircuit.cpp","ShiftCircuit TEST 9.6 SUCCESSFUL\n"); 
	else {
		failedTests++;
		logObj.log(LogLevel::WARNING,"testshiftcircuit.cpp","ShiftCircuit TEST 9.6 shift() FAILURE " + source.getStringStateInStore()
		+" d: " + destination.getStringStateInStore() + "\n");
	}

	/********************************************
	 *              Accumulator tests           *
	 ********************************************/
	Accumulator accum;
	logObj.log(LogLevel::INFO,"testshiftcircuit.cpp","Shifts and transfer tests with accumulator\n");
	// Store to Accum addition
	source.setStoreValue("123456789",bufferDekatron);
	transferUnit.transfer(&source,&accum,0);
	if(!accum.getStringStateInStore().compare("1234567891111111"))
		logObj.log(LogLevel::INFO, "testshiftcircuit.cpp","Accumulator transfer/shift TEST 1.01 SUCCESSFUL \n");
	else{
		failedTests++;
		logObj.log(LogLevel::WARNING,"testshiftcircuit.cpp","Accumulator transfer/shift TEST 1.01 shift() FAILURE "
		+ getHumanReadableOutput(accum.getStringStateInStore(),16) + " vs 1 2345 6789 1111 111\n");
	}
	accum.clearAccumulator();
	transferUnit.transfer(&source,&accum,-1);
	if(!accum.getStringStateInStore().compare("1345678911111111"))
		logObj.log(LogLevel::INFO,"testshiftcircuit.cpp", "Accumulator transfer/shift TEST 1.02 SUCCESSFUL\n");
	else{
		failedTests++;
		logObj.log(LogLevel::WARNING,"testshiftcircuit.cpp","Accumulator transfer/shift TEST 1.02 shift() FAILURE "
		+ getHumanReadableOutput(accum.getStringStateInStore(),16) + " vs 1 3456 7891 1111 111\n");
	}
	source.setStoreValue("111111111",bufferDekatron);
	transferUnit.transfer(&source,&accum,7);
	if(!accum.getStringStateInStore().compare("2456790022222222"))
		logObj.log(LogLevel::INFO,"testshiftcircuit.cpp", "Accumulator transfer/shift TEST 1.03 SUCCESSFUL \n");
	else{
		failedTests++;
		logObj.log(LogLevel::WARNING,"testshiftcircuit.cpp","Accumulator transfer/shift TEST 1.03 shift() FAILURE "
		+ getHumanReadableOutput(accum.getStringStateInStore(),16) + " vs 2 4567 9002 2222 222\n");
	}

	source.setStoreValue("071433102",bufferDekatron);
	transferUnit.transfer(&source,&accum,0);
	if(!accum.getStringStateInStore().compare("3171121042222222"))
		logObj.log(LogLevel::INFO,"testshiftcircuit.cpp", "Accumulator transfer/shift TEST 1.04 SUCCESSFUL \n");
	else{
		failedTests++;
		logObj.log(LogLevel::WARNING,"testshiftcircuit.cpp","Accumulator transfer/shift TEST 1.04 shift() FAILURE "
		+ getHumanReadableOutput(accum.getStringStateInStore(),16) + " vs 3 1711 2104 2222 222\n");
	}
	source.setStoreValue("932359219",bufferDekatron);
	transferUnit.transfer(&source,&accum,4);
	if(!accum.getStringStateInStore().compare("3171053401442222"))
		logObj.log(LogLevel::INFO,"testshiftcircuit.cpp", "Accumulator transfer/shift TEST 1.05 SUCCESSFUL \n");
	else{
		failedTests++;
		logObj.log(LogLevel::WARNING,"testshiftcircuit.cpp","Accumulator transfer/shift TEST 1.05 shift() FAILURE "
		+ getHumanReadableOutput(accum.getStringStateInStore(),16) + " vs  3 1710 5340 1442 222\n");
	}

	source.setStoreValue("991234567",bufferDekatron);
	transferUnit.transfer(&source,&accum,0);
	if(!accum.getStringStateInStore().compare("3083399081442222"))
		logObj.log(LogLevel::INFO,"testshiftcircuit.cpp", "Accumulator transfer/shift TEST 1.06 SUCCESSFUL \n");
	else{
		failedTests++;
		logObj.log(LogLevel::WARNING,"testshiftcircuit.cpp","Accumulator transfer/shift TEST 1.06 shift() FAILURE "
		+ getHumanReadableOutput(accum.getStringStateInStore(),16) + " vs 3 0833 9908 1442 222\n");
	}

	source.setStoreValue("991234567",bufferDekatron);
	transferUnit.transfer(&source,&accum,0);
	if(!accum.getStringStateInStore().compare("2995744761442222"))
		logObj.log(LogLevel::INFO,"testshiftcircuit.cpp", "Accumulator transfer/shift TEST 1.07 SUCCESSFUL \n");
	else{
		failedTests++;
		logObj.log(LogLevel::WARNING,"testshiftcircuit.cpp","Accumulator transfer/shift TEST 1.07 shift() FAILURE "
		+ getHumanReadableOutput(accum.getStringStateInStore(),16) + " vs 2 9957 4476 1442 222\n");
	}
	source.setStoreValue("099998888",bufferDekatron);
	accum.setAccumulatorValue("8819901921600000");
	transferUnit.transfer(&source,&accum,2);
	if(!accum.getStringStateInStore().compare("8829901810400000"))
		logObj.log(LogLevel::INFO,"testshiftcircuit.cpp", "Accumulator transfer/shift TEST 1.08 SUCCESSFUL \n");
	else{
		failedTests++;
		logObj.log(LogLevel::WARNING,"testshiftcircuit.cpp","Accumulator transfer/shift TEST 1.08 shift() FAILURE "
		+ getHumanReadableOutput(accum.getStringStateInStore(),16) + " vs 8 8299 0181 0400 000\n");
	}
	source.setStoreValue("999999999",bufferDekatron);
	accum.setAccumulatorValue("9999999999999999");
	transferUnit.transfer(&source,&accum,0);
	if(!accum.getStringStateInStore().compare("9999999999999999"))
		logObj.log(LogLevel::INFO,"testshiftcircuit.cpp", "Accumulator transfer/shift TEST 1.09 SUCCESSFUL \n");
	else{
		failedTests++;
		logObj.log(LogLevel::WARNING,"testshiftcircuit.cpp","Accumulator transfer/shift TEST 1.09 shift() FAILURE "
		+ getHumanReadableOutput(accum.getStringStateInStore(),16) + " vs 9 9999 9999 9999 999\n");
	}

	source.setStoreValue("999999999",bufferDekatron);
	accum.setAccumulatorValue("9999999999999999");
	transferUnit.transfer(&source,&accum,7);
	if(!accum.getStringStateInStore().compare("9999999999999999"))
		logObj.log(LogLevel::INFO,"testshiftcircuit.cpp", "Accumulator transfer/shift TEST 1.10 SUCCESSFUL \n");
	else{
		failedTests++;
		logObj.log(LogLevel::WARNING,"testshiftcircuit.cpp","Accumulator transfer/shift TEST 1.10 shift() FAILURE "
		+ getHumanReadableOutput(accum.getStringStateInStore(),16) + " vs 9 9999 9999 9999 999\n");
	}

	/*
	 * store to accumulator subtraction (complement transfer)
	 */
	source.setStoreValue("012345678",bufferDekatron);
	accum.clearAccumulator();
	transferUnit.transferComplement(&source,&accum,0);
	if(!accum.getStringStateInStore().compare("9876543219999999"))
		logObj.log(LogLevel::INFO,"testshiftcircuit.cpp", "Accumulator transfer/shift TEST 2.01 SUCCESSFUL \n");
	else {
		failedTests++;
		logObj.log(LogLevel::WARNING,"testshiftcircuit.cpp","Accumulator transfer/shift TEST 2.01 shift() FAILURE "
		+ getHumanReadableOutput(accum.getStringStateInStore(),16) + " vs 9 8765 4321 9999 999\n");
	}
	accum.clearAccumulator();
	transferUnit.transferComplement(&source,&accum,-1);
	if(!accum.getStringStateInStore().compare("9765432199999999"))
		logObj.log(LogLevel::INFO,"testshiftcircuit.cpp", "Accumulator transfer/shift TEST 2.02 SUCCESSFUL \n");
	else{
		failedTests++;
		logObj.log(LogLevel::WARNING,"testshiftcircuit.cpp","Accumulator transfer/shift TEST 2.02 shift() FAILURE "
		+ getHumanReadableOutput(accum.getStringStateInStore(),16) + " vs 9 7654 3219 9999 999\n");
	}
	source.setStoreValue("111111111",bufferDekatron);
	transferUnit.transferComplement(&source,&accum,7);
	if(!accum.getStringStateInStore().compare("8654321088888888"))
		logObj.log(LogLevel::INFO,"testshiftcircuit.cpp", "Accumulator transfer/shift TEST 2.03 SUCCESSFUL \n");
	else{
		failedTests++;
		logObj.log(LogLevel::WARNING,"testshiftcircuit.cpp","Accumulator transfer/shift TEST 2.03 shift() FAILURE "
		+ getHumanReadableOutput(accum.getStringStateInStore(),16) + " vs 8 6543 2108 8888 888\n");
	}

	source.setStoreValue("071433102",bufferDekatron);
	transferUnit.transferComplement(&source,&accum,0);
	if(!accum.getStringStateInStore().compare("7939990068888888"))
		logObj.log(LogLevel::INFO,"testshiftcircuit.cpp", "Accumulator transfer/shift TEST 2.04 SUCCESSFUL \n");
	else{
		failedTests++;
		logObj.log(LogLevel::WARNING,"testshiftcircuit.cpp","Accumulator transfer/shift TEST 2.04 shift() FAILURE "
		+ getHumanReadableOutput(accum.getStringStateInStore(),16) + " vs 7 9399 9006 8888 888\n");
	}
	source.setStoreValue("932359219",bufferDekatron);
	transferUnit.transferComplement(&source,&accum,4);
	if(!accum.getStringStateInStore().compare("7940057709668888"))
		logObj.log(LogLevel::INFO,"testshiftcircuit.cpp", "Accumulator transfer/shift TEST 2.05 SUCCESSFUL \n");
	else{
		failedTests++;
		logObj.log(LogLevel::WARNING,"testshiftcircuit.cpp","Accumulator transfer/shift TEST 2.05 shift() FAILURE "
		+ getHumanReadableOutput(accum.getStringStateInStore(),16) + " vs  7 9400 5770 9668 888\n");
	}

	source.setStoreValue("991234567",bufferDekatron);
	transferUnit.transferComplement(&source,&accum,0);
	if(!accum.getStringStateInStore().compare("8027712029668888"))
		logObj.log(LogLevel::INFO,"testshiftcircuit.cpp", "Accumulator transfer/shift TEST 2.06 SUCCESSFUL \n");
	else{
		failedTests++;
		logObj.log(LogLevel::WARNING,"testshiftcircuit.cpp","Accumulator transfer/shift TEST 2.06 shift() FAILURE "
		+ getHumanReadableOutput(accum.getStringStateInStore(),16) + " vs 8 0277 1202 9668 888\n");
	}
	// 0 1234 5678 9000 000 
	// 0 0876 5432 0000 000 +
	// 0 2111 1110 9000 000
	source.setStoreValue("991234567",bufferDekatron);
	accum.setAccumulatorValue("0123456789000000");
	transferUnit.transferComplement(&source,&accum,0);
	if(!accum.getStringStateInStore().compare("0211111109000000"))
		logObj.log(LogLevel::INFO,"testshiftcircuit.cpp", "Accumulator transfer/shift TEST 2.07 SUCCESSFUL \n");
	else{
		failedTests++;
		logObj.log(LogLevel::WARNING,"testshiftcircuit.cpp","Accumulator transfer/shift TEST 2.07 shift() FAILURE "
		+ getHumanReadableOutput(accum.getStringStateInStore(),16) + " vs 0 2111 1110 9000 000\n");
	}
	// 0 2111 1110 9000 000
	// 0 9999 0000 0000 000 -
	// - 7887 8889 1000 000 = 9 2112 1110 8999 999
	source.setStoreValue("099990000",bufferDekatron);
	transferUnit.transferComplement(&source,&accum,0);
	if(!accum.getStringStateInStore().compare("9211211108999999"))
		logObj.log(LogLevel::INFO,"testshiftcircuit.cpp", "Accumulator transfer/shift TEST 2.08 SUCCESSFUL \n");
	else{
		failedTests++;
		logObj.log(LogLevel::WARNING,"testshiftcircuit.cpp","Accumulator transfer/shift TEST 2.08 shift() FAILURE "
		+ getHumanReadableOutput(accum.getStringStateInStore(),16) + " vs 9 2112 1110 8999 999\n");
	}

	source.setStoreValue("999999999",bufferDekatron);
	accum.setAccumulatorValue("9999999999999999");
	transferUnit.transfer(&source,&accum,7);
	if(!accum.getStringStateInStore().compare("9999999999999999"))
		logObj.log(LogLevel::INFO,"testshiftcircuit.cpp", "Accumulator transfer/shift TEST 2.09 SUCCESSFUL \n");
	else{
		failedTests++;
		logObj.log(LogLevel::WARNING,"testshiftcircuit.cpp","Accumulator transfer/shift TEST 2.09 shift() FAILURE "
		+ getHumanReadableOutput(accum.getStringStateInStore(),16) + " vs 9 9999 9999 9999 999\n");
	}

	source.setStoreValue("011653443",bufferDekatron);
	accum.setAccumulatorValue("0987698765432543");
	transferUnit.transferComplement(&source,&accum,7);
	if(!accum.getStringStateInStore().compare("0987698753779100"))
		logObj.log(LogLevel::INFO,"testshiftcircuit.cpp", "Accumulator transfer/shift TEST 2.10 SUCCESSFUL \n");
	else{
		failedTests++;
		logObj.log(LogLevel::WARNING,"testshiftcircuit.cpp", "Accumulator transfer/shift TEST 2.10 shift() FAILURE "
		+ getHumanReadableOutput(accum.getStringStateInStore(),16) + " vs 0 9876 9875 3779 100\n");
	}

	logObj.log(LogLevel::INFO, "testshiftcircuit.cpp","FINISH shiftcircuit.cpp TESTS\n");
}

std::string TestShiftCircuit::getHumanReadableOutput(std::string inp,int size){
	inp.insert(1," ");
	inp.insert(6," ");
	if(size == 16) {
		inp.insert(11," ");
		inp.insert(16," ");
	}
	return inp;
}


