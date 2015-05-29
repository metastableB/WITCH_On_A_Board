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
	this->receivingStore = store;
}

void TransferUnit::setReceivingStore(DekatronStore* store) {
	this->sendingStore = store;
}

void TransferUnit::initializeCarryRelays() {
	for (int i = 0 ; i < 9 ; i++)
		this->carryRelays[i].setDekatronState(DekatronState::ZERO);
}

void TransferUnit::initializeGuideOutputFlags(){
	for (int i = 0; i < 9 ; i++)
		guideOutputFlags[i] = 0;
}

// The guide produces a pulse on a ZERO to ONE
// transition (not the first transition)
void TransferUnit::updateGuideOutputFlags() {
	if(bufferDekatrons[0].getCurrentState() == DekatronState::ONE)
		guideOutputFlags[0] = 1;
	if(bufferDekatrons[1].getCurrentState() == DekatronState::ONE)
		guideOutputFlags[1] = 1;
	if(bufferDekatrons[2].getCurrentState() == DekatronState::ONE)
		guideOutputFlags[2] = 1;
	if(bufferDekatrons[3].getCurrentState() == DekatronState::ONE)
		guideOutputFlags[3] = 1;
	if(bufferDekatrons[4].getCurrentState() == DekatronState::ONE)
		guideOutputFlags[4] = 1;
	if(bufferDekatrons[5].getCurrentState() == DekatronState::ONE)
		guideOutputFlags[5] = 1;
	if(bufferDekatrons[6].getCurrentState() == DekatronState::ONE)
		guideOutputFlags[6] = 1;
	if(bufferDekatrons[7].getCurrentState() == DekatronState::ONE)
		guideOutputFlags[7] = 1;
	if(bufferDekatrons[8].getCurrentState() == DekatronState::ONE)
		guideOutputFlags[8] = 1;
}

// If any of the receiving stores reach zero on pulsing,
// it means a carry over
void TransferUnit::updateCarryRelays(){
	if(bufferDekatrons[0].getCurrentState() == DekatronState::ZERO)
		carryRelays[0].setDekatronState(DekatronState::ONE);
	if(bufferDekatrons[1].getCurrentState() == DekatronState::ZERO)
		carryRelays[1].setDekatronState(DekatronState::ONE);
	if(bufferDekatrons[2].getCurrentState() == DekatronState::ZERO)
		carryRelays[2].setDekatronState(DekatronState::ONE);
	if(bufferDekatrons[3].getCurrentState() == DekatronState::ZERO)
		carryRelays[3].setDekatronState(DekatronState::ONE);
	if(bufferDekatrons[4].getCurrentState() == DekatronState::ZERO)
		carryRelays[4].setDekatronState(DekatronState::ONE);
	if(bufferDekatrons[5].getCurrentState() == DekatronState::ZERO)
		carryRelays[5].setDekatronState(DekatronState::ONE);
	if(bufferDekatrons[6].getCurrentState() == DekatronState::ZERO)
		carryRelays[6].setDekatronState(DekatronState::ONE);
	if(bufferDekatrons[7].getCurrentState() == DekatronState::ZERO)
		carryRelays[7].setDekatronState(DekatronState::ONE);
	if(bufferDekatrons[8].getCurrentState() == DekatronState::ZERO)
		carryRelays[8].setDekatronState(DekatronState::ONE);
}

// Recursively Completes carry operations required
void TransferUnit::makeCarryOver() {
	int tempCarryPulse[9] = {0,0,0,0,0,0,0,0,0};
	if(carryRelays[8].getCurrentState() == DekatronState::ONE)
		tempCarryPulse[7] = 1;
	if(carryRelays[7].getCurrentState() == DekatronState::ONE)
		tempCarryPulse[6] = 1;
	if(carryRelays[6].getCurrentState() == DekatronState::ONE)
		tempCarryPulse[5] = 1;
	if(carryRelays[5].getCurrentState() == DekatronState::ONE)
		tempCarryPulse[4] = 1;
	if(carryRelays[4].getCurrentState() == DekatronState::ONE)
		tempCarryPulse[3] = 1;
	if(carryRelays[3].getCurrentState() == DekatronState::ONE)
		tempCarryPulse[2] = 1;
	if(carryRelays[2].getCurrentState() == DekatronState::ONE)
		tempCarryPulse[1] = 1;
	if(carryRelays[1].getCurrentState() == DekatronState::ONE)
		tempCarryPulse[0] = 1;
	if(carryRelays[0].getCurrentState() == DekatronState::ONE)
		tempCarryPulse[8] = 1;
	// if there are no carry to be done, return
	int sum = 0;
	for(int i = 0 ; i < 9; i++)
		sum += tempCarryPulse[i];
	if (sum == 0)
		return;
	// Continue till there are no more carry overs
	std::cout << "Carry exists and sums to " << sum <<" \n";
	receivingStore->pulseStore(tempCarryPulse, bufferDekatrons);
	std::cout << "Intermediate result being " << receivingStore->getStringStateInStore() << "\n";
	updateCarryRelays();
}

void TransferUnit::transfer(DekatronStore* sStore, DekatronStore* rStore) {
	setSendingStore(sStore);
	setReceivingStore(rStore);
	initializeCarryRelays();
	initializeGuideOutputFlags();

	for (int i = 0 ; i < 10 ; i++) {
		// Send a set of pulse to sending dekatron
		sendingStore->pulseStore(pulseTrainElement,carryRelays);
		// First pulse is irrelevant
		if( i != 0)
			updateGuideOutputFlags();
		receivingStore->pulseStore(guideOutputFlags, bufferDekatrons);
		updateCarryRelays();
	}
	makeCarryOver();
}

