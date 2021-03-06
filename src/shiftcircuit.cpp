/*
 * shiftcircuit.cpp
 *
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 13-Jun-2015
 * 
 */

#include "shiftcircuit.h"

void ShiftCircuit::initializeShiftDekatron(DekatronState state){
	for(int i = 0; i < 16; i++)
		this->shiftDekatron[i].setDekatronState(state);
}
void ShiftCircuit::shift(Dekatron* buffer, int shiftAmount, int size) {

	if(shiftAmount > 7 || shiftAmount < -1 )
	// TODO : ERROR
		return;

	initializeShiftDekatron(buffer[0].getCurrentState());
	for(int i = 1; i < 9; i++)
		this->shiftDekatron[i + shiftAmount] = buffer[i];
	for(int i = 1; i < size ; i++)
		buffer[i] = this->shiftDekatron[i];
}
