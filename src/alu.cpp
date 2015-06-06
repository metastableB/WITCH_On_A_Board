/*
 * alu.cpp
 *
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 05-Jun-2015
 * 
 */
#include "alu.h"

bool ALU::add(DekatronStore* sStore, DekatronStore* rStore){
	transferUnit.transfer(sStore,rStore);
	// TODO : Check for overflow
	return false;
}

bool ALU::subtract(DekatronStore* sStore, DekatronStore* rStore){
	transferUnit.transferComplement(sStore,rStore);
	// TODO : Check for overflow
	return false;
}



