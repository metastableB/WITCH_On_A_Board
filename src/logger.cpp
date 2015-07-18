/*
 * logger.cpp
 *
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 18-Jul-2015
 * 
 */

#include "logger.h"

void Logger::log(std::string msg, LogLevel level) {
	switch(level) {
	case LogLevel::DEBUG :
		std::cerr << "[DEBUG] : " << msg;
		break;
	case LogLevel::INFO :
		std::cerr << "[INFO] : " << msg;
		break;
	case LogLevel::WARNING :
		std::cerr << "[WARNING] : " << msg;
	}
}

