/*
 * driver.h
 *
 * The driver for the command line interface.
 * Input handling, parsing and also acts a PSEUDO Control unit for the WITCH
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 20-Jul-2015
 * 
 */

#ifndef DRIVER_H
#define DRIVER_H


#include "../dekatron.h"
#include "../dekatronstore.h"
#include "../transferunit.h"
#include "../shiftcircuit.h"
#include "../accumulator.h"
#include "../alu.h"
#include "../witch.h"

#include "../lib/logger.h"
#include "../lib/definitions.h"
#include "../lib/msgprinter.h"

#include <iostream>
#include <string>

enum WitchState {
	PRGM_LOADED, // MODE 1
	PRGM_UNLOADED, // MODE 2
	PRGM_RUNNING
};
enum DriverStatus {
	SUCCESS,
	INVALID_CL_ARGUMENT
};

class Driver {
	WITCH witch;

	Logger logObj;
	MsgPrinter msg;
	WitchState witchState = WitchState::PRGM_UNLOADED;

	bool commandLineArgs(int argc, char * argv[]);
	void printPrompt();
	int execute(std::string inp);
	std::string getUserInput();

public :
	Driver();
	int runSim(int argc, char* argv[]);
};
#endif /*DRIVER_H*/




