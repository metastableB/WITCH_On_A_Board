/*
 * dekatron.h
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 27 May,2015
 */

#include "dekatron.h"
Dekatron::Dekatron(){
	// TODO(metastableB) Remove if not required
	this->state =  DekatronState::ZERO;
}

DekatronState Dekatron::getCurrentState(){
	return this->state;
}

DekatronState Dekatron::incrementState() {
  switch(this->state) {
  	// Increment modulo 10
    case DekatronState::NINE : 
    	this->state = DekatronState::ZERO;
    	return this->state;
    default:
    	return (this->state = static_cast<DekatronState>(static_cast<int>(this->state)+1));
  }
}

