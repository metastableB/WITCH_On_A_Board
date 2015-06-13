/*
 * shiftcircuit.cpp
 *
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 13-Jun-2015
 * 
 */

#include "shiftcircuit.h"

void ShiftCircuit::initializeShiftDekatron(){
	for(int i = 0; i < 15; i++)
		this->shiftDekatron[i] == DekatronState::ZERO;
}
void ShiftCircuit::shift(Dekatron* buffer, int shiftAmount) {
	if(shiftAmount > 7 || shiftAmount < -1 );
		// TODO : ERROR
	initializeShiftDekatron();
	int noOfShift = 8;
	if(shiftAmount == -1)
		noOfShift = 7;
	for(int i = 1; i < noOfShift; i++)
		this->shiftDekatron[i + shiftAmount] = buffer[i];

	for(int i = 1; i < 9 ; i++)
		buffer[i] = this->shiftDekatron[i];
}
