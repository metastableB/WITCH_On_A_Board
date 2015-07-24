/*
 * logger.h
 *
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 18-Jul-2015
 *
 * Implementing a logging interface to print to stderr.
 */

#ifndef LOGGER_H
#define LOGGER_H


#include <string>
#include <iostream>

enum LogLevel { L_INFO, L_DEBUG, L_WARNING, L_ERROR};
class Logger {

public:
	void log(LogLevel level,std::string origin,std::string msg);
};

#endif /*LOGGER_H*/


