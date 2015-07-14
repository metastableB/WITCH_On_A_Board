/*
 * transferunit.cpp
 *
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 28-May-2015
 * 
 */
#include "transferunit.h"

void TransferUnit::setSendingStore(DekatronStore* store) {
	this->sendingStore = store;
}
void TransferUnit::setSendingAccumulator(Accumulator* accum) {
	this->sendingAccum = accum;
}

void TransferUnit::setReceivingStore(DekatronStore* store) {
	this->receivingStore = store;
}

void TransferUnit::setReceivingAccumulator(Accumulator* accum) {
	this->receivingAccum = accum;
}

void TransferUnit::initializeCarryRelays(DekatronStore* store) {
	for (int i = 0 ; i < 9 ; i++)
		this->carryRelays[i].setDekatronState(DekatronState::ZERO);
}

void TransferUnit::initializeCarryRelays(Accumulator* accum) {
	for (int i = 0 ; i < 16 ; i++)
		this->a_carryRelays[i].setDekatronState(DekatronState::ZERO);
}

void TransferUnit::initializeGuideOutputFlags(DekatronStore* store){
	for (int i = 0; i < 9 ; i++)
		guideOutputFlags[i] = 0;
}
void TransferUnit::initializeGuideOutputFlags(Accumulator* accum){
	for (int i = 0; i < 16 ; i++)
		a_guideOutputFlags[i] = 0;
}

void TransferUnit::initializeBufferDekatrons(DekatronStore* store){
	for(int i = 0; i < 9; i++){
		this->bufferDekatrons_s[i].setDekatronState(DekatronState::ZERO);
		this->bufferDekatrons_r[i].setDekatronState(DekatronState::ZERO);
	}
}


void TransferUnit::initializeBufferDekatrons(Accumulator* accum){
	for(int i = 0; i < 16; i++){
		this->a_bufferDekatrons_s[i].setDekatronState(DekatronState::ZERO);
		this->a_bufferDekatrons_r[i].setDekatronState(DekatronState::ZERO);
	}
}

void TransferUnit::initializeReceivingStorePulse(DekatronStore* store){
	for(int i = 0; i < 9; i++){
		this->receivingStorePulse[i] = 0;
		this->receivingStorePulseComplement[i] = 1;
	}
}
void TransferUnit::initializeReceivingStorePulse(Accumulator* accum){
	for(int i = 0; i < 16; i++){
		this->a_receivingStorePulse[i] = 0;
		this->a_receivingStorePulseComplement[i] = 1;
	}
}

void TransferUnit::initializeV1OutputFlags(DekatronStore* store){
	for(int i=0; i < 9; i++)
		this->v1OutputFlags[i] = 0;
}

void TransferUnit::initializeV1OutputFlags(Accumulator* accum){
	for(int i=0; i < 16; i++)
		this->a_v1OutputFlags[i] = 0;
}

void TransferUnit::initializeTempAccum(Accumulator* accum){
	for(int i = 0; i < 16 ;i++)
		this->tempAccum.setAccumulatorValueIn(i,0);
}

std::string TransferUnit::dekatronArrayToString(Dekatron* arr, int size) {
	std::string s;
	for(int i = 0; i < size; i++) {
		s.append(std::to_string(arr[i].getCurrentNumber()));
	}
	return s;
}

// The guide is flagged on a 9 to 0 transitions
void TransferUnit::updateGuideOutputFlags(Dekatron* bufferDekatrons,int guideOutputFlags[], int size ) {
	for(int i = 0; i < size ; i++)
		if(bufferDekatrons[i].getCurrentState() == DekatronState::ZERO)
			guideOutputFlags[i] = 1;
}

// If a guide pulse has been produced and a 0-1 transition occurs
// V1 is active.
void TransferUnit::updateV1OutputFlags(Dekatron* bufferDekatrons,int guideOutputFlags[],int v1OutputFlags[], int size) {
	for(int i = 0; i < size; i++)
		if(/*bufferDekatrons[i].getCurrentState() == DekatronState::ZERO
			&& */guideOutputFlags[i] == 1)
			v1OutputFlags[i] = 1;
}

// If any of the receiving stores reach zero on pulsing,
// it means a carry over
void TransferUnit::updateCarryRelays(int pulseSent[], Dekatron* bufferDekatrons,Dekatron* carryRelays, int size ){
	for(int i = 0 ; i < size; i++)
		if(bufferDekatrons[i].getCurrentState() == DekatronState::ZERO && 
			pulseSent[i] == 1)
			carryRelays[i].setDekatronState(DekatronState::ONE);
}

void TransferUnit::makeReceivingStorePulse(DekatronStore* store){
	for(int i = 0; i < 9; i++)
		if(v1OutputFlags[i] == 1) {
			receivingStorePulse[i] = 1;
			receivingStorePulseComplement[i] = 0;
		}
}
void TransferUnit::makeReceivingStorePulse(Accumulator* store){
	for(int i = 0; i < 16; i++)
		if(a_v1OutputFlags[i] == 1) {
			a_receivingStorePulse[i] = 1;
			a_receivingStorePulseComplement[i] = 0;
		}
}


