/*
 * ordervalidater.h
 *
 *  Created on: 08-Aug-2015
 *      Author: metastableB
 */

/*
 * The order validater.
 *
 * This class has the task of validating all orders sent to WITCH, at the same time
 * it also has to let through all orders whose validity can be detected by the inbuilt
 * WITCH mechanisms
 */

#ifndef ORDERVALIDATER_H
#define ORDERVALIDATER_H

#include <string>

#include "../lib/logger.h"
#include "../lib/msgprinter.h"

enum ValidaterStatus{
	VALID_ORDER,
	INVALID_ORDER,
	UNDEFINED_ORDER
};
class OrderValidater{
	Logger logObj;
	MsgPrinter msg;

public:
	ValidaterStatus validateOrder(std::string s);
};

#endif // ORDERVALIDATOR_H


