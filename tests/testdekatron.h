/*
 * testdekatron.h
 *
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 29-May-2015
 *
 */
#ifndef TESTDEKATRON_H
#define TESTDEKATRON_H

#include "../src/dekatron.h"
#include "../src/lib/logger.h"
#include <iostream>
 
class TestDekatron {
	Logger logObj;
public:
	int failedTests = 0;
	TestDekatron() ;
};
#endif /*TESTDEKATRON_H*/
