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
#include "roundofgenerator.h"

#include "lib/logger.h"
#include "lib/definitions.h"

#include <string>

enum WitchStatus {
	INVALID_STORE_INDEX,
	INVALID_STORE_ACCESS,
	INVALID_STORE_VALUE_H, // Human readable
	INVALID_STORE_VALUE_R,  // Raw
	INVALID_WITCH_INPUT,

	VALID_INDEX,
	VALID_VALUE_H,
	VALID_VALUE_R,
	VALID_WITCH_ORDER, // Different from INVALID_INP_ORDER read from tape

	SET_ORDER,
	NOT_SET_ORDER,

	OPERATION_SUCCESSFUL,
	OPERATION_NOT_DEFINED, // features yet to implement
	OPERATION_FAILURE
};
class WITCH {
	DekatronStore dekatronArray[NO_OF_STORE_ROW][NO_OF_STORE_COL];
	Accumulator accum;
	ALU alu;
	Translator translator;
	DekatronStore currentOrder;
	RoundOfGenerator roundOfGenerator;

	// Global Class Flags
	WitchStatus orderStatus = NOT_SET_ORDER;

	DekatronStore* tempStore;
	Dekatron tempDekatronArr[9];
	Logger logObj;
	bool getDigitAt(std::string s,int index, int& num);
	/*
	 *  TODO: After deciding and segregating the tasks for the
	 *  	  Control unit, move the appropriate methods to it.
	 */
	WitchStatus validateStoreIndex(std::string index);
	WitchStatus validateStoreValue_H(std::string value);
	WitchStatus validateStoreValue_R(std::string value);
	WitchStatus WITCH_validateOrder(std::string order);
	WitchStatus validateOrdersArguments(std::string order);
	WitchStatus getStore(std::string index, DekatronStore*& store);
	WitchStatus executeArithmeticOrder();
	WitchStatus executeNonArithmeticOrder();

public:
	// Store to witch
	WitchStatus translateAndStore(std::string index, std::string value);
	WitchStatus translateAndLoad(std::string index,std::string& value);
	WitchStatus rawLoad(std::string index, std::string& value);
	WitchStatus setCurrentOrder(std::string);
	WitchStatus executeCurrentOrder();

	// Temporary methods, later to be reimplemented.

	std::string getAccumValue();
};
#endif /*WITCH_H*/



