/*
 * dekatronStore.cpp
 *
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 28-May-2015
 * 
 */

#include "dekatronstore.h"

void DekatronStore::pulseStore(int pulses[], Dekatron newState[]) {
	// LSB : 8 , MSB 1, Sign Bit 0
	
	if (pulses[8] == 1) {
		newState[8].setDekatronState(this->store[8].incrementState());
	} else if (pulses[8] != 1) {
		// TODO : Error handlers - Something went wrong here
	}

	if (pulses[7] == 1) {
		newState[7].setDekatronState(this->store[7].incrementState());
	} else if (pulses[7] != 1) {
		// TODO : Error handlers - Something went wrong here
	}
	if (pulses[6] == 1) {
		newState[6].setDekatronState(this->store[6].incrementState());
	} else if (pulses[6] != 1) {
		// TODO : Error handlers - Something went wrong here
	}
	if (pulses[5] == 1) {
		newState[5].setDekatronState(this->store[5].incrementState());
	} else if (pulses[5] != 1) {
		// TODO : Error handlers - Something went wrong here
	}
	if (pulses[4] == 1) {
		newState[4].setDekatronState(this->store[4].incrementState());
	} else if (pulses[4] != 1) {
		// TODO : Error handlers - Something went wrong here
	}
	if (pulses[3] == 1) {
		newState[3].setDekatronState(this->store[3].incrementState());
	} else if (pulses[3] != 1) {
		// TODO : Error handlers - Something went wrong here
	}
	if (pulses[2] == 1) {
		newState[2].setDekatronState(this->store[2].incrementState());
	} else if (pulses[2] != 1) {
		// TODO : Error handlers - Something went wrong here
	}
	if (pulses[1] == 1) {
		newState[1].setDekatronState(this->store[1].incrementState());
	} else if (pulses[1] != 1) {
		// TODO : Error handlers - Something went wrong here
	}
	if (pulses[0] == 1) {
		newState[0].setDekatronState(this->store[0].incrementState());
	} else if (pulses[0] != 1) {
		// TODO : Error handlers - Something went wrong here
	}

}

std::string DekatronStore::getStringStateInStore() {
	std::string state;
	state.append(std::to_string(this->store[0].getCurrentNumber()));
	state.append(std::to_string(this->store[1].getCurrentNumber()));
	state.append(std::to_string(this->store[2].getCurrentNumber()));
	state.append(std::to_string(this->store[3].getCurrentNumber()));
	state.append(std::to_string(this->store[4].getCurrentNumber()));
	state.append(std::to_string(this->store[5].getCurrentNumber()));
	state.append(std::to_string(this->store[6].getCurrentNumber()));
	state.append(std::to_string(this->store[7].getCurrentNumber()));
	state.append(std::to_string(this->store[8].getCurrentNumber()));
	return state;
}

