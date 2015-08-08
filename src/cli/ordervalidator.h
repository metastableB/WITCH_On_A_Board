/*
 * ordervalidator.h
 *
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 08-Aug-2015
 *
 */

/*
 * The order validator.
 *
 * This class has the task of validating all orders sent to WITCH, at the same time
 * it also has to let through all orders whose validity can be detected by the inbuilt
 * WITCH mechanisms
 */

#ifndef ORDERVALIDATOR_H
#define ORDERVALIDATOR_H

#include <string>

#include "../lib/logger.h"
#include "../lib/msgprinter.h"


	/* The below three are to be sent to the caller function. This defines the general
     * three types of error which can occur in an order.
     *
     * The next set of enums are for specific error types. They are
     * never to be returned. They are for the information of user and is to be
     * dealt with using the validatorErrorHandler() fucntion.
     */
enum ValidatorStatus{
	VALID_ORDER,
	INVALID_ORDER,
	UNDEFINED_ORDER
};

enum ValidatorErrors{
	STORES_IN_SAME_SET, // The store arguments belong to the same set of ten stores
};

class OrderValidator{
	Logger logObj;
	MsgPrinter msg;
	bool errorHandlerEnabled = true;

	void printErrorMsg(std::string s);
	ValidatorStatus validatorErrorHandler(ValidatorErrors errors);
public:
	// To toggle error message printing
	void disableErrorHandler();
	void enableErrorHandler();

	ValidatorStatus validateOrder(std::string s);
};

#endif // ORDERVALIDATOR_H


