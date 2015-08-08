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
#include "dekatron.h"
#include "dekatronstore.h"
#include "transferunit.h"

class ALU {
	// TODO : [Reminder] since we have more than one accum, we use a pointer here
	TransferUnit transferUnit;
public :
	// TODO : the return value to be used for overflow checks
	bool add(DekatronStore* sStore, DekatronStore* rStore);
	bool addAndClear(DekatronStore* sStore, DekatronStore* rStore);
	bool addPositiveModulus(DekatronStore* sStore,DekatronStore* rStore);
	bool subtract(DekatronStore* sStore, DekatronStore* rStore);
	bool subtractAndClear(DekatronStore* sStore, DekatronStore* rStore);
	bool multiply(DekatronStore* sStore, DekatronStore* rStore, Accumulator* accum);
	bool divide(DekatronStore* sStore, DekatronStore* rStore, Accumulator* accum);

};

#endif /*ALU_H*/

