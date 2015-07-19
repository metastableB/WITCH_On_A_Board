/*
 * witch.h
 *
 * The master object for the witch simulator.
 * Contains all the 'submodules' of the WITCH.
 *
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 19-Jul-2015
 * 
 */

#ifndef WITCH_H
#define WITCH_H

#include "dekatron.h"
#include "dekatronstore.h"
#include "transferunit.h"
#include "shiftcircuit.h"
#include "accumulator.h"
#include "alu.h"
#include "translator.h"

#include "lib/logger.h"
#include "lib/definitions.h"

#include <string>

class WITCH {
	DekatronStore dekatronArray[NO_OF_STORE_ROW][NO_OF_STORE_COL];
	Accumulator accum;
	ALU alu;
	Translator translator;

	Logger logObj;
public:
	// Ensure correct store is indexed
	DekatronStore* getStore(std::string index);

};
#endif /*WITCH_H*/



