/*
 * transferunit.cpp
 *
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 28-May-2015
 * 
 */

void TransferUnit::setSendingStore(Dekatron* &store) {
	this->receivingStore = store;
}

void TransferUnit::setReceivingStore(Dekatron* &store) {
	this->sendingStore = store;
}

// Sends a 10 pulse train to sending store and retrieves the state stored
void TransferUnit::generatePulses() {
	// TODO : define this after testing the receiving mechanism

}

void TransferUnit::transfer(Dekatron* &sStore, Dekatron* &rStore) {
	this->setSendingStore(sStore);
	this->setReceivingStore(rStore);
	this->generatePulses();
	// At this point the pulseStore should hold the pulses to be sent
	// We creat the array per digit and send it to the pulse

}

