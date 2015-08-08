/*
 * ordervalidater.cpp
 *
 *  Created on: 08-Aug-2015
 *      Author: metastableB
 */

#include "ordervalidater.h"

ValidaterStatus OrderValidater::validateOrder(std::string order){
	if(order.length() != 5)
			return ValidaterStatus::INVALID_ORDER;
		int digits[5];
		for(int i = 0; i < 5 ; i++){
			if(!std::isdigit(order[i])){
				logObj.log(LogLevel::L_WARNING,"witch.cpp","ORDER is invalid\n");
				return ValidaterStatus::INVALID_ORDER;
			}
			digits[i] = std::stoi(std::string(digits[i]));
		}

		switch(digits[0]){
		case 0:
			return ValidaterStatus::UNDEFINED_ORDER;
		case 1: /*
				 * Addition orders
				 * for regular additions, sending store and receiving store
				 * be in same set of ten stores. For addition operations with
				 * sending store having first digit as a zero, exceptions apply.
				 */
			if(digits[1] != 0 && (digits[1] == digits[3]))
				return ValidaterStatus::INVALID_ORDER;
			// TODO :
			else if(digits[1] == 0)
				return ValidaterStatus::UNDEFINED_ORDER;
			return ValidaterStatus::VALID_ORDER;
		case 2: /*
		 * Addition orders
		 * for regular additions, sending store and receiving store
		 * be in same set of ten stores. For addition operations with
		 * sending store having first digit as a zero, exceptions apply.
		 */

		}
		logObj.log(LogLevel::L_INFO,"witch.cpp","ORDER is valid\n");

	return ValidaterStatus::INVALID_ORDER;
}




