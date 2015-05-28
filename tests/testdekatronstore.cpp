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
			std::cout << "DekatronStore TEST 1 SUCCESSFUL\n";
		else
			std::cout << "DekatronStore TEST 1 getStringStateInStore() FAILURE\n";

		int arr[9] = {0,1,1,1,1,1,1,1,1};
		Dekatron cRelays[9];
		store.pulseStore(arr,cRelays);
		if(!store.getStringStateInStore().compare("011111111"))
			std::cout<< "DekatronStore TEST 2 SUCCESSFUL\n";
		else
			std::cout << "DekatronStore TEST 2 pulseStore(int [],Dekatron []) FAILURE\n";

		// cRelays should have all zeros
		int  sum = 0;
		for (int i = 0 ; i < 9 ; i++)
			sum += cRelays[i].getCurrentNumber();
		if(sum == 0)
			std::cout << "DekatronStore TEST 3 SUCCESSFUL\n";
		else
			std::cout << "DekatronStore TEST 3  Relay Check FAILURE\n";

		arr[0] = 1;
		arr[4] = 0;
		arr[5] = 0;
		arr[6] = 0;
		// I.e. input pulse combination is 1,1,1,1,0,0,0,1,1
		// Sending a train of 9 pulses
		store.pulseStore(arr,cRelays);
		store.pulseStore(arr,cRelays);
		store.pulseStore(arr,cRelays);
		store.pulseStore(arr,cRelays);
		store.pulseStore(arr,cRelays);
		store.pulseStore(arr,cRelays);
		store.pulseStore(arr,cRelays);
		store.pulseStore(arr,cRelays);
		store.pulseStore(arr,cRelays);
		// Expected out put is 9,0,0,0,1,1,1,0,0
		// Expected cRelay config 0,1,1,1,0,0,0,1,1
		if(!store.getStringStateInStore().compare("900011100"))
			std::cout<< "DekatronStore TEST 4 SUCCESSFUL\n";
		else
			std::cout << "DekatronStore TEST 4 multiple pulseStore(int [],Dekatron []) FAILURE\n";

		for (int i = 0 ; i < 9 ; i++) {

			if(i == 0 || i == 4 || i  == 5 || i == 6 ) {
				if(cRelays[i].getCurrentNumber() == 0)
					std::cout << "DekatronStore TEST 5."<< i <<" SUCCESSFUL\n";
				else {
					std::cout << "DekatronStore TEST 5."<< i <<"  Relay Check FAILURE\n";
					break;
				}
			} else {
				if(cRelays[i].getCurrentNumber() == 1)
					std::cout << "DekatronStore TEST 5."<< i <<" SUCCESSFUL\n";
				else {
					std::cout << "DekatronStore TEST 5."<< i <<"  Relay Check FAILURE\n";
					break;
				}
			}
		}
		std::cout << "FINISH dekatronstore.cpp TESTS\n";
	}
};



