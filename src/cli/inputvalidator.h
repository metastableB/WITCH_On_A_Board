/*
 * inputvalidator.h
 *
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 08-Aug-2015
 *
 */

/*
 * The input validator.
 *
 * This class has the task of validating all inputs sent to WITCH, at the same time
 * it also has to let through all orders whose validity can be detected by the inbuilt
 * WITCH mechanisms
 */

#ifndef ORDERVALIDATOR_H
#define ORDERVALIDATOR_H

#include <string>

#include "../lib/logger.h"
#include "../lib/msgprinter.h"

/*
 * WARNING: This class is only used for validating the orders exclusively. Numbers are not
 * extensively checked for and that task is left for the translator unit. The purpose here
 * is to filter out any undefined order and the class should be used with this in mind.
 *
 * This also means that any numbers of length 5 digits might get trapped here if used like so. Make
 * sure such numbers are appended with '0's or '9s' when the case arises.
 *
 *
 */
/* The below three are to be sent to the caller function. This defines the general
 * three types of error which can occur in an order.
 *
 * The next set of enums are for specific error types. They are
 * never to be returned. They are for the information of user and is to be
 * dealt with using the validatorErrorHandler() function.
 *
 * Since we have an independent driver and a validator, we have to keep a redundant copy
 * of the error types. A general set of errors within the driver and an extensive set here.
 */

/*
 * NOTE: The validateOrder method validates the order according to a strict rules
 * regarding the argument set etc. To input a number as an order, (i.e. of order length). You need
 * to explicitly make sure its length i 9.
 */
enum ValidatorStatus{
	VALID_ORDER,
	UNDEFINED_ORDER,

	VALID_NUMBER,

	INVALID_INPUT,
};

enum ValidatorErrors{
	STORES_IN_SAME_SET, // The store arguments belong to the same set of ten stores
};

class InputValidator{
	Logger logObj;
	MsgPrinter msg;
	bool errorHandlerEnabled = true;

	void printErrorMsg(std::string s);
	ValidatorStatus validatorErrorHandler(ValidatorErrors errors);
	ValidatorStatus validateOrder(std::string order);
	ValidatorStatus validateNumber(std::string number);
public:
	// To toggle error message printing
	void disableErrorHandler();
	void enableErrorHandler();

	ValidatorStatus validateInput(std::string s);
};

#endif // ORDERVALIDATOR_H


