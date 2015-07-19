/*
 * msgprinter.cpp
 *
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 20-Jul-2015
 * 
 */

#include "msgprinter.h"

void MsgPrinter::print(MsgLevel level, std::string msg) {
	switch(level) {
	case MsgLevel::DEBUG :
		std::cout << "[DEBUG]: "<< msg;
		break;
	case MsgLevel::INFO :
		std::cout << "[INFO]: "<< msg;
		break;
	case MsgLevel::WARNING :
		std::cout << "[WARNING]: "<< msg;
		break;
	case MsgLevel::ERROR :
		std::cout << "[ERROR]: "<< msg;
		break;
	case MsgLevel::MSG :
		std::cout << msg;
		break;
	}
}

