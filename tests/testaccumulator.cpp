/*
 * testaccumulator.cpp
 *
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 26-Jun-2015
 * 
 */

#include "testaccumulator.h"
/*
 * void pulseAccumulator(int arr[]);
	void setAccumulatorValue(int arr[]);
	int setAccumulatorValue(std::string value);
	void setAccumulatorValueIn(int index, int value);
	std::string getStringStateInStore();
	DekatronState getStateIn(int index);
 */

TestAccumulator::TestAccumulator() {
	std::cout << "Testing accumulator.cpp\n";
	if(!accum.getStringStateInStore().compare("0000000000000000"))
		std::cout << "Accumulator TEST 1 SUCCESSFUL\n";
	else {
		failedTests++;
		std::cout << "Accumulator TEST 1 initialization FAILURE "<< accum.getStringStateInStore()<<"\n";
	}
	int arr[16] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	accum.pulseAccumulator(arr);
	accum.pulseAccumulator(arr);
	accum.pulseAccumulator(arr);
	if(!accum.getStringStateInStore().compare("3333333333333333"))
		std::cout << "Accumulator TEST 2 SUCCESSFUL\n";
	else {
		failedTests++;
		std::cout << "Accumulator TEST 2 pulseAccumulator() FAILURE "<< accum.getStringStateInStore()<<"\n";
	}

	arr[0] = 0;
	arr[5] = 5;
	arr[7] = 7;
	arr[8] = 8;
	arr[9] = 9;
	arr[10] = 1;
	arr[14] = 5;
	arr[15] = 6;
	accum.setAccumulatorValue(arr);
	if(!accum.getStringStateInStore().compare("0111151789111156"))
		std::cout << "Accumulator TEST 3 SUCCESSFUL\n";
	else {
		failedTests++;
		std::cout << "Accumulator TEST 3 setAccumulatorValue() FAILURE "<< accum.getStringStateInStore()<<"\n";
	}

	accum.setAccumulatorValue("9876543210123456");
	if(!accum.getStringStateInStore().compare("9876543210123456"))
		std::cout << "Accumulator TEST 4 SUCCESSFUL\n";
	else {
		failedTests++;
		std::cout << "Accumulator TEST 4 setAccumulatorValue() FAILURE "<< accum.getStringStateInStore()<<"\n";
	}

	accum.setAccumulatorValueIn(0,0);
	accum.setAccumulatorValueIn(1,1);
	accum.setAccumulatorValueIn(8,8);
	accum.setAccumulatorValueIn(9,9);
	accum.setAccumulatorValueIn(15,5);
	if(!accum.getStringStateInStore().compare("0176543289123455"))
		std::cout << "Accumulator TEST 5 SUCCESSFUL\n";
	else {
		failedTests++;
		std::cout << "Accumulator TEST 5 setAccumulatorValueIn() FAILURE " << accum.getStringStateInStore()<<"\n";
	}
	bool state = true;
	state = state && (accum.getStateIn(0) == DekatronState::ZERO);
	state = state && (accum.getStateIn(8) == DekatronState::EIGHT);
	state = state && (accum.getStateIn(9) == DekatronState::NINE);
	state = state && (accum.getStateIn(10) == DekatronState::ONE);
	state = state && (accum.getStateIn(14) == DekatronState::FIVE);
	state = state && (accum.getStateIn(15) == DekatronState::FIVE);

	if(state)
		std::cout << "Accumulator TEST 6 SUCCESSFUL\n";
	else {
		failedTests++;
		std::cout << "Accumulator TEST 6 getStateIn FAILURE " << accum.getStringStateInStore()<<"\n";
	}
	std::cout << "FINISH accumulator.cpp TESTS\n";
}



