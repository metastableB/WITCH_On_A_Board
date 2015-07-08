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
	std::cout << "Testing shiftcircuit.cpp"<< std::endl;
	Dekatron bufferDekatron[9];
	DekatronStore source, destination;
	TransferUnit transferUnit;
	ShiftCircuit shiftCircuit;

	source.setStoreValue("023456789",bufferDekatron);
	transferUnit.transfer(&source,&destination,-1);
	if(!destination.getStringStateInStore().compare("034567890"))
		std::cout << "ShiftCircuit TEST 1.1 SUCCESSFUL \n";
	else{
		failedTests++;
		std::cout << "ShiftCircuit TEST 1.1 shift() FAILURE "  << destination.getStringStateInStore() << " vs 034567890\n";
	}
	destination.setStoreValue("000000000",bufferDekatron);
	transferUnit.transfer(&source,&destination);
	if(!destination.getStringStateInStore().compare("023456789"))
			std::cout << "ShiftCircuit TEST 1.2 SUCCESSFUL \n";
	else{
		failedTests++;
		std::cout << "ShiftCircuit TEST 1.2 shift() FAILURE " << destination.getStringStateInStore() << " vs 023456789\n";
	}
	destination.setStoreValue("000000000",bufferDekatron);
	transferUnit.transfer(&source,&destination,0);
	if(!destination.getStringStateInStore().compare("023456789"))
			std::cout << "ShiftCircuit TEST 1.3 SUCCESSFUL \n";
	else{
		failedTests++;
		std::cout << "ShiftCircuit TEST 1.3 shift() FAILURE " << destination.getStringStateInStore() << " vs 023456789\n";
	}
	destination.setStoreValue("000000000",bufferDekatron);
	transferUnit.transfer(&source,&destination,1);
	if(!destination.getStringStateInStore().compare("002345678"))
			std::cout << "ShiftCircuit TEST 1.4 SUCCESSFUL \n";
	else{
		failedTests++;
		std::cout << "ShiftCircuit TEST 1.4 shift() FAILURE " << destination.getStringStateInStore() << " vs 002345678\n";
	}
	destination.setStoreValue("000000000",bufferDekatron);
	transferUnit.transfer(&source,&destination,3);
	if(!destination.getStringStateInStore().compare("000023456"))
			std::cout << "ShiftCircuit TEST 1.5 SUCCESSFUL \n";
	else{
		failedTests++;
		std::cout << "ShiftCircuit TEST 1.5 shift() FAILURE " << destination.getStringStateInStore() << " vs 000023456\n";
	}
	destination.setStoreValue("000000000",bufferDekatron);
	source.setStoreValue("912345678",bufferDekatron);
	transferUnit.transfer(&source,&destination,7);
	if(!destination.getStringStateInStore().compare("999999991"))
			std::cout << "ShiftCircuit TEST 1.6 SUCCESSFUL \n";
	else{
		failedTests++;
		std::cout << "ShiftCircuit TEST 1.6 shift() FAILURE " << destination.getStringStateInStore() << " vs 999999991\n";
	}

	// Adding both zeros
	source.setStoreValue("000000000",bufferDekatron);
	destination.setStoreValue("000000000",bufferDekatron);
	transferUnit.transfer(&source,&destination,7);
	if(!destination.getStringStateInStore().compare("000000000"))
		std::cout << "ShiftCircuit TEST 2.1 SUCCESSFUL" << std::endl;
	else{
		failedTests++;
		std::cout << "ShiftCircuit TEST 2.1 shift() FAILURE" << std::endl;
	}
	transferUnit.transfer(&destination, &source);
	if(!source.getStringStateInStore().compare("000000000"))
		std::cout << "ShiftCircuit TEST 2.2 SUCCESSFUL" << std::endl;
	else{
		failedTests++;
		std::cout << "ShiftCircuit TEST 2.2 shift() FAILURE" << std::endl;
	}

	// Performing simple additions by pulsing
	int pulse[9] = {1,1,1,1,1,1,1,1,1};
	source.pulseStore(pulse, bufferDekatron);
	source.pulseStore(pulse, bufferDekatron);
	transferUnit.transfer(&source,&destination,7);
	if(!destination.getStringStateInStore().compare("222222222"))
		std::cout << "ShiftCircuit TEST 3.1 SUCCESSFUL" << std::endl;
	else{
		failedTests++;
		std::cout << "ShiftCircuit TEST 3.1 shift() FAILURE " << destination.getStringStateInStore() << " vs 222222222\n";
	}
	transferUnit.transfer(&destination, &source,-1);
	if(!source.getStringStateInStore().compare("444444444"))
		std::cout << "ShiftCircuit TEST 3.2 SUCCESSFUL" << std::endl;
	else{
		failedTests++;
		std::cout << "ShiftCircuit TEST 3.2 shift() FAILURE " << source.getStringStateInStore() << " vs 444444444\n";
	}

	source.setStoreValue("977777977",bufferDekatron);
	destination.setStoreValue("200000002",bufferDekatron);
	
	// source is  9 7777 7977, dest is 2 0000 0002
	transferUnit.transfer(&source,&destination,-1);
	if(!destination.getStringStateInStore().compare("177779782"))
		std::cout << "ShiftCircuit TEST 4.1 SUCCESSFUL" << std::endl;
	else{
		failedTests++;
		std::cout << "ShiftCircuit TEST 4.1 shift() FAILURE " <<  destination.getStringStateInStore() << " vs 177779782\n";
	}
	transferUnit.transfer(&destination, &source,5);
	if(!source.getStringStateInStore().compare("088889755"))
		std::cout << "ShiftCircuit TEST 4.2 SUCCESSFUL" << std::endl;
	else{
		failedTests++;
		std::cout << "ShiftCircuit TEST 4.2 shift() FAILURE " <<  source.getStringStateInStore() << " vs 088889755\n";
	}

	// Performing multiple addition tests
	source.setStoreValue("555555555", bufferDekatron);
	destination.setStoreValue("444444444", bufferDekatron);
	transferUnit.transfer(&source, &destination,3);
	if(!destination.getStringStateInStore().compare("999999999"))
		std::cout << "ShiftCircuit TEST 5.1 SUCCESSFUL" << std::endl;
	else{
		failedTests++;
		std::cout << "ShiftCircuit TEST 5.1 shift() FAILURE " <<  destination.getStringStateInStore() << " vs 999999999\n";
	}
	transferUnit.transfer(&destination, &source,7);
	if(!source.getStringStateInStore().compare("555555555"))
		std::cout << "ShiftCircuit TEST 5.2 SUCCESSFUL" << std::endl;
	else{
		failedTests++;
		std::cout << "ShiftCircuit TEST 5.2 shift() FAILURE " <<  source.getStringStateInStore() << " vs 555555555\n";
	}

	source.setStoreValue("012345678", bufferDekatron);
	destination.setStoreValue("991111111", bufferDekatron);
	transferUnit.transfer(&source, &destination,4);
	if(!destination.getStringStateInStore().compare("991112345"))
		std::cout << "ShiftCircuit TEST 5.3 SUCCESSFUL" << std::endl;
	else{
		failedTests++;
		std::cout << "ShiftCircuit TEST 5.3 shift() FAILURE" << std::endl;
	}
	transferUnit.transfer(&destination, &source,1);
	if(!source.getStringStateInStore().compare("011456913"))
		std::cout << "ShiftCircuit TEST 5.4 SUCCESSFUL" << std::endl;
	else{
		failedTests++;
		std::cout << "ShiftCircuit TEST 5.4 shift() FAILURE" << source.getStringStateInStore() << " vs 011456913\n";
	}

	source.setStoreValue("000000000", bufferDekatron);
	destination.setStoreValue("000000000", bufferDekatron);
	// Subtracting both zeros
	transferUnit.transferComplement(&source,&destination,7);
	if(!destination.getStringStateInStore().compare("999999999"))
		std::cout << "ShiftCircuit TEST 6.1 SUCCESSFUL" << std::endl;
	else{
		failedTests++;
		std::cout << "ShiftCircuit TEST 6.1 shift() FAILURE " << source.getStringStateInStore() <<" d: " << destination.getStringStateInStore() << " " << std::endl;
	}
	transferUnit.transferComplement(&destination, &source);
	if(!source.getStringStateInStore().compare("000000000"))
		std::cout << "ShiftCircuit TEST 6.2 SUCCESSFUL" << std::endl;
	else{
		failedTests++;
		std::cout << "ShiftCircuit TEST 6.2 shift() FAILURE " << source.getStringStateInStore() <<" d: " << destination.getStringStateInStore() << " " << std::endl;
	}

	// Performing simple subtractions after pulsing
	source.pulseStore(pulse, bufferDekatron);
	source.pulseStore(pulse, bufferDekatron);
	transferUnit.transferComplement(&source,&destination,-1);
	if(!destination.getStringStateInStore().compare("777777777"))
		std::cout << "ShiftCircuit TEST 7.1 SUCCESSFUL" << std::endl;
	else{
		failedTests++;
		std::cout << "ShiftCircuit TEST 7.1 shift() FAILURE " <<  destination.getStringStateInStore() << " vs 777777777" << std::endl;
	}
	transferUnit.transferComplement(&destination, &source,4);
	if(!source.getStringStateInStore().compare("444444444"))
		std::cout << "ShiftCircuit TEST 7.2 SUCCESSFUL" << std::endl;
	else{
		failedTests++;
		std::cout << "ShiftCircuit TEST 7.2 shift() FAILURE " << source.getStringStateInStore() <<" vs 444444444\n";
	}

	source.pulseStore(pulse, bufferDekatron);
	source.pulseStore(pulse, bufferDekatron);
	source.pulseStore(pulse, bufferDekatron);
	destination.pulseStore(pulse, bufferDekatron);
	destination.pulseStore(pulse, bufferDekatron);
	destination.pulseStore(pulse, bufferDekatron);
	transferUnit.transferComplement(&source,&destination);
	if(!destination.getStringStateInStore().compare("222222222"))
		std::cout << "ShiftCircuit TEST 8.1 SUCCESSFUL" << std::endl;
	else {
		failedTests++;
		std::cout << "ShiftCircuit TEST 8.1 shift() FAILURE " << destination.getStringStateInStore() <<" vs 222222222\n";
	}
	transferUnit.transferComplement(&destination, &source,3);
	if(!source.getStringStateInStore().compare("555555555"))
		std::cout << "ShiftCircuit TEST 8.2 SUCCESSFUL" << std::endl;
	else {
		failedTests++;
		std::cout << "ShiftCircuit TEST 8.2 shift() FAILURE " << source.getStringStateInStore() <<" vs 555555555 ";
	}

	// Performing multiple subtraction tests
	source.setStoreValue("000000005", bufferDekatron);
	destination.setStoreValue("000000004", bufferDekatron);
	transferUnit.transferComplement(&source, &destination,-1);
	// -46 : 9 9999 9953
	if(!destination.getStringStateInStore().compare("999999953"))
		std::cout << "ShiftCircuit TEST 9.1 SUCCESSFUL" << std::endl;
	else {
		failedTests++;
		std::cout << "ShiftCircuit TEST 9.1 shift() FAILURE " << source.getStringStateInStore()
		<<" d: " << destination.getStringStateInStore() << " " << std::endl;
	}
	transferUnit.transferComplement(&destination, &source,-1);
	// 5 - -460 = 465
	if(!source.getStringStateInStore().compare("000000465"))
		std::cout << "ShiftCircuit TEST 9.2 SUCCESSFUL" << std::endl;
	else {
		failedTests++;
		std::cout << "ShiftCircuit TEST 9.2 shift() FAILURE " << source.getStringStateInStore()
		<<" d: " << destination.getStringStateInStore() << " " << std::endl;
	}

	source.setStoreValue("000000000", bufferDekatron);
	destination.setStoreValue("991111111", bufferDekatron);
	// - 0 0888 8888 - 0 = 0 0888 8888 = 9 9111 1111
	transferUnit.transferComplement(&source, &destination);
	if(!destination.getStringStateInStore().compare("991111111"))
		std::cout << "ShiftCircuit TEST 9.3 SUCCESSFUL" << std::endl;
	else {
		failedTests++;
		std::cout << "ShiftCircuit TEST 9.3 shift() FAILURE " << source.getStringStateInStore()
		<<" d: " << destination.getStringStateInStore() << " " << std::endl;
	}
	source.setStoreValue("991111111", bufferDekatron);
	transferUnit.transferComplement(&destination, &source,7);
	if(!source.getStringStateInStore().compare("991111111"))
		std::cout << "ShiftCircuit TEST 9.4 SUCCESSFUL" << std::endl;
	else {
		failedTests++;
		std::cout << "ShiftCircuit TEST 9.4 shift() FAILURE " << source.getStringStateInStore()
		<<" d: " << destination.getStringStateInStore() << " " << std::endl;
	}

	source.setStoreValue("088448800", bufferDekatron);
	destination.setStoreValue("991001234", bufferDekatron);
	transferUnit.transferComplement(&destination, &source,0);
	if(!source.getStringStateInStore().compare("097447565"))
		std::cout << "ShiftCircuit TEST 9.5 SUCCESSFUL" << std::endl;
	else {
		failedTests++;
		std::cout << "ShiftCircuit TEST 9.5 shift() FAILURE " << source.getStringStateInStore()
		<<" d: " << destination.getStringStateInStore() << " " << std::endl;
	}
	transferUnit.transferComplement(&source, &destination,2);
	if(!destination.getStringStateInStore().compare("990026759"))
		std::cout << "ShiftCircuit TEST 9.6 SUCCESSFUL" << std::endl;
	else {
		failedTests++;
		std::cout << "ShiftCircuit TEST 9.6 shift() FAILURE " << source.getStringStateInStore()
		<<" d: " << destination.getStringStateInStore() << " " << std::endl;
	}

	/********************************************
	 *              Accumulator tests           *
	 ********************************************/
	Accumulator accum;
	std::cout << "\nShifts and transfer tests with accumulator\n";
	// Store to Accum transfer
	source.setStoreValue("123456789",bufferDekatron);
	transferUnit.transfer(&source,&accum,0);
	if(!accum.getStringStateInStore().compare("1234567891111111"))
		std::cout << "Accumulator transfer/shift TEST 1.01 SUCCESSFUL \n";
	else{
		failedTests++;
		std::cout << "Accumulator transfer/shift TEST 1.01 shift() FAILURE "
		<< getHumanReadableOutput(accum.getStringStateInStore(),16) << " vs 1 2345 6789 1111 111\n";
	}
	accum.clearAccumulator();
	transferUnit.transfer(&source,&accum,-1);
	if(!accum.getStringStateInStore().compare("1345678911111111"))
		std::cout << "Accumulator transfer/shift TEST 1.02 SUCCESSFUL \n";
	else{
		failedTests++;
		std::cout << "Accumulator transfer/shift TEST 1.02 shift() FAILURE "
		<< getHumanReadableOutput(accum.getStringStateInStore(),16) << " vs 1 3456 7891 1111 111\n";
	}
	source.setStoreValue("111111111",bufferDekatron);
	transferUnit.transfer(&source,&accum,7);
	if(!accum.getStringStateInStore().compare("2456790022222222"))
		std::cout << "Accumulator transfer/shift TEST 1.03 SUCCESSFUL \n";
	else{
		failedTests++;
		std::cout << "Accumulator transfer/shift TEST 1.03 shift() FAILURE "
		<< getHumanReadableOutput(accum.getStringStateInStore(),16) << " vs 2 4567 9002 2222 222\n";
	}

	source.setStoreValue("071433102",bufferDekatron);
	transferUnit.transfer(&source,&accum,0);
	if(!accum.getStringStateInStore().compare("3171121042222222"))
		std::cout << "Accumulator transfer/shift TEST 1.04 SUCCESSFUL \n";
	else{
		failedTests++;
		std::cout << "Accumulator transfer/shift TEST 1.04 shift() FAILURE "
		<< getHumanReadableOutput(accum.getStringStateInStore(),16) << " vs 3 1711 2104 2222 222\n";
	}
	source.setStoreValue("932359219",bufferDekatron);
	transferUnit.transfer(&source,&accum,4);
	if(!accum.getStringStateInStore().compare("3171053401442222"))
		std::cout << "Accumulator transfer/shift TEST 1.05 SUCCESSFUL \n";
	else{
		failedTests++;
		std::cout << "Accumulator transfer/shift TEST 1.05 shift() FAILURE "
		<< getHumanReadableOutput(accum.getStringStateInStore(),16) << " vs  3 1710 5340 1442 222\n";
	}

	source.setStoreValue("991234567",bufferDekatron);
	transferUnit.transfer(&source,&accum,0);
	if(!accum.getStringStateInStore().compare("3083399081442222"))
		std::cout << "Accumulator transfer/shift TEST 1.06 SUCCESSFUL \n";
	else{
		failedTests++;
		std::cout << "Accumulator transfer/shift TEST 1.06 shift() FAILURE "
		<< getHumanReadableOutput(accum.getStringStateInStore(),16) << " vs 3 0833 9908 1442 222\n";
	}

	source.setStoreValue("991234567",bufferDekatron);
	transferUnit.transfer(&source,&accum,0);
	if(!accum.getStringStateInStore().compare("2995744761442222"))
		std::cout << "Accumulator transfer/shift TEST 1.07 SUCCESSFUL \n";
	else{
		failedTests++;
		std::cout << "Accumulator transfer/shift TEST 1.07 shift() FAILURE "
		<< getHumanReadableOutput(accum.getStringStateInStore(),16) << " vs 2 9957 4476 1442 222\n";
	}
	source.setStoreValue("099998888",bufferDekatron);
	accum.setAccumulatorValue("8819901921600000");
	transferUnit.transfer(&source,&accum,2);
	if(!accum.getStringStateInStore().compare("8829901810400000"))
		std::cout << "Accumulator transfer/shift TEST 1.08 SUCCESSFUL \n";
	else{
		failedTests++;
		std::cout << "Accumulator transfer/shift TEST 1.08 shift() FAILURE "
		<< getHumanReadableOutput(accum.getStringStateInStore(),16) << " vs 8 8299 0181 0400 000\n";
	}
	source.setStoreValue("999999999",bufferDekatron);
	accum.setAccumulatorValue("9999999999999999");
	transferUnit.transfer(&source,&accum,0);
	if(!accum.getStringStateInStore().compare("9999999999999999"))
		std::cout << "Accumulator transfer/shift TEST 1.09 SUCCESSFUL \n";
	else{
		failedTests++;
		std::cout << "Accumulator transfer/shift TEST 1.09 shift() FAILURE "
		<< getHumanReadableOutput(accum.getStringStateInStore(),16) << " vs 9 9999 9999 9999 999\n";
	}

	source.setStoreValue("999999999",bufferDekatron);
	accum.setAccumulatorValue("9999999999999999");
	transferUnit.transfer(&source,&accum,7);
	if(!accum.getStringStateInStore().compare("9999999999999999"))
		std::cout << "Accumulator transfer/shift TEST 1.10 SUCCESSFUL \n";
	else{
		failedTests++;
		std::cout << "Accumulator transfer/shift TEST 1.10 shift() FAILURE "
		<< getHumanReadableOutput(accum.getStringStateInStore(),16) << " vs 9 9999 9999 9999 999\n";
	}


	/*destination.setStoreValue("000000000",bufferDekatron);
	transferUnit.transfer(&source,&destination,1);
	if(!destination.getStringStateInStore().compare("002345678"))
			std::cout << "Accumulator transfer/shift TEST 1.4 SUCCESSFUL \n";
		else{
			failedTests++;
			std::cout << "Accumulator transfer/shift TEST 1.4 shift() FAILURE " << destination.getStringStateInStore() << " vs 002345678\n";
	destination.setStoreValue("000000000",bufferDekatron);
	}
	transferUnit.transfer(&source,&destination,3);
	if(!destination.getStringStateInStore().compare("000023456"))
			std::cout << "Accumulator transfer/shift TEST 1.5 SUCCESSFUL \n";
		else
			std::cout << "Accumulator transfer/shift TEST 1.5 shift() FAILURE " << destination.getStringStateInStore() << " vs 000023456\n";
	destination.setStoreValue("000000000",bufferDekatron);
	source.setStoreValue("912345678",bufferDekatron);
	transferUnit.transfer(&source,&destination,7);
	if(!destination.getStringStateInStore().compare("900000001"))
			std::cout << "Accumulator transfer/shift TEST 1.6 SUCCESSFUL \n";
		else
			std::cout << "Accumulator transfer/shift TEST 1.6 shift() FAILURE " << destination.getStringStateInStore() << " vs 900000001\n";

	// Adding both zeros
	source.setStoreValue("000000000",bufferDekatron);
	destination.setStoreValue("000000000",bufferDekatron);
	transferUnit.transfer(&source,&destination,7);
	if(!destination.getStringStateInStore().compare("000000000"))
		std::cout << "Accumulator transfer/shift TEST 2.1 SUCCESSFUL" << std::endl;
	else
		std::cout << "Accumulator transfer/shift TEST 2.1 shift() FAILURE" << std::endl;
	transferUnit.transfer(&destination, &source);
	if(!source.getStringStateInStore().compare("000000000"))
		std::cout << "Accumulator transfer/shift TEST 2.2 SUCCESSFUL" << std::endl;
	else
		std::cout << "Accumulator transfer/shift TEST 2.2 shift() FAILURE" << std::endl;

	// Performing simple additions by pulsing
	int pulse[9] = {1,1,1,1,1,1,1,1,1};
	source.pulseStore(pulse, bufferDekatron);
	source.pulseStore(pulse, bufferDekatron);
	transferUnit.transfer(&source,&destination,7);
	if(!destination.getStringStateInStore().compare("200000002"))
		std::cout << "Accumulator transfer/shift TEST 3.1 SUCCESSFUL" << std::endl;
	else
		std::cout << "Accumulator transfer/shift TEST 3.1 shift() FAILURE" << std::endl;
	transferUnit.transfer(&destination, &source,-1);
	if(!source.getStringStateInStore().compare("422222242"))
		std::cout << "Accumulator transfer/shift TEST 3.2 SUCCESSFUL" << std::endl;
	else
		std::cout << "Accumulator transfer/shift TEST 3.2 shift() FAILURE " << source.getStringStateInStore() << " vs 222222242\n";

	// Creating carry over by pulsing
	source.pulseStore(pulse, bufferDekatron);
	source.pulseStore(pulse, bufferDekatron);
	source.pulseStore(pulse, bufferDekatron);
	source.pulseStore(pulse, bufferDekatron);
	source.pulseStore(pulse, bufferDekatron);

	// source is  9 7777 7977, dest is 2 0000 0002
	transferUnit.transfer(&source,&destination,-1);
	if(!destination.getStringStateInStore().compare("177777973"))
		std::cout << "Accumulator transfer/shift TEST 4.1 SUCCESSFUL" << std::endl;
	else
		std::cout << "Accumulator transfer/shift TEST 4.1 shift() FAILURE " <<  destination.getStringStateInStore() << " vs 177777973\n";
	transferUnit.transfer(&destination, &source,5);
	if(!source.getStringStateInStore().compare("077778575"))
		std::cout << "Accumulator transfer/shift TEST 4.2 SUCCESSFUL" << std::endl;
	else
		std::cout << "Accumulator transfer/shift TEST 4.2 shift() FAILURE " <<  source.getStringStateInStore() << " vs 077778575\n";

	// Performing multiple addition tests
	source.setStoreValue("555555555", bufferDekatron);
	destination.setStoreValue("444444444", bufferDekatron);
	transferUnit.transfer(&source, &destination,3);
	if(!destination.getStringStateInStore().compare("944499999"))
		std::cout << "Accumulator transfer/shift TEST 5.1 SUCCESSFUL" << std::endl;
	else
		std::cout << "Accumulator transfer/shift TEST 5.1 shift() FAILURE " <<  destination.getStringStateInStore() << " vs 944499999\n";
	transferUnit.transfer(&destination, &source,7);
	if(!source.getStringStateInStore().compare("455555560"))
		std::cout << "Accumulator transfer/shift TEST 5.2 SUCCESSFUL" << std::endl;
	else
		std::cout << "Accumulator transfer/shift TEST 5.2 shift() FAILURE " <<  source.getStringStateInStore() << " vs 455555560\n";

	source.setStoreValue("012345678", bufferDekatron);
	destination.setStoreValue("991111111", bufferDekatron);
	transferUnit.transfer(&source, &destination,4);
	if(!destination.getStringStateInStore().compare("991112345"))
		std::cout << "Accumulator transfer/shift TEST 5.3 SUCCESSFUL" << std::endl;
	else
		std::cout << "Accumulator transfer/shift TEST 5.3 shift() FAILURE" << std::endl;
	transferUnit.transfer(&destination, &source,1);
	if(!source.getStringStateInStore().compare("921456912"))
		std::cout << "Accumulator transfer/shift TEST 5.4 SUCCESSFUL" << std::endl;
	else
		std::cout << "Accumulator transfer/shift TEST 5.4 shift() FAILURE" << std::endl;


	source.setStoreValue("000000000", bufferDekatron);
	destination.setStoreValue("000000000", bufferDekatron);
	// Subtracting both zeros
	transferUnit.transferComplement(&source,&destination,7);
	if(!destination.getStringStateInStore().compare("999999999"))
		std::cout << "Accumulator transfer/shift TEST 6.1 SUCCESSFUL" << std::endl;
	else
		std::cout << "Accumulator transfer/shift TEST 6.1 shift() FAILURE " << source.getStringStateInStore() <<" d: " << destination.getStringStateInStore() << " " << std::endl;
	transferUnit.transferComplement(&destination, &source);
	if(!source.getStringStateInStore().compare("000000000"))
		std::cout << "Accumulator transfer/shift TEST 6.2 SUCCESSFUL" << std::endl;
	else
		std::cout << "Accumulator transfer/shift TEST 6.2 shift() FAILURE " << source.getStringStateInStore() <<" d: " << destination.getStringStateInStore() << " " << std::endl;

	// Performing simple subtractions after pulsing
	source.pulseStore(pulse, bufferDekatron);
	source.pulseStore(pulse, bufferDekatron);
	transferUnit.transferComplement(&source,&destination,-1);
	if(!destination.getStringStateInStore().compare("777777779"))
		std::cout << "Accumulator transfer/shift TEST 7.1 SUCCESSFUL" << std::endl;
	else
		std::cout << "Accumulator transfer/shift TEST 7.1 shift() FAILURE " << source.getStringStateInStore() <<" d: " << destination.getStringStateInStore() << " " << std::endl;
	transferUnit.transferComplement(&destination, &source,4);
	if(!source.getStringStateInStore().compare("522214444"))
		std::cout << "Accumulator transfer/shift TEST 7.2 SUCCESSFUL" << std::endl;
	else
		std::cout << "Accumulator transfer/shift TEST 7.2 shift() FAILURE " << source.getStringStateInStore() <<" d: " << destination.getStringStateInStore() << " " << std::endl;

	source.pulseStore(pulse, bufferDekatron);
	source.pulseStore(pulse, bufferDekatron);
	source.pulseStore(pulse, bufferDekatron);
	destination.pulseStore(pulse, bufferDekatron);
	destination.pulseStore(pulse, bufferDekatron);
	destination.pulseStore(pulse, bufferDekatron);
	transferUnit.transferComplement(&source,&destination);
	if(!destination.getStringStateInStore().compare("144452224"))
		std::cout << "Accumulator transfer/shift TEST 8.1 SUCCESSFUL" << std::endl;
	else
		std::cout << "Accumulator transfer/shift TEST 8.1 shift() FAILURE " << source.getStringStateInStore() <<" d: " << destination.getStringStateInStore() << " " << std::endl;
	transferUnit.transferComplement(&destination, &source,3);
	if(!source.getStringStateInStore().compare("755503325"))
		std::cout << "Accumulator transfer/shift TEST 8.2 SUCCESSFUL" << std::endl;
	else
		std::cout << "Accumulator transfer/shift TEST 8.2 shift() FAILURE " << source.getStringStateInStore() <<" d: " << destination.getStringStateInStore() << " " << std::endl;

	// Performing multiple subtraction tests
	source.setStoreValue("000000005", bufferDekatron);
	destination.setStoreValue("000000004", bufferDekatron);
	transferUnit.transferComplement(&source, &destination,-1);
	// -46 : 9 9999 9953
	if(!destination.getStringStateInStore().compare("999999953"))
		std::cout << "Accumulator transfer/shift TEST 9.1 SUCCESSFUL" << std::endl;
	else
		std::cout << "Accumulator transfer/shift TEST 9.1 shift() FAILURE " << source.getStringStateInStore() <<" d: " << destination.getStringStateInStore() << " " << std::endl;
	transferUnit.transferComplement(&destination, &source,-1);
	// 5 - -469 = 474
	if(!source.getStringStateInStore().compare("000000474"))
		std::cout << "Accumulator transfer/shift TEST 9.2 SUCCESSFUL" << std::endl;
	else
		std::cout << "Accumulator transfer/shift TEST 9.2 shift() FAILURE " << source.getStringStateInStore() <<" d: " << destination.getStringStateInStore() << " " << std::endl;

	source.setStoreValue("000000000", bufferDekatron);
	destination.setStoreValue("991111111", bufferDekatron);
	// - 0 0888 8888 - 0 = 0 0888 8888 = 9 9111 1111
	transferUnit.transferComplement(&source, &destination);
	if(!destination.getStringStateInStore().compare("991111111"))
		std::cout << "Accumulator transfer/shift TEST 9.3 SUCCESSFUL" << std::endl;
	else
		std::cout << "Accumulator transfer/shift TEST 9.3 shift() FAILURE " << source.getStringStateInStore() <<" d: " << destination.getStringStateInStore() << " " << std::endl;
	source.setStoreValue("991111111", bufferDekatron);
	transferUnit.transferComplement(&destination, &source,7);
	if(!source.getStringStateInStore().compare("091111102"))
		std::cout << "Accumulator transfer/shift TEST 9.4 SUCCESSFUL" << std::endl;
	else
		std::cout << "Accumulator transfer/shift TEST 9.4 shift() FAILURE " << source.getStringStateInStore() <<" d: " << destination.getStringStateInStore() << " " << std::endl;

	source.setStoreValue("088448800", bufferDekatron);
	destination.setStoreValue("991001234", bufferDekatron);
	transferUnit.transferComplement(&destination, &source,0);
	if(!source.getStringStateInStore().compare("097447565"))
		std::cout << "Accumulator transfer/shift TEST 9.5 SUCCESSFUL" << std::endl;
	else
		std::cout << "Accumulator transfer/shift TEST 9.5 shift() FAILURE " << source.getStringStateInStore() <<" d: " << destination.getStringStateInStore() << " " << std::endl;
	transferUnit.transferComplement(&source, &destination,2);
	if(!destination.getStringStateInStore().compare("990026759"))
		std::cout << "Accumulator transfer/shift TEST 9.6 SUCCESSFUL" << std::endl;
	else
		std::cout << "Accumulator transfer/shift TEST 9.6 shift() FAILURE " << source.getStringStateInStore() <<" d: " << destination.getStringStateInStore() << " " << std::endl;
*/
	std::cout << "FINISH shiftcircuit.cpp TESTS\n";
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


