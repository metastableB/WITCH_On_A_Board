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
	// 5 : direct order. 6 : *(order/number) , 9 : Number
	if(order.length() != 6 && order.length() != 9 && order.length() != 5){
		logObj.log(LogLevel::L_DEBUG,"validateInput","Invalid input length"+std::to_string(order.length())+"\n");
		return ValidatorStatus::INVALID_INPUT;
	}
	else if(order.length() == 6 || order.length() == 5)
		return validateOrder(order);
	else
		return validateNumber(order);
}


ValidatorStatus InputValidator::validateOrder(std::string order){
	int digits[5];
	if(order.length() == 5)
		order = "*" + order;
	logObj.log(LogLevel::L_INFO,"inputvalidator.cpp","Order is \"" + order + "\"\n");
	if(order.at(0)!= '*')
		return ValidatorStatus::INVALID_INPUT;
	for(int i = 1; i < 6 ; i++){
		if(!std::isdigit(order[i])){
			logObj.log(LogLevel::L_WARNING,"witch.cpp","ORDER is invalid\n");
			return ValidatorStatus::INVALID_INPUT;
		}
		digits[i-1] = std::stoi(std::string(&order[i],1));
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
		logObj.log(LogLevel::L_INFO,"inputvalidator.cpp","add\n");
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
		logObj.log(LogLevel::L_INFO,"inputvalidator.cpp","add and clear\n");
		logObj.log(LogLevel::L_WARNING,"inputvalidator.cpp","validator not implemented!\n");
		break;
	case 3:
		logObj.log(LogLevel::L_INFO,"inputvalidator.cpp","Subtract\n");
		logObj.log(LogLevel::L_WARNING,"inputvalidator.cpp","validator not implemented!\n");
		break;
	case 4:
		logObj.log(LogLevel::L_INFO,"inputvalidator.cpp","subtract and clear\n");
		logObj.log(LogLevel::L_WARNING,"inputvalidator.cpp","validator not implemented!\n");
		break;
	case 5:
		logObj.log(LogLevel::L_INFO,"inputvalidator.cpp","multiply\n");
		logObj.log(LogLevel::L_WARNING,"inputvalidator.cpp","validator not implemented!\n");
		break;
	case 7:
		logObj.log(LogLevel::L_INFO,"inputvalidator.cpp","Transfer modulus\n");
		logObj.log(LogLevel::L_WARNING,"inputvalidator.cpp","validator not implemented!\n");
		break;
	default :
		return ValidatorStatus::UNDEFINED_ORDER;
	}
	logObj.log(LogLevel::L_INFO,"inputvalidator.cpp","ORDER is valid\n");
	return ValidatorStatus::VALID_ORDER;
}

ValidatorStatus InputValidator::validateNumber(std::string number){
	// TODO : remember that some part or even the entirety of this function is done
	// by the translator unit. Once we have a better understanding of the translator unit
	// we will have to reassign responsibilities between the input validator and the
	// translator object.
	/*
	if(number[0] != '+' || number[0] != '-')
		return ValidatorStatus::INVALID_INPUT;
	for (int i = 1; i < 9; i++){
		if(!std::isdigit(number[i])){
			logObj.log(LogLevel::L_WARNING,"witch.cpp","NUMBER is invalid\n");
			return ValidatorStatus::INVALID_INPUT;
		}
	}*/
	return ValidatorStatus::VALID_NUMBER;
}
ValidatorStatus InputValidator::validatorErrorHandler(ValidatorErrors error){
	switch(error){
	case ValidatorErrors::STORES_IN_SAME_SET:
		printErrorMsg("The sending store and receiving store cannot be "
				"from the same set of ten stores\n");
		return ValidatorStatus::INVALID_INPUT;
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

