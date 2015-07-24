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
#include <vector>
#include <iterator>
#include <sstream>
#include <unordered_map>
#include <stdexcept>

enum WitchState {
	PRGM_LOADED, // MODE 1
	PRGM_UNLOADED, // MODE 2
	PRGM_RUNNING
};
enum DriverStatus {
	QUIT_SUCCESS,
	QUIT_FAILURE,
	INVALID_CL_ARGUMENT, // CLA is diff from runtime commands
	COMMAND_EMPTY,
	COMMAND_UNKNOWN,
	COMMAND_SUCCESS,
	COMMAND_ARGUMENT_ERROR,
	UNKNOWN_ERROR,
	SUCCESS,
};

class Driver {
	WITCH witch;
	DekatronStore* tempStore1;
	Dekatron tempDekatronArr[9];

	Logger logObj;
	MsgPrinter msg;
	WitchState witchState = WitchState::PRGM_UNLOADED;

	bool commandLineArgs(int argc, char * argv[]);
	void printPrompt();
	void getUserInput(std::vector<std::string>& tokens);
	int execute(std::vector<std::string>& inp);
	/*
	 * Parsing and validation functions
	 */
	bool getDigitAt(std::string s,int index, int& num);
	bool getStoreValue(std::string s, int num[]);
	DriverStatus witchErrorHandler(WitchStatus status);

	/*
	 * Command functions
	 * Add appropriate help topics to c_help(vector<string>&)
	 * when new commands are added.
	 */

	DriverStatus c_quit(std::vector<std::string>& tokens);
	DriverStatus c_help(std::vector<std::string>& tokens);
	DriverStatus c_inp(std::vector<std::string>& tokens);
	DriverStatus c_set(std::vector<std::string>& tokens);
	DriverStatus c_print(std::vector<std::string>& tokens);
	DriverStatus c_order(std::vector<std::string>& tokens);
public :
	int runSim(int argc, char* argv[]);
};
#endif /*DRIVER_H*/




