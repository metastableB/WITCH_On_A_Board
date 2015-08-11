/*
 * inputvalidator.cpp
 *
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 08-Aug-2015
 *
 */


#include "inputvalidator.h"

ValidatorStatus InputValidator::validateInput(std::string order){
	if(order.length() != 6 || order.length() != 9)
			return ValidatorStatus::INVALID_INPUT;
	else if(order.length() == 6)
		return validateOrder(order);
	else
		return validateNumber(order);
}


ValidatorStatus InputValidator::validateOrder(std::string order){
	int digits[5];
	for(int i = 1; i < 6 ; i++){
		if(!std::isdigit(order[i])){
			logObj.log(LogLevel::L_WARNING,"witch.cpp","ORDER is invalid\n");
			return ValidatorStatus::INVALID_INPUT;
		}
		digits[i] = std::stoi(std::string(&order[i],1));
	}

	switch(digits[0]){
	case 0:
		return ValidatorStatus::UNDEFINED_ORDER;
	case 1: /*
			 * Addition orders
			 * for regular additions, sending store and receiving store
			 * be in same set of ten stores. For addition operations with
			 * sending store having first digit as a zero, exceptions apply.
			 */
		if(digits[1] != 0 && (digits[1] == digits[3]))
			return validatorErrorHandler(ValidatorErrors::STORES_IN_SAME_SET);
		// TODO :
		else if(digits[1] == 0)
			return ValidatorStatus::UNDEFINED_ORDER;
		break;
	case 2:
	/*
	 * Addition with clear
	 * for regular additions, sending store and receiving store
	 * be in same set of ten stores. For addition operations with
	 * sending store having first digit as a zero, exceptions apply.
	 */
	default :
		return ValidatorStatus::UNDEFINED_ORDER;
	}
	logObj.log(LogLevel::L_INFO,"witch.cpp","ORDER is valid\n");
	return ValidatorStatus::VALID_ORDER;
}


ValidatorStatus InputValidator::validatorErrorHandler(ValidatorErrors error){
	switch(error){
	case ValidatorErrors::STORES_IN_SAME_SET:
		printErrorMsg("The sending store and receiving store cannot be "
				"from the same set of ten stores\n");
		return ValidatorStatus::INVALID_ORDER;
	}
	logObj.log(LogLevel::L_WARNING,"ordervalidator.cpp","An unhandled error has occurred!\n");
	return ValidatorStatus::UNDEFINED_ORDER;
}

void InputValidator::printErrorMsg(std::string s){
	if(!errorHandlerEnabled)
		return ;
	msg.print(MsgLevel::M_ERROR, s);
}

void InputValidator::enableErrorHandler(){
	this->errorHandlerEnabled = true;
}

void InputValidator::disableErrorHandler(){
	this->errorHandlerEnabled = false;
}

