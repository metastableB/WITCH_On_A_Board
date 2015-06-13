/*
 * shiftcircuit.h
 *
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 13-Jun-2015
 * 
 */


#ifndef SHIFTCIRCUIT_H
#define SHIFTCIRCUIT_H

#include "dekatron.h"
#include "accumulator.h"

class ShiftCircuit {
	// to store the intermediate values while transfering to acc
	Dekatron shiftDekatron[15];
	void initializeShiftDekatron();
public :
	void shift(Dekatron* buffer, int shiftAmount);
	void shiftAcc(Accumulator* acc, int shiftAmount);
};
#endif // SHIFTCIRCUIT_H



