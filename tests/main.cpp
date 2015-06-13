/*
 * dekatronStore.cpp
 *
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 28-May-2015
 *
 */
#include <iostream>
#include "testdekatron.h"
#include "testdekatronstore.h"
#include "testtransferunit.h"
#include  "testshiftcircuit.h"
int main(int argc , char *argv[]) {
#ifdef TEST_DEKATRON
	TestDekatron dekatron;
#endif /*TEST_DEKATRON*/
#ifdef TEST_DEKATRONSTORE
	TestDekatronStore store;
#endif /*TEST_DEKATRONSTORE*/
#ifdef TEST_TRANSFERUNIT
	TestTransferUnit transferUnit;
#endif /*TEST_TRANSFERUNIT*/
#ifdef TEST_SHIFTCIRCUIT
	TestShiftCircuit testShiftCircuit;
#endif /*TEST_SHIFTCIRCUIT*/
	std::cout << "\n:::END TEST:::\n";
}
