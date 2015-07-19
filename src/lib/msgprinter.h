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

enum MsgLevel { INFO, DEBUG, WARNING, ERROR, MSG};

class MsgPrinter {

public:
	void print(MsgLevel level,std::string msg);
};

#endif /*MSGPRINTER_H*/


