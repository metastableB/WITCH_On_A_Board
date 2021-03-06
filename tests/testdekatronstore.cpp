/*
 * testdekatronstore.cpp
 *
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 28-May-2015
 * 
 */
#include "testdekatronstore.h"

TestDekatronStore::TestDekatronStore() {
	logObj.log(LogLevel::INFO, "testdekatronstore.cpp","Testing dekatronstore.cpp\n");
	DekatronStore store;

	if (!store.getStringStateInStore().compare("000000000"))
		logObj.log(LogLevel::INFO, "testdekatronstore.cpp","DekatronStore TEST 1   SUCCESSFUL\n");
	else{
		failedTests++;
		logObj.log(LogLevel::WARNING,"testdekatronsore.cpp","DekatronStore TEST 1 getStringStateInStore() FAILURE\n");
	}

	int arr[9] = { 0, 1, 1, 1, 1, 1, 1, 1, 1 };
	Dekatron dekatronBuffers[9];
	store.pulseStore(arr, dekatronBuffers);
	if (!store.getStringStateInStore().compare("011111111"))
		logObj.log(LogLevel::INFO, "testdekatronstore.cpp","DekatronStore TEST 2   SUCCESSFUL\n");
	else{
		failedTests++;
		logObj.log(LogLevel::WARNING,"testdekatronsore.cpp","DekatronStore TEST 2 pulseStore(int [],Dekatron []) FAILURE\n");
	}

	int sum = 0;
	for (int i = 0; i < 9; i++)
		sum += dekatronBuffers[i].getCurrentNumber();
	if (sum == 8)
		logObj.log(LogLevel::INFO, "testdekatronstore.cpp","DekatronStore TEST 3   SUCCESSFUL\n");
	else{
		failedTests++;
		logObj.log(LogLevel::WARNING,"testdekatronsore.cpp","DekatronStore TEST 3  Relay Check FAILURE\n");
	}

	arr[0] = 1;
	arr[4] = 0;
	arr[5] = 0;
	arr[6] = 0;
	// I.e. input pulse combination is 1,1,1,1,0,0,0,1,1
	// Sending a train of 9 pulses
	store.pulseStore(arr, dekatronBuffers);
	store.pulseStore(arr, dekatronBuffers);
	store.pulseStore(arr, dekatronBuffers);
	store.pulseStore(arr, dekatronBuffers);
	store.pulseStore(arr, dekatronBuffers);
	store.pulseStore(arr, dekatronBuffers);
	store.pulseStore(arr, dekatronBuffers);
	store.pulseStore(arr, dekatronBuffers);
	store.pulseStore(arr, dekatronBuffers);
	// Expected output (dekatronBuffers) is 9,0,0,0,1,1,1,0,0

	if (!store.getStringStateInStore().compare("900011100"))
		logObj.log(LogLevel::INFO, "testdekatronstore.cpp","DekatronStore TEST 4   SUCCESSFUL\n");
	else{
		failedTests++;
		logObj.log(LogLevel::WARNING,"testdekatronsore.cpp","DekatronStore TEST 4 multiple pulseStore(int [],Dekatron []) FAILURE\n");
	}

	for (int i = 0; i < 9; i++) {
		if (i == 1 || i == 2 || i == 3 || i == 7 || i == 8) {
			if (dekatronBuffers[i].getCurrentNumber() == 0)
				logObj.log(LogLevel::INFO, "testdekatronstore.cpp", "DekatronStore TEST 5." + std::to_string(i)+ " SUCCESSFUL\n");
			else {
				failedTests++;
				logObj.log(LogLevel::WARNING,"testdekatronsore.cpp","DekatronStore TEST 5." +std::to_string(i) +"  Relay Check FAILURE\n");
				break;
			}
		} else if (i == 0) {
			if (dekatronBuffers[i].getCurrentNumber() == 9)
				logObj.log(LogLevel::INFO, "testdekatronstore.cpp","DekatronStore TEST 5."+std::to_string(i)+" SUCCESSFUL\n");
			else {
				failedTests++;
				logObj.log(LogLevel::WARNING,"testdekatronsore.cpp","DekatronStore TEST 5."+ std::to_string(i)+"  Relay Check FAILURE\n");
				break;
			}
		} else {
			if (dekatronBuffers[i].getCurrentNumber() == 1)
				logObj.log(LogLevel::INFO, "testdekatronstore.cpp","DekatronStore TEST 5." + std::to_string(i)+" SUCCESSFUL\n");
			else {
				failedTests++;
				logObj.log(LogLevel::WARNING,"testdekatronsore.cpp","DekatronStore TEST 5."+ std::to_string(i)+"  Relay Check FAILURE\n");
				break;
			}
		}
	}
	arr[0] = 0;
	arr[1] = 1;
	arr[2] = 2;
	arr[3] = 3;
	arr[4] = 4;
	arr[5] = 5;
	arr[6] = 6;
	arr[7] = 7;
	arr[8] = 8;
	// arr : 0 1234 5478
	store.setStoreValue(arr,  dekatronBuffers);
	for(int i= 0; i < 9; i++)
		if(dekatronBuffers[i].getCurrentNumber() == i)
			logObj.log(LogLevel::INFO, "testdekatronstore.cpp","DekatronStore TEST 6."+std::to_string(i)+" SUCCESSFUL\n");
		else {
			failedTests++;
			logObj.log(LogLevel::WARNING,"testdekatronsore.cpp","DekatronStore TEST 6."+std::to_string(i)+"  setStoreValue FAILURE\n");
			break;
		}

	if(!store.getStringStateInStore().compare("012345678") )
		logObj.log(LogLevel::INFO, "testdekatronstore.cpp", "DekatronStore TEST 7   SUCCESSFUL\n");
	else{
		failedTests++;
		logObj.log(LogLevel::WARNING,"testdekatronsore.cpp","DekatronStore TEST 7 setStoreValue FAILURE\n");
	}

	if(store.setStoreValue("000", dekatronBuffers))
		logObj.log(LogLevel::INFO, "testdekatronstore.cpp","DekatronStore TEST 8   SUCCESSFUL\n");
	else{
		failedTests++;
		logObj.log(LogLevel::WARNING,"testdekatronsore.cpp","DekatronStore TEST 8 setStoreValue(string) FAILURE\n");
	}

	if(store.setStoreValue("90000000a", dekatronBuffers))
		logObj.log(LogLevel::INFO, "testdekatronstore.cpp","DekatronStore TEST 9   SUCCESSFUL\n");
	else{
		failedTests++;
		logObj.log(LogLevel::WARNING,"testdekatronsore.cpp","DekatronStore TEST 9 setStoreValue(string) FAILURE\n");
	}

	if(!store.setStoreValue("012345678", dekatronBuffers)) {
		if(store.getStringStateInStore().compare("012345678"))
			logObj.log(LogLevel::INFO, "testdekatronstore.cpp","DekatronStore TEST 10   SUCCESSFUL\n");
	} else{
		failedTests++;
		logObj.log(LogLevel::WARNING,"testdekatronsore.cpp","DekatronStore TEST 10 setStoreValue(string) FAILURE\n");
	}

	logObj.log(LogLevel::INFO, "testdekatronstore.cpp","FINISH dekatronstore.cpp TESTS\n");
}
