/*
 * dekatron.h
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 27 May,2015
 */


#ifndef DEKATRON_H
#define DEKATRON_H

#include <iostream>

enum class DekatronState : int {
	ZERO,
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	END_OF_LIST
};

class Dekatron {
	// TODO (metastableB): the WITCH does not have a default value. Remove
	// this if not required.
	DekatronState state;
	
	public:
		Dekatron ();	
		DekatronState incrementState();
		DekatronState getCurrentState();
		// Overload operators as required
};
#endif /* DEKATRON_H */