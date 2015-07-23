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

enum WitchStatus {
	INVALID_STORE_INDEX,
	INVALID_STORE_ACCESS,
	INVALID_STORE_VALUE_H, // Human readable
	INVALID_STORE_VALUE_R,  // Raw
	OPERATION_SUCCESSFUL
};
class WITCH {
	DekatronStore dekatronArray[NO_OF_STORE_ROW][NO_OF_STORE_COL];
	Accumulator accum;
	ALU alu;
	Translator translator;

	Logger logObj;
	bool getDigitAt(std::string s,int index, int& num);
public:
	// Ensure correct store is indexed
	DekatronStore* getStore(std::string index);
	std::string translateStore(std::string index);
	WitchStatus translateAndStore(std::string index, std::string value);
	bool translateAndLoad(std::string index);

};
#endif /*WITCH_H*/



