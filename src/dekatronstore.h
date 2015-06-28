/*
 * dekatronstore.h
 *
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 28-May-2015
 * 
 */

#ifndef DEKATRONSTORE_H
#define DEKATRONSTORE_H

#include "dekatron.h"
#include <string>

class DekatronStore {
	// TODO: Figure out a better variable name maybe?
	// LSB : 8, MSB : 1 , Sign Bit : 0
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
	void setStoreValue(int arr[]);
	void setStoreValueIn(int index, int value);
	int setStoreValue(std::string value, Dekatron newState[]);
	// TODO : Define the getter methods according to the
	// required data types.
	std::string getStringStateInStore();
	DekatronState getStateIn(int index);
};

#endif /* DEKATRONSTORE_H */

