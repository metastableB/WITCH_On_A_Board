/*
 * roundofgenerator.cpp
 *
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 08-Aug-2015
 *
 */

#include "roundofgenerator.h"

DekatronStore* RoundOfGenerator::getRoundOf(){
	int pulse[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0};
	Dekatron temp[9];
	pulse[8] = 	std::rand();
	roundOf.setStoreValue(pulse,temp);
	return &roundOf;
}



