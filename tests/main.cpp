/*
 * dekatronStore.cpp
 *
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 28-May-2015
 *
 */
#include <iostream>
#include <string>
#include "testdekatron.h"
#include "testdekatronstore.h"
#include "testtransferunit.h"
#include "testshiftcircuit.h"
#include "testaccumulator.h"
int main(int argc , char *argv[]) {
	std::string report;
#ifdef TEST_DEKATRON
	TestDekatron dekatron;
	report += "\ndekatron.cpp       Failures = " + std::to_string(dekatron.failedTests);
#endif /*TEST_DEKATRON*/
#ifdef TEST_DEKATRONSTORE
	TestDekatronStore store;
	report += "\ndekatronstore.cpp  Failures = " + std::to_string(store.failedTests);
#endif /*TEST_DEKATRONSTORE*/
#ifdef TEST_TRANSFERUNIT
	TestTransferUnit transferUnit;
	report += "\ntransferunit.cpp   Failures = " + std::to_string(transferUnit.failedTests);
#endif /*TEST_TRANSFERUNIT*/
#ifdef TEST_SHIFTCIRCUIT
	TestShiftCircuit shiftCircuit;
	report += "\nshiftcircuit.cpp   Failures = " + std::to_string(shiftCircuit.failedTests);
#endif /*TEST_SHIFTCIRCUIT*/
#ifdef TEST_ACCUMULATOR
	TestAccumulator testAccumulator;
	report += "\naccumulator.cpp    Failures = " + std::to_string(testAccumulator.failedTests);
#endif /*TEST_ACCUMULATOR*/
	std::cout << "\n:::END TEST:::\n" << report <<"\n\n";
}
