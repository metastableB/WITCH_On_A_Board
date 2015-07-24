/*
 * witch.cpp
 *
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 20-Jul-2015
 * 
 */

#include "witch.h"

WitchStatus WITCH::translateAndStore(std::string index, std::string value){
	WitchStatus status = getStore(index, tempStore);
	if(status != WitchStatus::OPERATION_SUCCESSFUL){
		return status;
	}

	std::string str_val;
	status = validateStoreValue_H(value);
	if(status != WitchStatus::VALID_VALUE_H){
		return status;
	}
	if(translator.storeValue(value,tempStore))
		return WitchStatus::OPERATION_SUCCESSFUL;
	else
		return WitchStatus::OPERATION_FAILURE;
}

WitchStatus WITCH::translateAndLoad(std::string index, std::string& value){
	WitchStatus status = getStore(index, tempStore);
	if(status != WitchStatus::OPERATION_SUCCESSFUL)
		return status;
	value = translator.loadValue(tempStore);
	return WitchStatus::OPERATION_SUCCESSFUL;
}
WitchStatus WITCH::rawLoad(std::string index, std::string& value){
	WitchStatus status = getStore(index, tempStore);
	if(status != WitchStatus::OPERATION_SUCCESSFUL)
		return status;
	value = tempStore->getStringStateInStore();
	return WitchStatus::OPERATION_SUCCESSFUL;
}

WitchStatus WITCH::setCurrentOrder(std::string order){
	WitchStatus status = validateOrder(order);
	if(status != WitchStatus::VALID_WITCH_ORDER)
		return status;
	order = "+" + order + "000";

	if(translator.storeValue(order,&currentOrder)){
		orderStatus = SET_ORDER;
		return WitchStatus::OPERATION_SUCCESSFUL;
	}
	return WitchStatus::OPERATION_FAILURE;
}
WitchStatus WITCH::executeCurrentOrder(){
	if(orderStatus == WitchStatus::NOT_SET_ORDER)
		return orderStatus;
	if(currentOrder.getIntValueIn(1) != 0)
		return executeArithmeticOrder();
	else if(currentOrder.getIntValueIn(1) == 0)
		return executeNonArithmeticOrder();
	logObj.log(LogLevel::L_ERROR,"witch.cpp","UNKNOWN ERROR : Unrecognized order got past validator\n");
	return WitchStatus::OPERATION_FAILURE;
}

WitchStatus WITCH::executeArithmeticOrder(){
	// order is stored, has 5 digits.digit_0 is 0 (+), digit_1 is 1
	int digits[6];
	std::string sStore_str, rStore_str;
	for(int i = 0; i < 6; i++)
		digits[i] = currentOrder.getIntValueIn(i);
	sStore_str = std::to_string(digits[2]) + std::to_string(digits[3]);
	rStore_str = std::to_string(digits[4]) + std::to_string(digits[5]);
	DekatronStore *sStore,*rStore;
	WitchStatus status1,status2;
	status1 = getStore(sStore_str,sStore);
	status2 = getStore(rStore_str,rStore);
	if(status1 != WitchStatus::OPERATION_SUCCESSFUL)
		return status1;
	if(status2 != WitchStatus::OPERATION_SUCCESSFUL)
		return status2;

	switch(digits[1]){
	case 1: // Add without clear
		alu.add(sStore,rStore);
		break;
	case 2: // Add without clear
		alu.addAndClear(sStore,rStore);
		break;
	case 3: // subtract without clear
		alu.subtract(sStore,rStore);
		break;
	case 4: // subtract without clear
		alu.subtractAndClear(sStore,rStore);
		break;
	case 5: // Multiply
		alu.multiply(sStore,rStore,&accum);
		break;
	default :
		return WitchStatus::OPERATION_NOT_DEFINED;
	}
	return WitchStatus::OPERATION_SUCCESSFUL;
}
WitchStatus WITCH::executeNonArithmeticOrder(){
	return WitchStatus::OPERATION_NOT_DEFINED;
}

