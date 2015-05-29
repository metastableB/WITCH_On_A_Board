/*
 * transferunit.h
 *
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 28-May-2015
 * 
 */
#ifndef TRANSFERUNIT_H
#define TRANSFERUNIT_H

 #include "dekatron.h"
 #include "dekatronstore.h"

class TransferUnit {
	// set if output guides emit signal
	int guideOutputFlags[9];
	int pulseTrainElement[10] = { 1,1,1,1,1,1,1,1,1 };
	// TODO: This is temporary to facilitate addition. Move this to the
	// actual relay model once you are done
	Dekatron carryRelays[9];
	Dekatron bufferDekatrons[9];
	DekatronStore* sendingStore;
	DekatronStore* receivingStore;
	/* TODO : 1) Make sure dekatrons are incrementing correctly
	 2) Simulate a false set of pulses and send it to the store
	 and make sure the stores are updated correctly.
	 3) Create the method to read store values by sending the train of
	 10 pulses, push the return value to the above function
	 Remember that when we send a 10 pulse stream to the dekatron stores
	 the value in it changes though finally returns to the initial state.
	 Make sure this is reflected in the code
	 */
	void setSendingStore(DekatronStore* store);
	void setReceivingStore(DekatronStore* store);
	void initializeCarryRelays();
	void initializeGuideOutputFlags();
	void updateCarryRelays();
	void updateGuideOutputFlags();
	void makeCarryOver();
public:
	void transfer(DekatronStore* sStore, DekatronStore* rStore);
	void trasferComplement(DekatronStore* sStore, DekatronStore* rStore);
};
#endif /* TRANSFERUNIT_H */

