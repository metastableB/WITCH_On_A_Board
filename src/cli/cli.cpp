/*
 * cli.cpp
 *
 * This file handles the command line interace for the WITCH simulator
 * This class will act as the driver class , acting between the user
 * and the WITCH object
 *
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 20-Jul-2015
 * 
 */

#include "driver.h"
#include "../lib/logger.h"

#include <string>
#include <iostream>


int main(int argc, char* argv[]) {
	Logger logObj;
	logObj.log(LogLevel::L_INFO, "cli.cpp","Starting WITCH simulator\n");
	Driver driver;
	int i = driver.runSim(argc,argv);
	logObj.log(LogLevel::L_INFO, "cli.cpp","Done\n");
	return !(i == DriverStatus::QUIT_SUCCESS);
}

