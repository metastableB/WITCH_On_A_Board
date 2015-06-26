/*
 * accumulator.h
 *
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 05-Jun-2015
 * 
 */

#ifndef ACCUMULATOR_H
#define ACCUMULATOR_H

#include "dekatron.h"
#include "dekatronstore.h"
#include <string>

// The accumulator is made up of two stores. This detail is hidden
// Outside this class. Other objects index from 0-16. 0 Being sign bit.


class Accumulator {
	DekatronStore accumulatorA;
	DekatronStore accumulatorB;
public:
	void pulseAccumulator(int arr[]);
	void setAccumulatorValue(int arr[]);
	int setAccumulatorValue(std::string value);
	void setAccumulatorValueIn(int index, int value);
	std::string getStringStateInStore();
	DekatronState getStateIn(int index);
};
#endif // ACCUMULATOR_H



