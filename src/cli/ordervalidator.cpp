/*
 * ordervalidator.cpp
 *
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 08-Aug-2015
 *
 */


#include "ordervalidator.h"

ValidatorStatus OrderValidator::validateOrder(std::string order){
	if(order.length() != 5)
			return ValidatorStatus::INVALID_ORDER;
		int digits[5];
		for(int i = 0; i < 5 ; i++){
			if(!std::isdigit(order[i])){
				logObj.log(LogLevel::L_WARNING,"witch.cpp","ORDER is invalid\n");
				return ValidatorStatus::INVALID_ORDER;
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
			return ValidatorStatus::VALID_ORDER;
		case 2: /*
		 * Addition orders
		 * for regular additions, sending store and receiving store
		 * be in same set of ten stores. For addition operations with
		 * sending store having first digit as a zero, exceptions apply.
		 */break;
		default :
			return ValidatorStatus::UNDEFINED_ORDER;
		}
		logObj.log(LogLevel::L_INFO,"witch.cpp","ORDER is valid\n");

	return ValidatorStatus::INVALID_ORDER;
}


ValidatorStatus OrderValidator::validatorErrorHandler(ValidatorErrors error){
	switch(error){
	case ValidatorErrors::STORES_IN_SAME_SET:
		printErrorMsg("The sending store and receiving store cannot be "
				"from the same set of ten stores\n");
		return ValidatorStatus::INVALID_ORDER;
	}
	logObj.log(LogLevel::L_WARNING,"ordervalidator.cpp","An unhandled error has occurred!\n");
	return ValidatorStatus::UNDEFINED_ORDER;
}

void OrderValidator::printErrorMsg(std::string s){
	if(!errorHandlerEnabled)
		return ;
	msg.print(MsgLevel::M_ERROR, s);
}

void OrderValidator::enableErrorHandler(){
	this->errorHandlerEnabled = true;
}

void OrderValidator::disableErrorHandler(){
	this->errorHandlerEnabled = false;
}

