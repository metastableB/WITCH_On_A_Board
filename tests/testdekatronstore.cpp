/*
 * testdekatronstore.cpp
 *
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 28-May-2015
 * 
 */
#include "../src/dekatronstore.h"

class TestDekatronStore {
public:
	TestDekatronStore() {
		DekatronStore store;

		if(!store.getStringStateInStore().compare("000000000"))
			std::cout << "DekatroneStore TEST 1 SUCCESS\n";
		else
			std::cout << "DekatroneStore TEST 1 getStringStateInStore() FAILURE\n";

		int arr[9] = {0,1,1,1,1,1,1,1,1};
		Dekatron cRelays[9];
		store.pulseStore(arr,cRelays);
		if(!store.getStringStateInStore().compare("011111111"))
			std::cout<< "DekatroneStore TEST 2 SUCCESS\n";
		else
			std::cout << "DekatroneStore TEST 2 pulseStore(int [],Dekatron []) FAILURE\n";
		std::cout << "FINISH dekatronstore.cpp TESTS\n";

	}
};