// Recursively Completes carry operations required
void TransferUnit::makeCarryOver(DekatronStore* store) {
	int tempCarryPulse[9] = {0,0,0,0,0,0,0,0,0};
	int sum = 0;
	// Transfering carries
	for(int i = 8; i >= 0; i--) {
		if(carryRelays[i].getCurrentState() == DekatronState::ONE) {
			tempCarryPulse[(i+8)%9] = 1;
			sum += tempCarryPulse[(i+8)%9];
		}
	}
	// if there are no carry to be done, return
	if (sum == 0)
		return;
	// Continue till there are no more carry overs
	receivingStore->pulseStore(tempCarryPulse, bufferDekatrons_r);
	initializeCarryRelays(store);
	updateCarryRelays(tempCarryPulse, bufferDekatrons_r, carryRelays);
	makeCarryOver(store);
}
void TransferUnit::makeCarryOver(Accumulator* accum) {
	int tempCarryPulse[16] = {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0};
	int sum = 0;
	for(int i = 15; i >= 0; i--) {
		if(a_carryRelays[i].getCurrentState() == DekatronState::ONE) {
			tempCarryPulse[(i+15)%16] = 1;
			sum += tempCarryPulse[(i+15)%16];
		}
	}
	// if there are no carry to be done, return
	if (sum == 0)
		return;
	accum->pulseAccumulator(tempCarryPulse, a_bufferDekatrons_r);
	initializeCarryRelays(accum);
	updateCarryRelays(tempCarryPulse, a_bufferDekatrons_r,a_carryRelays,16);
	makeCarryOver(accum);
}
// Store to Store
// Pulses from 0-1 (inclusive) are effective in moving the receiving store
void TransferUnit::transfer(DekatronStore* sStore, DekatronStore* rStore, int shiftAmount ) {
	setSendingStore(sStore);
	setReceivingStore(rStore);
	initializeCarryRelays(sStore);
	initializeGuideOutputFlags(sStore);
	initializeBufferDekatrons(sStore);
	initializeReceivingStorePulse(sStore);
	initializeV1OutputFlags(sStore);

	// Send a set of pulse to sending dekatron
	for (int i = 0 ; i < 10 ; i++) {
		sendingStore->pulseStore(pulseTrainElement,bufferDekatrons_s);
		shiftCircuit.shift(bufferDekatrons_s,shiftAmount);
		updateV1OutputFlags(bufferDekatrons_s, guideOutputFlags, v1OutputFlags);
		updateGuideOutputFlags(bufferDekatrons_s,this->guideOutputFlags);
		makeReceivingStorePulse(rStore);

		receivingStore->pulseStore(receivingStorePulse, bufferDekatrons_r);
		updateCarryRelays(receivingStorePulse, bufferDekatrons_r,carryRelays);
		//std::cout << "Pulse no" << i+1 << " s " << sendingStore->getStringStateInStore()
		//	<< " r " << receivingStore->getStringStateInStore() ;
		//std::cout << " Guide Output flags :";
		//for(int j = 0; j<9 ;j++) {
		//	std::cout << this->guideOutputFlags[j];
		//}
		//std::cout << "\n";
	}
	makeCarryOver(rStore);
}
// Pulses before 9-0 (inclusive of 9-0, excluding first pulse) are effective in moving the receiving store
void TransferUnit::transferComplement(DekatronStore* sStore, DekatronStore* rStore, int shiftAmount ){
	setSendingStore(sStore);
	setReceivingStore(rStore);
	initializeCarryRelays(sStore);
	initializeGuideOutputFlags(sStore);
	initializeBufferDekatrons(sStore);
	initializeReceivingStorePulse(sStore);
	initializeV1OutputFlags(sStore);

	// Send a set of pulse to sending dekatron
	for (int i = 0 ; i < 10 ; i++) {
		sendingStore->pulseStore(pulseTrainElement,bufferDekatrons_s);
		shiftCircuit.shift(bufferDekatrons_s,shiftAmount);
		updateV1OutputFlags(bufferDekatrons_s, guideOutputFlags, v1OutputFlags);
		updateGuideOutputFlags(bufferDekatrons_s,this->guideOutputFlags);
		makeReceivingStorePulse(rStore);
		// We use complement on 9 and not ten. hence ignore
		if(i != 0) {
			receivingStore->pulseStore(receivingStorePulseComplement, bufferDekatrons_r);
			updateCarryRelays(receivingStorePulseComplement, bufferDekatrons_r,carryRelays);
		}
			//std::cout << "Pulse no" << i+1 << " s " << sendingStore->getStringStateInStore()
			//			<< " r " << receivingStore->getStringStateInStore() << "\n";
					//std::cout << " Guide Output flags :";
					//for(int j = 0; j<9 ;j++) {
					//	std::cout << this->guideOutputFlags[j];
					//}
					//std::cout << "\n";
	}
	makeCarryOver(rStore);
}