WitchStatus WITCH::getStore(std::string index, DekatronStore*& store) {
	WitchStatus status = validateStoreIndex(index);
	if(status != WitchStatus::VALID_INDEX){
		return status;
	} else{
		int row,col;
		if(!getDigitAt(index,0,row) || !getDigitAt(index,1,col))
			logObj.log(LogLevel::L_ERROR,"witch.cpp","Unknown error :getStore() "
					"got an invalid index!\n");
		store = &(dekatronArray[row][col]);
	}
	return WitchStatus::OPERATION_SUCCESSFUL;
}

WitchStatus WITCH::validateStoreIndex(std::string index){
	int row,col;
	if(index.length() != 2){
		logObj.log(LogLevel::L_WARNING,"witch.cpp","Incorrect index length.\n");
		return WitchStatus::INVALID_STORE_INDEX;
	} else {
		if(!getDigitAt(index,0, row) ||
				!getDigitAt(index,1,col)){
			logObj.log(LogLevel::L_WARNING,"witch.cpp", "Incorrect index\n");
			return WitchStatus::INVALID_STORE_INDEX;
		}
		if(row < 1 || row >= NO_OF_STORE_ROW || col < 0 || col >= NO_OF_STORE_COL) {
			logObj.log(LogLevel::L_WARNING,"witch.cpp", "Cannot access store.\nMake "
					"sure index obeys NO_OF_STORE_ROW and NO_OF_STORE_COL "
					"defined in " DIR_DEFINITIONS "\n");
			return WitchStatus::INVALID_STORE_ACCESS;
		}
	}
	return WitchStatus::VALID_INDEX;
}

WitchStatus WITCH::validateStoreValue_H(std::string value){
	std::string errMsg1 = "Invalid Value.\nValue "
			"should either be a 8 digit number with a "
			"leading + or - sign, or a 5 digit number with "
			"leading *.\n ";
	if(value.length() != 9 && value.length() != 6){
		logObj.log(LogLevel::L_WARNING,"witch.cpp", "VALUE length not correct.\n" );
		return WitchStatus::INVALID_STORE_VALUE_H;
	} else if(value.length() == 9){
		if(value[0] == '+'){
			// +ve 8 digit
			int i = 1,j;
			while(i < 9){
				if(!getDigitAt(value,i,j)){
					logObj.log(LogLevel::L_WARNING,"witch.cpp",errMsg1);
					return WitchStatus::INVALID_STORE_VALUE_H;
				}
				i++;
			}
		} else if(value[0] == '-'){
			// +ve 8 digit
			int i = 1,j;
			while(i < 9){
				if(!getDigitAt(value,i,j)){
					logObj.log(LogLevel::L_WARNING,"witch.cpp", errMsg1);
					return WitchStatus::INVALID_STORE_VALUE_H;
				}
				i++;
			}
		} else {
			logObj.log(LogLevel::L_WARNING,"witch.cpp", "Incorrect VALUE\n");
			return WitchStatus::INVALID_STORE_VALUE_H;
		}
	} else{
		// * and 5 digits
		if(value[0] != '*') {
			logObj.log(LogLevel::L_WARNING,"witch.cpp","Incorrect VALUE\n");
			return WitchStatus::INVALID_STORE_VALUE_H;
		}
		int i = 1,j;
		while(i <= 5){
			if(!getDigitAt(value,i,j)){
				logObj.log(LogLevel::L_WARNING,"witch.cpp", errMsg1);
				return WitchStatus::INVALID_STORE_VALUE_H;
			}
			i++;
		}
	}
	return WitchStatus::VALID_VALUE_H;
}
WitchStatus WITCH::validateStoreValue_R(std::string value){
	return WitchStatus::OPERATION_NOT_DEFINED;
}
WitchStatus WITCH::validateOrder(std::string order){
	if(order.length() != 5)
		return INVALID_WITCH_ORDER;
	int digits[5];
	for(int i = 0; i < 5 ; i++){
		if(!getDigitAt(order,i,digits[i])){
			logObj.log(LogLevel::L_WARNING,"witch.cpp","ORDER is invalid\n");
			return INVALID_WITCH_ORDER;
		}
	}
	logObj.log(LogLevel::L_INFO,"witch.cpp","ORDER is valid\n");
	return VALID_WITCH_ORDER;
}
bool WITCH::getDigitAt(std::string s,int index, int& num){
	num = s.at(index) - '0';
	// Distinguish between digits and other characters
	return (num >= 0 && num <= 9);
}

