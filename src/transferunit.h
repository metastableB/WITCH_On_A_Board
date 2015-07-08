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
#include "shiftcircuit.h"
#include "accumulator.h"
#include <string>

class TransferUnit {
	int pulseTrainElement[9] = { 1, 1,1,1,1 ,1,1,1,1};
	int receivingStorePulse[9];
	int receivingStorePulseComplement[9];
	int guideOutputFlags[9];
	int v1OutputFlags[9];
	// For accum circuit
	int a_pulseTrainElement[16] = { 1, 1,1,1,1 ,1,1,1,1, 1,1,1,1, 1,1,1};
	int a_receivingStorePulse[16];
	int a_receivingStorePulseComplement[16];
	int a_guideOutputFlags[16];
	int a_v1OutputFlags[16];
	// TODO: This is temporary to facilitate addition. Move this to the
	// actual relay model once you are done
	Dekatron carryRelays[9];
	Dekatron bufferDekatrons_s[9];
	Dekatron bufferDekatrons_r[9];
	DekatronStore* sendingStore;
	DekatronStore* receivingStore;

	ShiftCircuit shiftCircuit;
	// Accum circuit
	Dekatron a_carryRelays[16];
	Dekatron a_bufferDekatrons_s[16];
	Dekatron a_bufferDekatrons_r[16];
	Accumulator* sendingAccum;
	Accumulator* receivingAccum;
	Accumulator tempAccum;

	void setSendingStore(DekatronStore* store);
	void setReceivingStore(DekatronStore* store);
	void initializeCarryRelays(DekatronStore* store);
	void initializeGuideOutputFlags(DekatronStore* store);
	void initializeBufferDekatrons(DekatronStore* store);
	void initializeReceivingStorePulse(DekatronStore* store);
	void initializeV1OutputFlags(DekatronStore* store);

	void makeReceivingStorePulse(DekatronStore* store);
	void makeCarryOver(DekatronStore* store);
	// TODO : remove after testing
	std::string dekatronArrayToString(Dekatron* arr, int size);

	// TODO in each step : pulse the store. copy to temp accum - transfer
	// copy to accum and so forth. The changes should be visible from
	// both the stores and accumulators

	void setSendingAccumulator(Accumulator* accum);
	void setReceivingAccumulator(Accumulator* accum);
	void initializeTempAccum(Accumulator* accum);
	void initializeCarryRelays(Accumulator* accum);
	void initializeGuideOutputFlags(Accumulator* accum);
	void initializeBufferDekatrons(Accumulator* accum);
	void initializeReceivingStorePulse(Accumulator* accum);
	void initializeV1OutputFlags(Accumulator* accum);
	void makeReceivingStorePulse(Accumulator* accum);
	void makeCarryOver(Accumulator* accum);


	void updateCarryRelays(int pulses[], Dekatron* bufferDekatrons,Dekatron* carryRelays, int size = 9);
	void updateGuideOutputFlags(Dekatron* bufferDekatrons, int guideOutputFlags[], int size = 9);
	void updateV1OutputFlags(Dekatron* bufferDekatrons, int guideOutputFlags[], int v1OutputFlags[], int size = 9);


public:
	// TODO: Transfer unit does not check if stores are from the same set
	// TODO: Transfer does not use temp accum. Remove if not needed
	// Transfer from store to store
	void transfer(DekatronStore* sStore, DekatronStore* rStore, int shiftAmount = 0);
	void transferComplement(DekatronStore* sStore, DekatronStore* rStore, int shiftAmount = 0);
	// Transfer from accum to store
	void transfer(Accumulator* accum, DekatronStore* rStore, int shiftAmount = 0 );
	void transferComplement(Accumulator* accum, DekatronStore* rStore, int shiftAmount = 0 );
	// Transfer from store to accum
	void transfer(DekatronStore* sStore, Accumulator* accum, int shiftAmount = 0);
	void transferComplement(DekatronStore* sStore, Accumulator* accum, int shiftAmount = 0);
};
#endif /* TRANSFERUNIT_H */

