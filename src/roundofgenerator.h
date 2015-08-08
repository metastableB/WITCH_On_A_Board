/*
 * roundofgenerator.h
 *
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 08-Aug-2015
 *
 */

#ifndef ROUNDOFGENERATOR_H
#define ROUNDOFGENERATOR_H

#include "dekatronstore.h"
#include "dekatron.h"
#include <ctime>
#include <cstdlib>

class RoundOfGenerator{
	DekatronStore roundOf;
public:
	RoundOfGenerator(){
		std::srand(std::time(0));
	}
	DekatronStore* getRoundOf();
};

#endif // ROUNDOFGENERATOR_H



