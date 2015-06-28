/*
 * testaccumulator.h
 *
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 26-Jun-2015
 * 
 */
#ifndef TESTACCUMULATOR_H
#define TESTACCUMULATOR_H

#include <iostream>
#include "../src/accumulator.h"

class TestAccumulator {
	Accumulator accum;
public:
	int failedTests = 0;
	TestAccumulator();
};
#endif /*TESTACCUMULATOR_H*/




