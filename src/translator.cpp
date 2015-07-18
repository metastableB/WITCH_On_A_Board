/*
] * translator.cpp
 *
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 18-Jul-2015
 * 
 */

#include "translator.h"

bool Translator::store(std::string input, DekatronStore* store) {
	int sign = input.at(0) - '0';
	if(sign != 9 || sign != 0)
		// TODO : logoutput
		return false;
}


