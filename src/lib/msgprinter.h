/*
 * msgprinter.h
 *
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 20-Jul-2015
 *
 */

#ifndef MSGPRINTER_H
#define MSGPRINTER_H

#include <string>
#include <iostream>

enum MsgLevel { M_INFO, M_DEBUG, M_WARNING, M_ERROR, M_MSG};

class MsgPrinter {

public:
	void print(MsgLevel level,std::string msg);
};

#endif /*MSGPRINTER_H*/


