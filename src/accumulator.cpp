/*
 * accumulator.cpp
 *
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 26-Jun-2015
 * 
 */
#include "accumulator.h"

void Accumulator::pulseAccumulator(int arr[]) {
	Dekatron newState_t[9];
	int temparr[9];
	accumulatorA.pulseStore(arr,newState_t);

	for(int i = 1; i < 9; i++)
		temparr[i] = arr[i+8];
	temparr[0] = arr[0];
	accumulatorB.pulseStore(temparr,newState_t);
}

void Accumulator::pulseAccumulator(int arr[], Dekatron* newState) {
	Dekatron newState_t[9];
	int temparr[9];
	accumulatorA.pulseStore(arr,newState_t);

	for(int i = 1; i < 9; i++)
		temparr[i] = arr[i+8];
	temparr[0] = arr[0];
	accumulatorB.pulseStore(temparr,newState_t);
	for(int i = 0; i < 16; i++){
		newState[i].setDekatronState(this->getStateIn(i));
	}
}



void Accumulator::setAccumulatorValue(int arr[]){
	this->accumulatorA.setStoreValueIn(0,arr[0]);
	this->accumulatorB.setStoreValueIn(0,arr[0]);
	for(int i = 1; i <= 15; i++ ){
		if(i < 9)
			this->accumulatorA.setStoreValueIn(i, arr[i]);
		else
			this->accumulatorB.setStoreValueIn(i - 8, arr[i]);
	}
}
int Accumulator::setAccumulatorValue(std::string value){
	if(value.size() != 16)
		return 1;

	int temp = 0,i = 0;
	temp = value[i] - '0';
	if(temp >= 0 && temp <= 9){
		this->accumulatorA.setStoreValueIn(0,temp);
		this->accumulatorB.setStoreValueIn(0,temp);
	}
	else return 1;
	i++;
	for(; i < 16; i++){
		temp = value[i] - '0';
		if(temp >= 0 && temp <= 9){
			if(i < 9)
				this->accumulatorA.setStoreValueIn(i, temp);
			else
				this->accumulatorB.setStoreValueIn(i - 8, temp);
		}
		else return 1;
	}
	return 0;
}
void Accumulator::setAccumulatorValueIn(int index, int value){
	if(index == 0)
		this->accumulatorB.setStoreValueIn(index,value);
	if(index < 9)
		this->accumulatorA.setStoreValueIn(index,value);
	else
		this->accumulatorB.setStoreValueIn(index - 8,value);
}

void Accumulator::setAccumulatorSign(int sign) {
	this->accumulatorA.setStoreValueIn(0,sign);
	this->accumulatorB.setStoreValueIn(0,sign);
}

std::string Accumulator::getStringStateInStore(){
	std::string state;
	for(int i = 0; i < 9; i++)
		state.append(std::to_string(int(this->accumulatorA.getStateIn(i))));
	for(int i = 1; i < 8; i++)
		state.append(std::to_string(int(this->accumulatorB.getStateIn(i))));
	return state;

}
DekatronState Accumulator::getStateIn(int index){
	if(index < 9)
		return this->accumulatorA.getStateIn(index);
	else
		return this->accumulatorB.getStateIn(index-8);
}

int Accumulator::getAccumulatorSign() {
	return int(accumulatorA.getStateIn(0));
}

void Accumulator::clearAccumulator(){
	for(int i = 0; i < 16 ; i++)
		this->setAccumulatorValue("0000000000000000");
}


