/*
 * roundofgenerator.cpp
 *
 *  Created on: 08-Aug-2015
 *      Author: suckru
 */

#include "roundofgenerator.h"

DekatronStore* RoundOfGenerator::getRoundOf(){
	int pulse[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0};
	Dekatron temp[9];
	pulse[8] = 	std::rand();
	roundOf.setStoreValue(pulse,temp);
	return &roundOf;
}



