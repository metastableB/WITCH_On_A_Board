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
	DekatronStore store;

	if (!store.getStringStateInStore().compare("000000000"))
		std::cout << "DekatronStore TEST 1   SUCCESSFUL\n";
	else
		std::cout << "DekatronStore TEST 1 getStringStateInStore() FAILURE\n";

	int arr[9] = { 0, 1, 1, 1, 1, 1, 1, 1, 1 };
	Dekatron dekatronBuffers[9];
	store.pulseStore(arr, dekatronBuffers);
	if (!store.getStringStateInStore().compare("011111111"))
		std::cout << "DekatronStore TEST 2   SUCCESSFUL\n";
	else
		std::cout<< "DekatronStore TEST 2 pulseStore(int [],Dekatron []) FAILURE\n";

	int sum = 0;
	for (int i = 0; i < 9; i++)
		sum += dekatronBuffers[i].getCurrentNumber();
	if (sum == 8)
		std::cout << "DekatronStore TEST 3   SUCCESSFUL\n";
	else
		std::cout << "DekatronStore TEST 3  Relay Check FAILURE\n";

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
		std::cout << "DekatronStore TEST 4   SUCCESSFUL\n";
	else
		std::cout << "DekatronStore TEST 4 multiple pulseStore(int [],Dekatron []) FAILURE\n";

	for (int i = 0; i < 9; i++) {
		if (i == 1 || i == 2 || i == 3 || i == 7 || i == 8) {
			if (dekatronBuffers[i].getCurrentNumber() == 0)
				std::cout << "DekatronStore TEST 5." << i << " SUCCESSFUL\n";
			else {
				std::cout << "DekatronStore TEST 5." << i << "  Relay Check FAILURE\n";
				break;
			}
		} else if (i == 0) {
			if (dekatronBuffers[i].getCurrentNumber() == 9)
				std::cout << "DekatronStore TEST 5." << i << " SUCCESSFUL\n";
			else {
				std::cout << "DekatronStore TEST 5." << i << "  Relay Check FAILURE\n";
				break;
			}
		} else {
			if (dekatronBuffers[i].getCurrentNumber() == 1)
				std::cout << "DekatronStore TEST 5." << i << " SUCCESSFUL\n";
			else {
				std::cout << "DekatronStore TEST 5." << i << "  Relay Check FAILURE\n";
				break;
			}
		}
	}
	std::cout << "FINISH dekatronstore.cpp TESTS\n";
}
