/*
 * dekatronStore.cpp
 *
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 28-May-2015
 * 
 */

#include "dekatronstore.h"

void DekatronStore:: pulseStore (int pulses[], Dekatron CarryRelays[]) {
	// LSB : 8 , MSB 1, Sign Bit 0
	// If the incremented value reaches zero again, simulate carry by
	// updating the carry relays.
	if ( pulses[8] == 1) {
		if( this->store[8].incrementState() == DekatronState::ZERO)
			CarryRelays[8] = DekatronState::ONE;
	} else if (pulses[8] != 1) {
		// TODO : Error handlers - Something went wrong here
	}

	if ( pulses[7] == 1) {
		if( this->store[7].incrementState() == DekatronState::ZERO)
			CarryRelays[7] = DekatronState::ONE;
	} else if (pulses[7] != 1) {
		// TODO : Error handlers - Something went wrong here
	}
	if ( pulses[6] == 1) {
		if( this->store[6].incrementState() == DekatronState::ZERO)
			CarryRelays[6] = DekatronState::ONE;
	} else if (pulses[6] != 1) {
		// TODO : Error handlers - Something went wrong here
	}
	if ( pulses[5] == 1) {
		if( this->store[5].incrementState() == DekatronState::ZERO)
			CarryRelays[5] = DekatronState::ONE;
	} else if (pulses[5] != 1) {
		// TODO : Error handlers - Something went wrong here
	}
	if ( pulses[4] == 1) {
		if( this->store[4].incrementState() == DekatronState::ZERO)
			CarryRelays[4] = DekatronState::ONE;
	} else if (pulses[4] != 1) {
		// TODO : Error handlers - Something went wrong here
	}
	if ( pulses[3] == 1) {
		if( this->store[3].incrementState() == DekatronState::ZERO)
			CarryRelays[3] = DekatronState::ONE;
	} else if (pulses[3] != 1) {
		// TODO : Error handlers - Something went wrong here
	}
	if ( pulses[2] == 1) {
		if( this->store[2].incrementState() == DekatronState::ZERO)
			CarryRelays[2] = DekatronState::ONE;
	} else if (pulses[2] != 1) {
		// TODO : Error handlers - Something went wrong here
	}
	if ( pulses[1] == 1) {
		if( this->store[1].incrementState() == DekatronState::ZERO)
			CarryRelays[1] = DekatronState::ONE;
	} else if (pulses[1] != 1) {
		// TODO : Error handlers - Something went wrong here
	}
	if ( pulses[0] == 1) {
		if( this->store[0].incrementState() == DekatronState::ZERO)
			CarryRelays[0] = DekatronState::ONE;
	} else if (pulses[0] != 1) {
		// TODO : Error handlers - Something went wrong here
	}
	
}



