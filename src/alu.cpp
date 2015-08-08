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
	// TODO : Check for overflow, also check for errors at WITCH::executeArithmeticOrder()
	return true;
}

bool ALU::subtract(DekatronStore* sStore, DekatronStore* rStore){
	transferUnit.transferComplement(sStore,rStore);
	// TODO : Check for overflow
	return true;
}

bool ALU::addAndClear(DekatronStore* sStore, DekatronStore* rStore){
	transferUnit.transferClear(sStore,rStore);
	return true;
}

bool ALU::subtractAndClear(DekatronStore* sStore, DekatronStore* rStore){
	transferUnit.transferComplementClear(sStore,rStore);
	return true;
}

bool ALU::multiply(DekatronStore* sStore, DekatronStore* rStore, Accumulator* accum){
	// TODO : Check for overflow
	int currentDigit = 0;
	if(rStore->getStateIn(0) == DekatronState::ZERO) {
		for(int i = 1; i < 9; i++){
			currentDigit = int(rStore->getStateIn(i));
			while( currentDigit > 0){
				transferUnit.transfer(sStore,accum,i-1);
				currentDigit--;
				rStore->setStoreValueIn(i,currentDigit);
			}
		}
		return true;
	}
	else if (rStore->getStateIn(0) ==  DekatronState::NINE) {
		for(int i = 1; i < 9; i++){
			currentDigit = int(rStore->getStateIn(i));
			do {
				transferUnit.transferComplement(sStore,accum,i-1);
				rStore->setStoreValueIn(i,(currentDigit)%10);
				currentDigit++;
			} while( currentDigit%10 != 0);
			transferUnit.transfer(sStore,accum,i-1);
		}
		return true;
	}
	// TODO: ERROR HANDLER!
	return false;
}

bool ALU::addPositiveModulus(DekatronStore* sStore,DekatronStore* rStore){
	if(sStore->getStateIn(0) == DekatronState::ZERO)
		transferUnit.transfer(sStore,rStore);
	else if(sStore->getStateIn(0) == DekatronState::NINE)
		transferUnit.transferComplement(sStore,rStore);
	else // TODO:ERROR HANDLER
		return false;
	return true;
}



