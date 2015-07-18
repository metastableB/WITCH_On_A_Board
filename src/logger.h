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

enum LogLevel { INFO, DEBUG, WARNING};
class Logger {

public:
	void log(std::string msg, LogLevel level);
};

#endif /*LOGGER_H*/


