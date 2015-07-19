/*
 * witch.cpp
 *
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 20-Jul-2015
 * 
 */

#include "witch.h"

DekatronStore* WITCH::getStore(std::string index) {
	if(index.length() != 2)
		logObj.log(LogLevel::WARNING,"witch.cpp","getStore() received an index string of undefined length.\n");
		// TODO: Remember to trim inputs of spaces and tabs
	int row,col;
	row = index.at(0) - '0';
	col = index.at(1) - '0';
	if(row < 1 || row > NO_OF_STORE_ROW || col < 0 || col > NO_OF_STORE_COL) {
		logObj.log(LogLevel::WARNING,"witch.cpp","getStore() received an index out of range\n");
		return NULL;
	} else
		return &(dekatronArray[row][col]);
	logObj.log(LogLevel::ERROR,"witch.cpp","getStore() unknown error\n");
	return NULL;
}



