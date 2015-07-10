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

bool ALU::multiply(DekatronStore* sStore, DekatronStore* rStore, Accumulator* accum){
	/*
	 * Algorithm :
	 *	If multiplier is positive :
	 *	For each digit of the multiplier taken from left to right (current digit being i in [1,8])
	 *		while (digit > 0)
	 *			Add the multiplicand to the accm shifted i times
	 *			Decrement the digit
	 *
	 */
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
			while( currentDigit%10 != 0){
				transferUnit.transferComplement(sStore,accum,i-1);
				currentDigit++;
				rStore->setStoreValueIn(i,currentDigit);
			}
			transferUnit.transfer(sStore,accum,i-1);
		}
		return true;
	}
	return false;

}



