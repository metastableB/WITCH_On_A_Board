/*
 * logger.cpp
 *
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 18-Jul-2015
 * 
 */

#include "logger.h"

void Logger::log(LogLevel level, std::string origin,std::string msg) {
	switch(level) {
	case LogLevel::L_DEBUG :
		std::cerr << "[DEBUG]  " << origin << ": "<< msg;
		break;
	case LogLevel::L_INFO :
		std::cerr << "[INFO]   " << origin << ": "<< msg;
		break;
	case LogLevel::L_WARNING :
		std::cerr << "[WARNING]" << origin <<": "<< msg;
		break;
	case LogLevel::L_ERROR :
		std::cerr << "[ERROR] " << origin << ": "<< msg;
		break;
	}
}

