/*
 * alu.h
 *
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 05-Jun-2015
 * 
 */

#ifndef ALU_H
#define ALU_H

#include "accumulator.h"
#include "dekatronstore.h"
#include "transferunit.h"

class ALU {
	Accumulator accumulator;
	TransferUnit transferUnit;
public :
	// TODO : the return value to be used for overflow checks
	bool add(DekatronStore* sStore, DekatronStore* rStore);
	bool subtract(DekatronStore* sStore, DekatronStore* rStore);
	bool multiply(DekatronStore* sStore, DekatronStore* rStore);
	bool divide(DekatronStore* sStore, DekatronStore* rStore);
	bool getAccumulatorValue();
};

#endif /*ALU_H*/

