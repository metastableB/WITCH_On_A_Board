/*
 * testdekatronstore.h
 *
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 29-May-2015
 * 
 */
#ifndef TESTDEKATRONSTORE_H
#define TESTDEKATRONSTORE_H

#include <iostream>
#include "../src/dekatronstore.h"
#include "../src/lib/logger.h"
class TestDekatronStore {
	Logger logObj;
public:
	int failedTests = 0;
	TestDekatronStore();
};
#endif /*TESTDEKATRONSTORE_H*/
