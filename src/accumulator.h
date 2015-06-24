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

class Accumulator {
	DekatronStore accumulatorA;
	DekatronStore accumulatorB;
public:
	void getAcumulatorValue();

	Dekatron store[9];

public:
	// Pulses are treated as 2D array . Where each
	// subarray represents a parallel set of 9 pulses sent to
	// the dekatron stores.
	void pulseStore(int arr[], Dekatron newState[]);
	// In case we need to create the entire train at once
	void pulseStore(int arr[][9]);
	// Setting all the stores at once
	void setStoreValue(int arr[], Dekatron newState[]);
	int setStoreValue(std::string value, Dekatron newState[]);
	// TODO : Define the getter methods according to the
	// required data types.
	std::string getStringStateInStore();
	DekatronState getStateIn(int index);
};
#endif // ACCUMULATOR_H



