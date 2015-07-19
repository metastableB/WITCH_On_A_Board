/*
 * testshiftcircuit.h
 *
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 13-Jun-2015
 * 
 */
#ifndef TESTSHIFTCIRCUIT_H
#define TESTSHIFTCIRCUIT_H

#include "../src/shiftcircuit.h"
#include "../src/dekatronstore.h"
#include "../src/dekatron.h"
#include "../src/transferunit.h"
#include "../src/accumulator.h"
#include "../src/lib/logger.h"

class TestShiftCircuit {
	std::string getHumanReadableOutput(std::string inp, int size);
	Logger logObj;
public:
	int failedTests = 0;
	TestShiftCircuit();

};
#endif /*TESTSHIFTCIRCUIT_H*/



