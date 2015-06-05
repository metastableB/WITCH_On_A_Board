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

void TransferUnit::setReceivingStore(DekatronStore* store) {
	this->receivingStore = store;
}

void TransferUnit::initializeCarryRelays() {
	for (int i = 0 ; i < 9 ; i++)
		this->carryRelays[i].setDekatronState(DekatronState::ZERO);
}

void TransferUnit::initializeGuideOutputFlags(){
	for (int i = 0; i < 9 ; i++)
		guideOutputFlags[i] = 0;
}

void TransferUnit::initializeBufferDekatrons(){
	for(int i = 0; i < 9; i++){
		this->bufferDekatrons_s[i].setDekatronState(DekatronState::ZERO);
		this->bufferDekatrons_r[i].setDekatronState(DekatronState::ZERO);
	}
}

void TransferUnit::initializeReceivingStorePulse(){
	for(int i = 0; i < 9; i++)
		this->receivingStorePulse[i] = 0;
}

void TransferUnit::initializeReceivingStorePulseComplement(){
	for(int i = 0; i < 9; i++)
		this->receivingStorePulseComplement[i] = 1;
}

void TransferUnit::initializeV1OutputFlags(){
	for(int i=0; i < 9; i++)
		this->v1OutputFlags[i] = 0;
}
std::string TransferUnit::dekatronArrayToString(Dekatron* arr, int size) {
	std::string s;
	for(int i = 0; i < size; i++) {
		s.append(std::to_string(arr[i].getCurrentNumber()));
	}
	return s;
}

// The guide is flagged on a 9 to 0 transitions
void TransferUnit::updateGuideOutputFlags(Dekatron* bufferDekatrons) {
	for(int i = 0; i < 9 ; i++)
		if(bufferDekatrons[i].getCurrentState() == DekatronState::ZERO)
			guideOutputFlags[i] = 1;
}

// If a guide pulse has been produced and a 0-1 transition occurs
// V1 is active.
void TransferUnit::updateV1OutputFlags(Dekatron* bufferDekatrons) {
	for(int i = 0; i < 9; i++)
		if(bufferDekatrons[i].getCurrentState() == DekatronState::ONE
			&& guideOutputFlags[i] == 1)
			v1OutputFlags[i] = 1;
}

// If any of the receiving stores reach zero on pulsing,
// it means a carry over
void TransferUnit::updateCarryRelays(int pulseSent[], Dekatron* bufferDekatrons){
	for(int i = 0 ; i < 9; i++)
		if(bufferDekatrons[i].getCurrentState() == DekatronState::ZERO && 
			pulseSent[i] == 1)
			carryRelays[i].setDekatronState(DekatronState::ONE);
}

void TransferUnit::makeReceivingStorePulse(){
	for(int i = 0; i < 9; i++)
		if(v1OutputFlags[i] == 1)
			receivingStorePulse[i] = 1;

}
void TransferUnit::makeReceivingStorePulseComplement(){
	for(int i = 0; i < 9; i++)
		if(v1OutputFlags[i] == 1)
			receivingStorePulse[i] = 0;

}
// Recursively Completes carry operations required
void TransferUnit::makeCarryOver() {
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
	initializeCarryRelays();
	updateCarryRelays(tempCarryPulse, bufferDekatrons_r);
	makeCarryOver();
}
// TODO: (note) The ordering within the for loop is important fot the logic
void TransferUnit::transfer(DekatronStore* sStore, DekatronStore* rStore) {
	setSendingStore(sStore);
	setReceivingStore(rStore);
	initializeCarryRelays();
	initializeGuideOutputFlags();
	initializeBufferDekatrons();
	initializeReceivingStorePulse();
	initializeV1OutputFlags();

	// Send a set of pulse to sending dekatron
	for (int i = 0 ; i < 10 ; i++) {
		sendingStore->pulseStore(pulseTrainElement,bufferDekatrons_s);
		updateGuideOutputFlags(bufferDekatrons_s);
		updateV1OutputFlags(bufferDekatrons_s);
		makeReceivingStorePulse();

		receivingStore->pulseStore(receivingStorePulse, bufferDekatrons_r);
		updateCarryRelays(receivingStorePulse, bufferDekatrons_r);
	}
	makeCarryOver();
}
void TransferUnit::trasferComplement(DekatronStore* sStore, DekatronStore* rStore){
	setSendingStore(sStore);
	setReceivingStore(rStore);
	initializeCarryRelays();
	initializeGuideOutputFlags();
	initializeBufferDekatrons();
	initializeReceivingStorePulseComplement();
	initializeV1OutputFlags();

	// Send a set of pulse to sending dekatron
	for (int i = 0 ; i < 10 ; i++) {
		sendingStore->pulseStore(pulseTrainElement,bufferDekatrons_s);
		updateGuideOutputFlags(bufferDekatrons_s);
		updateV1OutputFlags(bufferDekatrons_s);
		makeReceivingStorePulseComplement();

		receivingStore->pulseStore(receivingStorePulseComplement, bufferDekatrons_r);
		updateCarryRelays(receivingStorePulseComplement, bufferDekatrons_r);
	}
	makeCarryOver();
}

