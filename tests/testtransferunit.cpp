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

	transferUnit.transfer(&source,&destination);
	if(!destination.getStringStateInStore().compare("000000000"))
		std::cout << "TransferUnit TEST 1.1 SUCCESSFUL" << std::endl;
	else{
		failedTests++;
		std::cout << "TransferUnit TEST 1.1 transfer() FAILURE" << std::endl;
	}
	transferUnit.transfer(&destination, &source);
	if(!source.getStringStateInStore().compare("000000000"))
		std::cout << "TransferUnit TEST 1.2 SUCCESSFUL" << std::endl;
	else{
		failedTests++;
		std::cout << "TransferUnit TEST 1.2 transfer() FAILURE" << std::endl;
	}
	
	// Performing simple additions by pulsing
	int pulse[9] = {1,1,1,1,1,1,1,1,1};
	Dekatron bufferDekatron[9];
	source.pulseStore(pulse, bufferDekatron);
	source.pulseStore(pulse, bufferDekatron);
	transferUnit.transfer(&source,&destination);
	if(!destination.getStringStateInStore().compare("222222222"))
		std::cout << "TransferUnit TEST 2.1 SUCCESSFUL" << std::endl;
	else{
		failedTests++;
		std::cout << "TransferUnit TEST 2.1 transfer() FAILURE" << source.getStringStateInStore() 
				  <<" d: " << destination.getStringStateInStore() << " " << std::endl;
	}
	transferUnit.transfer(&destination, &source);
	if(!source.getStringStateInStore().compare("444444444"))
		std::cout << "TransferUnit TEST 2.2 SUCCESSFUL" << std::endl;
	else{
		failedTests++;
		std::cout << "TransferUnit TEST 2.2 transfer() FAILURE" << std::endl;
	}
	
	// Creating carry over by pulsing
	source.pulseStore(pulse, bufferDekatron);
	source.pulseStore(pulse, bufferDekatron);
	source.pulseStore(pulse, bufferDekatron);
	source.pulseStore(pulse, bufferDekatron);
	source.pulseStore(pulse, bufferDekatron);
	// source is  9 9999 9999, dest is 2 2222 2222
	transferUnit.transfer(&source,&destination);
	if(!destination.getStringStateInStore().compare("222222222"))
		std::cout << "TransferUnit TEST 3.1 SUCCESSFUL" << std::endl;
	else{
		failedTests++;
		std::cout << "TransferUnit TEST 3.1 transfer() FAILURE" << std::endl;
	}
	transferUnit.transfer(&destination, &source);
	if(!source.getStringStateInStore().compare("222222222"))
		std::cout << "TransferUnit TEST 3.2 SUCCESSFUL" << std::endl;
	else{
		failedTests++;
		std::cout << "TransferUnit TEST 3.2 transfer() FAILURE" << std::endl;
	}

	// Performing multiple addition tests
	source.setStoreValue("555555555", bufferDekatron);
	destination.setStoreValue("444444444", bufferDekatron);
	transferUnit.transfer(&source, &destination);
	if(!destination.getStringStateInStore().compare("999999999"))
		std::cout << "TransferUnit TEST 4.1 SUCCESSFUL" << std::endl;
	else{
		failedTests++;
		std::cout << "TransferUnit TEST 4.1 transfer() FAILURE" << std::endl;
	}
	transferUnit.transfer(&destination, &source);
	if(!source.getStringStateInStore().compare("555555555"))
		std::cout << "TransferUnit TEST 4.2 SUCCESSFUL" << std::endl;
	else{
		failedTests++;
		std::cout << "TransferUnit TEST 4.2 transfer() FAILURE" << std::endl;
	}

	source.setStoreValue("012345678", bufferDekatron);
	destination.setStoreValue("991111111", bufferDekatron);
	transferUnit.transfer(&source, &destination);
	if(!destination.getStringStateInStore().compare("003456790"))
		std::cout << "TransferUnit TEST 4.3 SUCCESSFUL" << std::endl;
	else{
		failedTests++;
		std::cout << "TransferUnit TEST 4.3 transfer() FAILURE" << std::endl;
	}
	transferUnit.transfer(&destination, &source);
	if(!source.getStringStateInStore().compare("015802468"))
		std::cout << "TransferUnit TEST 4.4 SUCCESSFUL" << std::endl;
	else{
		failedTests++;
		std::cout << "TransferUnit TEST 4.4 transfer() FAILURE" << std::endl;
	}

	/*
	 * SUBTRACTION BETWEEN STORES
	 */

	source.setStoreValue("000000000", bufferDekatron);
	destination.setStoreValue("000000000", bufferDekatron);
	// Subtracting both zeros
	transferUnit.transferComplement(&source,&destination);
	if(!destination.getStringStateInStore().compare("999999999"))
		std::cout << "TransferUnit TEST 5.1 SUCCESSFUL" << std::endl;
	else{
		failedTests++;
		std::cout << "TransferUnit TEST 5.1 transferComplement() FAILURE " << source.getStringStateInStore() 
				  <<" d: " << destination.getStringStateInStore() << " " << std::endl;
	}
	transferUnit.transferComplement(&destination, &source);
	if(!source.getStringStateInStore().compare("000000000"))
		std::cout << "TransferUnit TEST 5.2 SUCCESSFUL" << std::endl;
	else{
		failedTests++;
		std::cout << "TransferUnit TEST 5.2 transferComplement() FAILURE " << source.getStringStateInStore() 
				  <<" d: " << destination.getStringStateInStore() << " " << std::endl;
	}

	// Performing simple subtractions after pulsing
	source.pulseStore(pulse, bufferDekatron);
	source.pulseStore(pulse, bufferDekatron);
	transferUnit.transferComplement(&source,&destination);
	if(!destination.getStringStateInStore().compare("777777777"))
		std::cout << "TransferUnit TEST 6.1 SUCCESSFUL" << std::endl;
	else{
		failedTests++;
		std::cout << "TransferUnit TEST 6.1 transferComplement() FAILURE " << source.getStringStateInStore() 
				  <<" d: " << destination.getStringStateInStore() << " " << std::endl;
	}
	transferUnit.transferComplement(&destination, &source);
	if(!source.getStringStateInStore().compare("444444444"))
		std::cout << "TransferUnit TEST 6.2 SUCCESSFUL" << std::endl;
	else{
		failedTests++;
		std::cout << "TransferUnit TEST 6.2 transferComplement() FAILURE " << source.getStringStateInStore() 
			      <<" d: " << destination.getStringStateInStore() << " " << std::endl;
	}

	source.pulseStore(pulse, bufferDekatron);
	source.pulseStore(pulse, bufferDekatron);
	source.pulseStore(pulse, bufferDekatron);
	destination.pulseStore(pulse, bufferDekatron);
	destination.pulseStore(pulse, bufferDekatron);
	destination.pulseStore(pulse, bufferDekatron);
	// source is 7 7777 777	7, dest is  0 0000 0000
	transferUnit.transferComplement(&source,&destination);
	if(!destination.getStringStateInStore().compare("222222222"))
		std::cout << "TransferUnit TEST 7.1 SUCCESSFUL" << std::endl;
	else{
		failedTests++;
		std::cout << "TransferUnit TEST 7.1 transferComplement() FAILURE " << source.getStringStateInStore() 
				   <<" d: " << destination.getStringStateInStore() << " " << std::endl;
	}
	transferUnit.transferComplement(&destination, &source);
	if(!source.getStringStateInStore().compare("555555555"))
		std::cout << "TransferUnit TEST 8.2 SUCCESSFUL" << std::endl;
	else{
		failedTests++;	
		std::cout << "TransferUnit TEST 8.2 transferComplement() FAILURE " << source.getStringStateInStore() 
	  			  <<" d: " << destination.getStringStateInStore() << " " << std::endl;
	}

	// Performing multiple subtraction tests
	source.setStoreValue("000000005", bufferDekatron);
	destination.setStoreValue("000000004", bufferDekatron);
	transferUnit.transferComplement(&source, &destination);
	// -1 : 9 9999 9998
	if(!destination.getStringStateInStore().compare("999999998"))
		std::cout << "TransferUnit TEST 9.1 SUCCESSFUL" << std::endl;
	else{
		failedTests++;
		std::cout << "TransferUnit TEST 9.1 transferComplement() FAILURE " << source.getStringStateInStore() <<" d: " 
				  << destination.getStringStateInStore() << " " << std::endl;
	}
	transferUnit.transferComplement(&destination, &source);
	// 5 - -1 = 6
	if(!source.getStringStateInStore().compare("000000006"))
		std::cout << "TransferUnit TEST 9.2 SUCCESSFUL" << std::endl;
	else{
		failedTests++;
		std::cout << "TransferUnit TEST 9.2 transferComplement() FAILURE " << source.getStringStateInStore() 
				   <<" d: " << destination.getStringStateInStore() << " " << std::endl;
	}

	source.setStoreValue("000000000", bufferDekatron);
	destination.setStoreValue("991111111", bufferDekatron);
	// - 0 0888 8888 - 0 = 0 0888 8888 = 9 9111 1111
	transferUnit.transferComplement(&source, &destination);
	if(!destination.getStringStateInStore().compare("991111111"))
		std::cout << "TransferUnit TEST 9.3 SUCCESSFUL" << std::endl;
	else{
		failedTests++;
		std::cout << "TransferUnit TEST 9.3 transferComplement() FAILURE " << source.getStringStateInStore() 
				  <<" d: " << destination.getStringStateInStore() << " " << std::endl;
	}
	source.setStoreValue("991111111", bufferDekatron);
	transferUnit.transferComplement(&destination, &source);
	if(!source.getStringStateInStore().compare("999999999"))
		std::cout << "TransferUnit TEST 9.4 SUCCESSFUL" << std::endl;
	else{
		failedTests++;
		std::cout << "TransferUnit TEST 9.4 transferComplement() FAILURE " << source.getStringStateInStore()
				  <<" d: " << destination.getStringStateInStore() << " " << std::endl;
	}

	source.setStoreValue("088448800", bufferDekatron);
	destination.setStoreValue("991001234", bufferDekatron);
	transferUnit.transferComplement(&destination, &source);
	if(!source.getStringStateInStore().compare("097447565"))
		std::cout << "TransferUnit TEST 9.5 SUCCESSFUL" << std::endl;
	else{
		failedTests++;
		std::cout << "TransferUnit TEST 9.5 transferComplement() FAILURE " << source.getStringStateInStore() 
				  <<" d: " << destination.getStringStateInStore() << " " << std::endl;
	}
	transferUnit.transferComplement(&source, &destination);
	if(!destination.getStringStateInStore().compare("893553669"))
		std::cout << "TransferUnit TEST 9.6 SUCCESSFUL" << std::endl;
	else{
		failedTests++;
		std::cout << "TransferUnit TEST 9.6 transferComplement() FAILURE " << source.getStringStateInStore()
				  <<" d: " << destination.getStringStateInStore() << " " << std::endl;
	}

	
	/*
	 *  ADDITION BETWEEN STORES (TRANSFER AND CLEAR)
	 */
	//int pulse[9];
	//Dekatron bufferDekatron[9];
	for(int i = 0; i < 9; i++)
		pulse[i] = 1;
	source.setStoreValue("000000000",bufferDekatron);
	destination.setStoreValue("000000000",bufferDekatron);
	transferUnit.transferClear(&source,&destination);
	if(!destination.getStringStateInStore().compare("000000000") && !source.getStringStateInStore().compare("000000000"))
		std::cout << "TransferUnit TEST 10.1 SUCCESSFUL" << std::endl;
	else{
		failedTests++;
		std::cout << "TransferUnit TEST 10.1 transferClear() FAILURE" << std::endl;
	}
	transferUnit.transferClear(&destination, &source);
	if(!source.getStringStateInStore().compare("000000000"))
		std::cout << "TransferUnit TEST 10.2 SUCCESSFUL" << std::endl;
	else{
		failedTests++;
		std::cout << "TransferUnit TEST 10.2 transferClear() FAILURE" << std::endl;
	}

	// Performing simple additions by pulsing
	source.pulseStore(pulse, bufferDekatron);
	source.pulseStore(pulse, bufferDekatron);
	transferUnit.transferClear(&source,&destination);
	if(!destination.getStringStateInStore().compare("222222222") && !source.getStringStateInStore().compare("000000000"))
		std::cout << "TransferUnit TEST 11.1 SUCCESSFUL" << std::endl;
	else{
		failedTests++;
		std::cout << "TransferUnit TEST 11.1 transferClear() FAILURE " << source.getStringStateInStore() <<" d " << destination.getStringStateInStore() << "\n" ;
	}
	source.setStoreValue("222222222",bufferDekatron);
	transferUnit.transferClear(&destination, &source);
	if(!source.getStringStateInStore().compare("444444444") && !destination.getStringStateInStore().compare("000000000"))
		std::cout << "TransferUnit TEST 11.2 SUCCESSFUL" << std::endl;
	else{
		failedTests++;
		std::cout << "TransferUnit TEST 11.2 transferClear() FAILURE" << std::endl;
	}
	
	// Creating carry over by pulsing
	source.pulseStore(pulse, bufferDekatron);
	source.pulseStore(pulse, bufferDekatron);
	source.pulseStore(pulse, bufferDekatron);
	source.pulseStore(pulse, bufferDekatron);
	source.pulseStore(pulse, bufferDekatron);
	destination.pulseStore(pulse,bufferDekatron);	
	destination.pulseStore(pulse,bufferDekatron);
	// source is  9 9999 9999, dest is 2 2222 2222
	transferUnit.transferClear(&source,&destination);
	if(!destination.getStringStateInStore().compare("222222222") && !source.getStringStateInStore().compare("000000000"))
		std::cout << "TransferUnit TEST 12.1 SUCCESSFUL" << std::endl;
	else{
		failedTests++;
		std::cout << "TransferUnit TEST 12.1 transferClear() FAILURE" << std::endl;
	}
	destination.setStoreValue("777777777",bufferDekatron);
	source.setStoreValue("012345678",bufferDekatron);
	transferUnit.transferClear(&destination, &source);
	if(!source.getStringStateInStore().compare("790123455")&& !destination.getStringStateInStore().compare("000000000"))
		std::cout << "TransferUnit TEST 12.2 SUCCESSFUL" << std::endl;
	else{
		failedTests++;
		std::cout << "TransferUnit TEST 12.2 transferClear() FAILURE" << std::endl;
	}
	
	// Performing multiple addition tests
	source.setStoreValue("555555555", bufferDekatron);
	destination.setStoreValue("444444444", bufferDekatron);
	transferUnit.transferClear(&source, &destination);
	if(!destination.getStringStateInStore().compare("999999999") && !source.getStringStateInStore().compare("000000000"))
		std::cout << "TransferUnit TEST 13.1 SUCCESSFUL" << std::endl;
	else{
		failedTests++;
		std::cout << "TransferUnit TEST 13.1 transferClear() FAILURE" << std::endl;
	}
	source.setStoreValue("555555555",bufferDekatron);
	transferUnit.transferClear(&destination, &source);
	if(!source.getStringStateInStore().compare("555555555") && !destination.getStringStateInStore().compare("000000000"))
		std::cout << "TransferUnit TEST 13.2 SUCCESSFUL" << std::endl;
	else{
		failedTests++;
		std::cout << "TransferUnit TEST 13.2 transferClear() FAILURE" << std::endl;
	}

	source.setStoreValue("012345678", bufferDekatron);
	destination.setStoreValue("991111111", bufferDekatron);
	transferUnit.transferClear(&source, &destination);
	if(!destination.getStringStateInStore().compare("003456790") && !source.getStringStateInStore().compare("000000000"))
		std::cout << "TransferUnit TEST 14.3 SUCCESSFUL" << std::endl;
	else{
		failedTests++;
		std::cout << "TransferUnit TEST 14.3 transferClear() FAILURE" << std::endl;
	}
	source.setStoreValue("012345678", bufferDekatron);
	transferUnit.transferClear(&destination, &source);
	if(!source.getStringStateInStore().compare("015802468") && !destination.getStringStateInStore().compare("000000000"))
		std::cout << "TransferUnit TEST 14.4 SUCCESSFUL" << std::endl;
	else{
		failedTests++;
		std::cout << "TransferUnit TEST 14.4 transferClear() FAILURE" << std::endl;
	}

	std::cout << "FINISH transferunit.cpp TESTS\n";
	/*
	 * Accumulator transfers and tests in shiftcircuit test module
	 */

}



