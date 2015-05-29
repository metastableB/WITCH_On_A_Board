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
	// Both source and destination are zero
	transferUnit.transfer(&source,&destination);
	if(!destination.getStringStateInStore().compare("000000000"))
		std::cout << "TransferUnit TEST 1 SUCCESS" << std::endl;
	else
		std::cout << "TransferUnit TEST 1 transfer() FAILURE" << std::endl;

	/*transferUnit.transfer(&destination, &source);
	if(!source.getStringStateInStore().compare("111000111"))
		std::cout << "TransferUnit TEST 2 SUCCESS" << std::endl;
	else
		std::cout << "TransferUnit TEST 2 transfer() FAILURE" << std::endl;

	int pulse[9] = {1,1,1,1,1,1,1,1,1};
	Dekatron bufferDekatron[9];
	source.pulseStore(pulse, bufferDekatron);
	// source now 1 1111 1111
	transferUnit.transfer(&source, &destination);
	if(!destination.getStringStateInStore().compare("000111000"))
		std::cout << "TransferUnit TEST 3 SUCCESS" << std::endl;
	else
		std::cout << "TransferUnit TEST 3 transfer() FAILURE" << std::endl;

	// destination 1 1111 1111
	transferUnit.transfer(&destination, &source);
	if(!source.getStringStateInStore().compare("111000111"))
		std::cout << "TransferUnit TEST 4 SUCCESS" << std::endl;
	else
		std::cout << "TransferUnit TEST 4 transfer() FAILURE" << std::endl;
	// source 2 2222 2222

	// creating one carry over
	pulse[0] = 9;
	pulse[1] = 8;
	pulse[2] = 8;
	pulse[3] = 8;
	pulse[4] = 8;
	pulse[5] = 8;
	pulse[6] = 8;
	pulse[7] = 8;
	pulse[8] = 8;
	source.setStoreValue(pulse,bufferDekatron);
	// source 9 8888 8888 , dest 1 1111 1111
	// result 1 0000 0000
	transferUnit.transfer(&source,&destination);
	*/

}



