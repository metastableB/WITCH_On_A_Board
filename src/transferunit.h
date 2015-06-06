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
#include <string>

class TransferUnit {
	int pulseTrainElement[9] = { 1,1,1,1,1,1,1,1,1 };
	int receivingStorePulse[9];
	int receivingStorePulseComplement[9];
	int guideOutputFlags[9];
	int v1OutputFlags[9];
	// TODO: This is temporary to facilitate addition. Move this to the
	// actual relay model once you are done
	Dekatron carryRelays[9];

	Dekatron bufferDekatrons_s[9];
	Dekatron bufferDekatrons_r[9];
	DekatronStore* sendingStore;
	DekatronStore* receivingStore;

	void setSendingStore(DekatronStore* store);
	void setReceivingStore(DekatronStore* store);
	void initializeCarryRelays();
	void initializeGuideOutputFlags();
	void initializeBufferDekatrons();
	void initializeReceivingStorePulse();
	void initializeV1OutputFlags();
	void updateCarryRelays(int pulses[], Dekatron* bufferDekatrons);
	void updateGuideOutputFlags(Dekatron* bufferDekatrons);
	void updateV1OutputFlags(Dekatron* bufferDekatrons);
	void makeReceivingStorePulse();
	void makeCarryOver();
	// TODO : remove after testing
	std::string dekatronArrayToString(Dekatron* arr, int size);
public:
	// TODO: Transfer unit does not check if stores are from the same set
	void transfer(DekatronStore* sStore, DekatronStore* rStore);
	void transferComplement(DekatronStore* sStore, DekatronStore* rStore);
};
#endif /* TRANSFERUNIT_H */

