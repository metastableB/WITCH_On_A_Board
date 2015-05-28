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

class TransferUnit {
	// TODO: This is temporary to facilitate addition. Move this to the
	// actual relay model once you are done
	Dekatron carryRelays[9];
	// Pulse store stores pulse received from the
	// output guides.
	Dekatron pulseStore[9];
	Dekatron* &sendingStore[];
	Dekatron* &receivingStore[];
	/* TODO : 1) Make sure dekatrons are incrementing correctly
			  2) Simulate a false set of pulses and send it to the store
				 and make sure the stores are updated correctly.
			  3) Create the method to read store values by sending the train of
			     10 pulses, push the return value to the above function
			  Remember that when we send a 10 pulse stream to the dekatron stores
			  the value in it changes though finally returns to the initial state.
			  Make sure this is reflected in the code
	*/
	void setSendingStore(Dekatron* &store);
	void setReceivingStore(Dekatron* &store);
	// Sends a 10 pulse train to sending store and retrieves the state stored
	void generatePulses();

public :
	void transfer(Dekatron* &sStore, Dekatron* &rStore);
};
#endif /* TRANSFERUNIT_H */

