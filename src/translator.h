/*
 * translator.h
 *
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 18-Jul-2015
 * 
 */

#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include "dekatron.h"
#include "dekatronstore.h"
#include "accumulator.h"
// TODO : This object currently acts as a place holder till we are ready with
//	  the details of how the translator actually works

class Translator {
public:
	// Store string_input of length 5/8 at sore
	// return if error!
	bool store(std::string input, DekatronStore* store);
	bool load();
};

#endif /*TRANSLATOR_H*/
