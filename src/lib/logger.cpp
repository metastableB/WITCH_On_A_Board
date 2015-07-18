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
	case LogLevel::DEBUG :
		std::cerr << "[DEBUG] : " << origin << " : "<< msg;
		break;
	case LogLevel::INFO :
		std::cerr << "[INFO] : " << origin << " : "<< msg;
		break;
	case LogLevel::WARNING :
		std::cerr << "[WARNING] : " << origin <<" : "<< msg;
		break;
	case LogLevel::ERROR :
		std::cerr << "[ERROR] : " << origin << " : "<< msg;
		break;
	}
}

