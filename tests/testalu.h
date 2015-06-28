/*
 * testalu.h
 *
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 27-Jun-2015
 * 
 */

#ifndef TESTALU_H
#define TESTALU_H

#include "../src/alu.h"
#include "../src/dekatron.h"
#include "../src/accumulator.h"
#include "../src/dekatron.h"

class TestALU {
	ALU alu;
public:
	int failedTests = 0;
	TestALU();
};

#endif /* TESTALU_H */

