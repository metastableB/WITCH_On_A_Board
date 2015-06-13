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
		std::cout << "ShiftCircuit TEST 1.1 SUCCESS \n";
	else
		std::cout << "ShiftCircuit TEST 1.1 shift() FAILURE "  << destination.getStringStateInStore() << " vs 034567890\n";
	destination.setStoreValue("000000000",bufferDekatron);
	transferUnit.transfer(&source,&destination);
	if(!destination.getStringStateInStore().compare("023456789"))
			std::cout << "ShiftCircuit TEST 1.2 SUCCESS \n";
		else
			std::cout << "ShiftCircuit TEST 1.2 shift() FAILURE " << destination.getStringStateInStore() << " vs 023456789\n";
	destination.setStoreValue("000000000",bufferDekatron);
	transferUnit.transfer(&source,&destination,0);
	if(!destination.getStringStateInStore().compare("023456789"))
			std::cout << "ShiftCircuit TEST 1.3 SUCCESS \n";
		else
			std::cout << "ShiftCircuit TEST 1.3 shift() FAILURE " << destination.getStringStateInStore() << " vs 023456789\n";
	destination.setStoreValue("000000000",bufferDekatron);
	transferUnit.transfer(&source,&destination,1);
	if(!destination.getStringStateInStore().compare("002345678"))
			std::cout << "ShiftCircuit TEST 1.4 SUCCESS \n";
		else
			std::cout << "ShiftCircuit TEST 1.4 shift() FAILURE " << destination.getStringStateInStore() << " vs 002345678\n";
	destination.setStoreValue("000000000",bufferDekatron);
	transferUnit.transfer(&source,&destination,3);
	if(!destination.getStringStateInStore().compare("000023456"))
			std::cout << "ShiftCircuit TEST 1.5 SUCCESS \n";
		else
			std::cout << "ShiftCircuit TEST 1.5 shift() FAILURE " << destination.getStringStateInStore() << " vs 000023456\n";
	destination.setStoreValue("000000000",bufferDekatron);
	source.setStoreValue("912345678",bufferDekatron);
	transferUnit.transfer(&source,&destination,7);
	if(!destination.getStringStateInStore().compare("900000001"))
			std::cout << "ShiftCircuit TEST 1.6 SUCCESS \n";
		else
			std::cout << "ShiftCircuit TEST 1.6 shift() FAILURE " << destination.getStringStateInStore() << " vs 900000001\n";

	// Adding both zeros
	source.setStoreValue("000000000",bufferDekatron);
	destination.setStoreValue("000000000",bufferDekatron);
	transferUnit.transfer(&source,&destination,7);
	if(!destination.getStringStateInStore().compare("000000000"))
		std::cout << "ShiftCircuit TEST 2.1 SUCCESS" << std::endl;
	else
		std::cout << "ShiftCircuit TEST 2.1 shift() FAILURE" << std::endl;
	transferUnit.transfer(&destination, &source);
	if(!source.getStringStateInStore().compare("000000000"))
		std::cout << "ShiftCircuit TEST 2.2 SUCCESS" << std::endl;
	else
		std::cout << "ShiftCircuit TEST 2.2 shift() FAILURE" << std::endl;

	// Performing simple additions by pulsing
	int pulse[9] = {1,1,1,1,1,1,1,1,1};
	source.pulseStore(pulse, bufferDekatron);
	source.pulseStore(pulse, bufferDekatron);
	transferUnit.transfer(&source,&destination,7);
	if(!destination.getStringStateInStore().compare("200000002"))
		std::cout << "ShiftCircuit TEST 3.1 SUCCESS" << std::endl;
	else
		std::cout << "ShiftCircuit TEST 3.1 shift() FAILURE" << std::endl;
	transferUnit.transfer(&destination, &source,-1);
	if(!source.getStringStateInStore().compare("422222242"))
		std::cout << "ShiftCircuit TEST 3.2 SUCCESS" << std::endl;
	else
		std::cout << "ShiftCircuit TEST 3.2 shift() FAILURE " << source.getStringStateInStore() << " vs 222222242\n";

	// Creating carry over by pulsing
	source.pulseStore(pulse, bufferDekatron);
	source.pulseStore(pulse, bufferDekatron);
	source.pulseStore(pulse, bufferDekatron);
	source.pulseStore(pulse, bufferDekatron);
	source.pulseStore(pulse, bufferDekatron);
	
	// source is  9 7777 7977, dest is 2 0000 0002
	transferUnit.transfer(&source,&destination,-1);
	if(!destination.getStringStateInStore().compare("177777973"))
		std::cout << "ShiftCircuit TEST 4.1 SUCCESS" << std::endl;
	else
		std::cout << "ShiftCircuit TEST 4.1 shift() FAILURE " <<  destination.getStringStateInStore() << " vs 177777973\n";
	transferUnit.transfer(&destination, &source,5);
	if(!source.getStringStateInStore().compare("077778575"))
		std::cout << "ShiftCircuit TEST 4.2 SUCCESS" << std::endl;
	else
		std::cout << "ShiftCircuit TEST 4.2 shift() FAILURE " <<  source.getStringStateInStore() << " vs 077778575\n";
	//std::cout << "s " <<source.getStringStateInStore()<<" d "<<destination.getStringStateInStore()<<" \n";
	// Performing multiple addition tests
	source.setStoreValue("555555555", bufferDekatron);
	destination.setStoreValue("444444444", bufferDekatron);
	transferUnit.transfer(&source, &destination,3);
	if(!destination.getStringStateInStore().compare("944499999"))
		std::cout << "ShiftCircuit TEST 5.1 SUCCESS" << std::endl;
	else
		std::cout << "ShiftCircuit TEST 5.1 shift() FAILURE " <<  destination.getStringStateInStore() << " vs 944499999\n";
	transferUnit.transfer(&destination, &source,7);
	if(!source.getStringStateInStore().compare("455555560"))
		std::cout << "ShiftCircuit TEST 5.2 SUCCESS" << std::endl;
	else
		std::cout << "ShiftCircuit TEST 5.2 shift() FAILURE " <<  source.getStringStateInStore() << " vs 455555560\n";

	source.setStoreValue("012345678", bufferDekatron);
	destination.setStoreValue("991111111", bufferDekatron);
	transferUnit.transfer(&source, &destination,4);
	if(!destination.getStringStateInStore().compare("991112345"))
		std::cout << "ShiftCircuit TEST 5.3 SUCCESS" << std::endl;
	else
		std::cout << "ShiftCircuit TEST 5.3 shift() FAILURE" << std::endl;
	transferUnit.transfer(&destination, &source,1);
	if(!source.getStringStateInStore().compare("921456912"))
		std::cout << "ShiftCircuit TEST 5.4 SUCCESS" << std::endl;
	else
		std::cout << "ShiftCircuit TEST 5.4 shift() FAILURE" << std::endl;


	source.setStoreValue("000000000", bufferDekatron);
	destination.setStoreValue("000000000", bufferDekatron);
	// Subtracting both zeros
	transferUnit.transferComplement(&source,&destination,7);
	if(!destination.getStringStateInStore().compare("999999999"))
		std::cout << "ShiftCircuit TEST 6.1 SUCCESS" << std::endl;
	else
		std::cout << "ShiftCircuit TEST 6.1 shift() FAILURE " << source.getStringStateInStore() <<" d: " << destination.getStringStateInStore() << " " << std::endl;
	transferUnit.transferComplement(&destination, &source);
	if(!source.getStringStateInStore().compare("000000000"))
		std::cout << "ShiftCircuit TEST 6.2 SUCCESS" << std::endl;
	else
		std::cout << "ShiftCircuit TEST 6.2 shift() FAILURE " << source.getStringStateInStore() <<" d: " << destination.getStringStateInStore() << " " << std::endl;

	// Performing simple subtractions after pulsing
	source.pulseStore(pulse, bufferDekatron);
	source.pulseStore(pulse, bufferDekatron);
	transferUnit.transferComplement(&source,&destination,-1);
	if(!destination.getStringStateInStore().compare("777777779"))
		std::cout << "ShiftCircuit TEST 7.1 SUCCESS" << std::endl;
	else
		std::cout << "ShiftCircuit TEST 7.1 shift() FAILURE " << source.getStringStateInStore() <<" d: " << destination.getStringStateInStore() << " " << std::endl;
	transferUnit.transferComplement(&destination, &source,4);
	if(!source.getStringStateInStore().compare("522214444"))
		std::cout << "ShiftCircuit TEST 7.2 SUCCESS" << std::endl;
	else
		std::cout << "ShiftCircuit TEST 7.2 shift() FAILURE " << source.getStringStateInStore() <<" d: " << destination.getStringStateInStore() << " " << std::endl;

	source.pulseStore(pulse, bufferDekatron);
	source.pulseStore(pulse, bufferDekatron);
	source.pulseStore(pulse, bufferDekatron);
	destination.pulseStore(pulse, bufferDekatron);
	destination.pulseStore(pulse, bufferDekatron);
	destination.pulseStore(pulse, bufferDekatron);
	transferUnit.transferComplement(&source,&destination);
	if(!destination.getStringStateInStore().compare("144452224"))
		std::cout << "ShiftCircuit TEST 8.1 SUCCESS" << std::endl;
	else
		std::cout << "ShiftCircuit TEST 8.1 shift() FAILURE " << source.getStringStateInStore() <<" d: " << destination.getStringStateInStore() << " " << std::endl;
	transferUnit.transferComplement(&destination, &source,3);
	if(!source.getStringStateInStore().compare("755503325"))
		std::cout << "ShiftCircuit TEST 8.2 SUCCESS" << std::endl;
	else
		std::cout << "ShiftCircuit TEST 8.2 shift() FAILURE " << source.getStringStateInStore() <<" d: " << destination.getStringStateInStore() << " " << std::endl;

	// Performing multiple subtraction tests
	source.setStoreValue("000000005", bufferDekatron);
	destination.setStoreValue("000000004", bufferDekatron);
	transferUnit.transferComplement(&source, &destination,-1);
	// -46 : 9 9999 9953
	if(!destination.getStringStateInStore().compare("999999953"))
		std::cout << "ShiftCircuit TEST 9.1 SUCCESS" << std::endl;
	else
		std::cout << "ShiftCircuit TEST 9.1 shift() FAILURE " << source.getStringStateInStore() <<" d: " << destination.getStringStateInStore() << " " << std::endl;
	transferUnit.transferComplement(&destination, &source,-1);
	// 5 - -469 = 474
	if(!source.getStringStateInStore().compare("000000474"))
		std::cout << "ShiftCircuit TEST 9.2 SUCCESS" << std::endl;
	else
		std::cout << "ShiftCircuit TEST 9.2 shift() FAILURE " << source.getStringStateInStore() <<" d: " << destination.getStringStateInStore() << " " << std::endl;

	source.setStoreValue("000000000", bufferDekatron);
	destination.setStoreValue("991111111", bufferDekatron);
	// - 0 0888 8888 - 0 = 0 0888 8888 = 9 9111 1111
	transferUnit.transferComplement(&source, &destination);
	if(!destination.getStringStateInStore().compare("991111111"))
		std::cout << "ShiftCircuit TEST 9.3 SUCCESS" << std::endl;
	else
		std::cout << "ShiftCircuit TEST 9.3 shift() FAILURE " << source.getStringStateInStore() <<" d: " << destination.getStringStateInStore() << " " << std::endl;
	source.setStoreValue("991111111", bufferDekatron);
	transferUnit.transferComplement(&destination, &source,7);
	if(!source.getStringStateInStore().compare("091111102"))
		std::cout << "ShiftCircuit TEST 9.4 SUCCESS" << std::endl;
	else
		std::cout << "ShiftCircuit TEST 9.4 shift() FAILURE " << source.getStringStateInStore() <<" d: " << destination.getStringStateInStore() << " " << std::endl;

	source.setStoreValue("088448800", bufferDekatron);
	destination.setStoreValue("991001234", bufferDekatron);
	transferUnit.transferComplement(&destination, &source,0);
	if(!source.getStringStateInStore().compare("097447565"))
		std::cout << "ShiftCircuit TEST 9.5 SUCCESS" << std::endl;
	else
		std::cout << "ShiftCircuit TEST 9.5 shift() FAILURE " << source.getStringStateInStore() <<" d: " << destination.getStringStateInStore() << " " << std::endl;
	transferUnit.transferComplement(&source, &destination,2);
	if(!destination.getStringStateInStore().compare("990026759"))
		std::cout << "ShiftCircuit TEST 9.6 SUCCESS" << std::endl;
	else
		std::cout << "ShiftCircuit TEST 9.6 shift() FAILURE " << source.getStringStateInStore() <<" d: " << destination.getStringStateInStore() << " " << std::endl;

	std::cout << "FINISH shiftcircuit.cpp TESTS\n";
}

