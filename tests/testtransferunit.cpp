/*
 * testtransferunit.cpp
 *
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 29-May-2015
 * 
 */

#include "testtransferunit.h"

TestTransferUnit::TestTransferUnit() {
	std::cout << "Testing transferunit.cpp"<< std::endl;
	DekatronStore source, destination;
	TransferUnit transferUnit;

	// Adding both zeros
	transferUnit.transfer(&source,&destination);
	if(!destination.getStringStateInStore().compare("000000000"))
		std::cout << "TransferUnit TEST 1.1 SUCCESS" << std::endl;
	else
		std::cout << "TransferUnit TEST 1.1 transfer() FAILURE" << std::endl;
	transferUnit.transfer(&destination, &source);
	if(!source.getStringStateInStore().compare("000000000"))
		std::cout << "TransferUnit TEST 1.2 SUCCESS" << std::endl;
	else
		std::cout << "TransferUnit TEST 1.2 transfer() FAILURE" << std::endl;
	
	// Performing simple additions by pulsing
	int pulse[9] = {1,1,1,1,1,1,1,1,1};
	Dekatron bufferDekatron[9];
	source.pulseStore(pulse, bufferDekatron);
	source.pulseStore(pulse, bufferDekatron);
	transferUnit.transfer(&source,&destination);
	if(!destination.getStringStateInStore().compare("222222222"))
		std::cout << "TransferUnit TEST 2.1 SUCCESS" << std::endl;
	else
		std::cout << "TransferUnit TEST 2.1 transfer() FAILURE" << std::endl;
	transferUnit.transfer(&destination, &source);
	if(!source.getStringStateInStore().compare("444444444"))
		std::cout << "TransferUnit TEST 2.2 SUCCESS" << std::endl;
	else
		std::cout << "TransferUnit TEST 2.2 transfer() FAILURE" << std::endl;
	
	// Creating carry over by pulsing
	source.pulseStore(pulse, bufferDekatron);
	source.pulseStore(pulse, bufferDekatron);
	source.pulseStore(pulse, bufferDekatron);
	source.pulseStore(pulse, bufferDekatron);
	source.pulseStore(pulse, bufferDekatron);
	// source is  9 9999 9999, dest is 2 2222 2222
	transferUnit.transfer(&source,&destination);
	if(!destination.getStringStateInStore().compare("222222222"))
		std::cout << "TransferUnit TEST 3.1 SUCCESS" << std::endl;
	else
		std::cout << "TransferUnit TEST 3.1 transfer() FAILURE" << std::endl;
	transferUnit.transfer(&destination, &source);
	if(!source.getStringStateInStore().compare("222222222"))
		std::cout << "TransferUnit TEST 3.2 SUCCESS" << std::endl;
	else
		std::cout << "TransferUnit TEST 3.2 transfer() FAILURE" << std::endl;

	// Performing multiple addition tests
	source.setStoreValue("555555555", bufferDekatron);
	destination.setStoreValue("444444444", bufferDekatron);
	transferUnit.transfer(&source, &destination);
	if(!destination.getStringStateInStore().compare("999999999"))
		std::cout << "TransferUnit TEST 4.1 SUCCESS" << std::endl;
	else
		std::cout << "TransferUnit TEST 4.1 transfer() FAILURE" << std::endl;
	transferUnit.transfer(&destination, &source);
	if(!source.getStringStateInStore().compare("555555555"))
		std::cout << "TransferUnit TEST 4.2 SUCCESS" << std::endl;
	else
		std::cout << "TransferUnit TEST 4.2 transfer() FAILURE" << std::endl;

	source.setStoreValue("012345678", bufferDekatron);
	destination.setStoreValue("991111111", bufferDekatron);
	transferUnit.transfer(&source, &destination);
	if(!destination.getStringStateInStore().compare("003456790"))
		std::cout << "TransferUnit TEST 4.3 SUCCESS" << std::endl;
	else
		std::cout << "TransferUnit TEST 4.3 transfer() FAILURE" << std::endl;
	transferUnit.transfer(&destination, &source);
	if(!source.getStringStateInStore().compare("015802468"))
		std::cout << "TransferUnit TEST 4.4 SUCCESS" << std::endl;
	else
		std::cout << "TransferUnit TEST 4.4 transfer() FAILURE" << std::endl;

	std::cout << "FINISH transferunit.cpp TESTS\n";
}



