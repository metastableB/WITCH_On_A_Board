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
#include "testalu.h"

int main(int argc , char *argv[]) {
	std::string report;
	std::cout << "Starting tests, logging to stderr\n";
#ifdef TEST_DEKATRON
	TestDekatron dekatron;
	std::cout <<"\n";
	report += "\ndekatron.cpp       Failures = " + std::to_string(dekatron.failedTests);
#endif /*TEST_DEKATRON*/
#ifdef TEST_DEKATRONSTORE
	TestDekatronStore store;
	std::cout <<"\n";
	report += "\ndekatronstore.cpp  Failures = " + std::to_string(store.failedTests);
#endif /*TEST_DEKATRONSTORE*/
#ifdef TEST_TRANSFERUNIT
	TestTransferUnit transferUnit;
	std::cout <<"\n";
	report += "\ntransferunit.cpp   Failures = " + std::to_string(transferUnit.failedTests);
#endif /*TEST_TRANSFERUNIT*/
#ifdef TEST_SHIFTCIRCUIT
	TestShiftCircuit shiftCircuit;
	std::cout <<"\n";
	report += "\nshiftcircuit.cpp   Failures = " + std::to_string(shiftCircuit.failedTests);
#endif /*TEST_SHIFTCIRCUIT*/
#ifdef TEST_ACCUMULATOR
	TestAccumulator accumulator;
	std::cout <<"\n";
	report += "\naccumulator.cpp    Failures = " + std::to_string(accumulator.failedTests);
#endif /*TEST_ACCUMULATOR*/
#ifdef TEST_ALU 
	TestALU alu;
	std::cout <<"\n";
	report += "\nalu.cpp            Failures = " + std::to_string(alu.failedTests);
#endif /*TEST_ALU*/
	std::cout << "\nAll Tests Finished\n:::REPORT:::" << report <<"\n\n";
}
