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
	// Pulses are treated as 2D array of size 9*9. Where each
	// subarray of 9 represents a parallel set of pulses sent to
	// the dekatron stores
	void pulseStore(int arr[] , Dekatron CarryRelays[]);
	// In case we need to create the entire train at once
	void pulseStore(int arr[][9]);
	// TODO : Define the getter methods according to the
	// required data types.
	std::string getStateInStore();
};

#endif /* DEKATRONSTORE_H */