// Accumulator to store
void TransferUnit::transfer(Accumulator* accum, DekatronStore* rStore, int shiftAmount ) {

}
void TransferUnit::transferComplement(Accumulator* accum, DekatronStore* rStore, int shiftAmount  ) {

}
// Store to Accumulator

void TransferUnit::transfer(DekatronStore* sStore, Accumulator* accum, int shiftAmount ) {
	// TODO: make sure shiftAmounts are in the range [-1,7]
	// TODO: Remove tempAccum if not needed
	initializeTempAccum(accum);
	initializeCarryRelays(accum);
	initializeGuideOutputFlags(accum);
	initializeBufferDekatrons(accum);
	initializeReceivingStorePulse(accum);
	initializeV1OutputFlags(accum);

	for(int i = 1; i <= 8 ; i++)
		tempAccum.setAccumulatorValueIn(i + shiftAmount, int(sStore->getStateIn(i)));
	tempAccum.setAccumulatorSign(int(sStore->getStateIn(0)));
	setSendingAccumulator(&tempAccum);
	setSendingStore(sStore);
	setReceivingAccumulator(accum);
	// Send a set of pulse to sending dekatron
	for (int i = 0 ; i < 10 ; i++) {
		sendingStore->pulseStore(pulseTrainElement,a_bufferDekatrons_s);
		shiftCircuit.shift(a_bufferDekatrons_s,shiftAmount,16);
		updateV1OutputFlags(a_bufferDekatrons_s ,a_guideOutputFlags, a_v1OutputFlags,16);
		updateGuideOutputFlags(a_bufferDekatrons_s, a_guideOutputFlags,16);

		makeReceivingStorePulse(accum);

		receivingAccum->pulseAccumulator(a_receivingStorePulse, a_bufferDekatrons_r);
		updateCarryRelays(a_receivingStorePulse, a_bufferDekatrons_r,a_carryRelays,16);
		initializeBufferDekatrons(accum);
	}
	makeCarryOver(accum);
}
void TransferUnit::transferComplement(DekatronStore* sStore, Accumulator* accum, int shiftAmount) {
	// TODO: make sure shiftAmounts are in the range [-1,7]
	// TODO: Remove tempAccum if not needed
	initializeTempAccum(accum);
	initializeCarryRelays(accum);
	initializeGuideOutputFlags(accum);
	initializeBufferDekatrons(accum);
	initializeReceivingStorePulse(accum);
	initializeV1OutputFlags(accum);

	for(int i = 1; i <= 8 ; i++)
		tempAccum.setAccumulatorValueIn(i + shiftAmount, int(sStore->getStateIn(i)));
	tempAccum.setAccumulatorSign(int(sStore->getStateIn(0)));
	setSendingAccumulator(&tempAccum);
	setSendingStore(sStore);
	setReceivingAccumulator(accum);
	// Send a set of pulse to sending dekatron
	for (int i = 0 ; i < 10 ; i++) {
		sendingStore->pulseStore(pulseTrainElement,a_bufferDekatrons_s);
		shiftCircuit.shift(a_bufferDekatrons_s,shiftAmount,16);
		updateV1OutputFlags(a_bufferDekatrons_s ,a_guideOutputFlags, a_v1OutputFlags,16);
		updateGuideOutputFlags(a_bufferDekatrons_s, a_guideOutputFlags,16);

		makeReceivingStorePulse(accum);

		if(i != 0) {
			receivingAccum->pulseAccumulator(a_receivingStorePulseComplement, a_bufferDekatrons_r);
			updateCarryRelays(a_receivingStorePulseComplement, a_bufferDekatrons_r,a_carryRelays,16);
		}
		initializeBufferDekatrons(accum);
	}
	makeCarryOver(accum);
}


void TransferUnit::transferClear(DekatronStore* sStore, DekatronStore* rStore) {
	setSendingStore(sStore);
	setReceivingStore(rStore);
	initializeCarryRelays(sStore);
	initializeGuideOutputFlags(sStore);
	initializeBufferDekatrons(sStore);
	initializeReceivingStorePulse(sStore);
	initializeV1OutputFlags(sStore);

	// Connect the receiving store pulse complement to the sending store
	for (int i = 0 ; i < 10 ; i++) {
		sendingStore->pulseStore(receivingStorePulseComplement,bufferDekatrons_s);
		//shiftCircuit.shift(bufferDekatrons_s,0);
		updateGuideOutputFlags(bufferDekatrons_s,this->guideOutputFlags);
		updateV1OutputFlags(bufferDekatrons_s, guideOutputFlags, v1OutputFlags);
		makeReceivingStorePulse(rStore);

		receivingStore->pulseStore(receivingStorePulse, bufferDekatrons_r);
		updateCarryRelays(receivingStorePulse, bufferDekatrons_r,carryRelays);
		//std::cout << "Pulse no" << i+1 << " s " << sendingStore->getStringStateInStore()
		//		<< " r " << receivingStore->getStringStateInStore() << "\n";
	}
	makeCarryOver(rStore);
}
