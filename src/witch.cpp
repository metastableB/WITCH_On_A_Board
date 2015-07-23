/*
 * witch.cpp
 *
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 20-Jul-2015
 * 
 */

#include "witch.h"

WitchStatus WITCH::getStore(std::string index, DekatronStore* store) {
	WitchStatus status = validateStoreIndex(index);
	if(status != WitchStatus::VALID_INDEX){
		return status;
	} else{
		int row,col;
		if(!getDigitAt(index,0,row) || !getDigitAt(index,1,col))
			logObj.log(LogLevel::L_ERROR,"witch.cpp","Unknown error :getStore() "
					"got an invalid index!\n");
		store = &dekatronArray[row][col];
	}
	return WitchStatus::OPERATION_SUCCESSFUL;
}

WitchStatus WITCH::translateAndStore(std::string index, std::string value){
	int row, col;
	std::string str_val;
	if(value.length() != 9 && value.length() != 6){
		logObj.log(LogLevel::L_WARNING,"witch.cpp", "VALUE length not correct.\n");
		return WitchStatus::INVALID_STORE_VALUE_H;
	} else if(value.length() == 9){
		if(value[0] == '+'){
			// +ve 8 digit
			int i = 1,j;
			std::string num = "0";
			while(i < 9){
				if(!getDigitAt(value,i,j)){
					logObj.log(LogLevel::L_WARNING,"witch.cpp","Invalid Value.\nValue should either be a 8 digit "
							"number with a leading + or - sign, or a 5 digit number with "
							"leading *.\n");
					return WitchStatus::INVALID_STORE_VALUE_H;
				} else
					num += std::to_string(j);
				i++;
			}
			tempStore->setStoreValue(num,tempDekatronArr);
		} else if(value[0] == '-'){
			// +ve 8 digit
			int i = 1,j;
			std::string num = "9";
			while(i < 9){
				if(!getDigitAt(value,i,j)){
					logObj.log(LogLevel::L_WARNING,"witch.cpp", "Invalid Value.\nValue should either be a 8 digit "
							"number with a leading + or - sign, or a 5 digit number with "
							"leading *.\n");
					return WitchStatus::INVALID_STORE_VALUE_H;
				} else
					num += std::to_string(9 - j);
				i++;
			}
			tempStore->setStoreValue(num,tempDekatronArr);
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
		std::string num = "0";
		while(i <= 5){
			if(!getDigitAt(value,i,j)){
				logObj.log(LogLevel::L_WARNING,"witch.cpp", "Invalid Value.\nValue should either be a 8 digit "
						"number with a leading + or - sign, or a 5 digit number with "
						"leading *.\n");
				return WitchStatus::INVALID_STORE_VALUE_H;
			} else
				num += std::to_string(j);
			i++;
		}
		num += "000";
		tempStore->setStoreValue(num,tempDekatronArr);
	}
	return WitchStatus::OPERATION_SUCCESSFUL;
}

WitchStatus WITCH::translateAndLoad(std::string index, std::string& value){
	WitchStatus status = getStore(index, tempStore);
	if(status != WitchStatus::VALID_INDEX)
		return status;
	value = tempStore->getStringStateInStore();
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
		if(row < 1 || row > NO_OF_STORE_ROW || col < 0 || col > NO_OF_STORE_COL) {
			logObj.log(LogLevel::L_WARNING,"witch.cpp", "Cannot access store.\nMake sure index obeys NO_OF_STORE_ROW "
					"and NO_OF_STORE_COL defined in " DIR_DEFINITIONS "\n");
			return WitchStatus::INVALID_STORE_ACCESS;
		}
	}
	return WitchStatus::VALID_INDEX;
}

WitchStatus WITCH::validateStoreValue_H(std::string value){

}

bool WITCH::getDigitAt(std::string s,int index, int& num){
	num = s.at(index) - '0';
	logObj.log(LogLevel::L_DEBUG,"driver.cpp",std::to_string(num)+"\n");
	// Distinguish between digits and other characters
	return (num >= 0 && num <= 9);
}

