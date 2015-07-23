/*
 * translator.cpp
 *
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 18-Jul-2015
 * 
 */

#include "translator.h"

bool Translator::storeValue(std::string input, DekatronStore* store) {
	// input format is +ve[8 digits], -ve[8 digits], *[5 digits]
	char sign = input.at(0);
	if(sign != '+' || sign != '-' || sign != '*') {
		logObject.log( LogLevel::L_ERROR,"translator.cpp", "Received object with undefined sign.\n");
		return false;
	}else if (input.length() != 9 || input.length() != 5){
		logObject.log(LogLevel::L_ERROR, "translator.cpp","Received undefined input length.\n");
		return false;
	}
	if(sign == '+' && input.length() == 9) {
		store->setStoreValueIn(0,0);
		for(int i = 1; i < 9; i++)
			store->setStoreValueIn(i, input.at(i) - '0');
		return true;
	} else if ( sign == '-' && input.length() == 9) {
		store->setStoreValueIn(0,9);
		for(int i = 1; i < 9; i++)
			store->setStoreValueIn(i, 9 -(input.at(i) - '0'));
		return true;
	} else if (sign == '*' && input.length() == 5) {
		store->setStoreValueIn(0,0);
		for(int i = 1; i < 6; i++)
			store->setStoreValueIn(i, input.at(i) - '0');
		for(int i = 6; i <= 9; i++)
			store->setStoreValueIn(i, 0);
		return true;
	} else {
		logObject.log(LogLevel::L_ERROR, "translator.cpp","Received undefined sign -value pair.");
		return false;
	}
	// Control should not reach here
	logObject.log(LogLevel::L_ERROR, "translator.cpp","Undefined behavior.");
	return false;
}


