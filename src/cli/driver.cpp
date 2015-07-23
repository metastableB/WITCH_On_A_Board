/*
 * driver.cpp
 *
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 20-Jul-2015
 * 
 */

#include "driver.h"


int Driver::runSim(int argc, char* argv[]){
	if(!commandLineArgs(argc,argv))
		return DriverStatus::INVALID_CL_ARGUMENT;
	std::vector<std::string> inCommand;
	while(true) {
		printPrompt();
		getUserInput(inCommand);
		switch(execute(inCommand)) {
		case DriverStatus::QUIT_SUCCESS :
			return DriverStatus::QUIT_SUCCESS;
		case DriverStatus::COMMAND_UNKNOWN :
			msg.print(MsgLevel::M_MSG, "Unknown Command. Please use 'help' for help\n");
			break;
		case DriverStatus::COMMAND_ARGUMENT_ERROR:
			msg.print(MsgLevel::M_MSG, "Please use 'help' for help\n");
			break;
		case DriverStatus::UNKNOWN_ERROR :
			msg.print(MsgLevel::M_MSG, "Unknown Error in execute\n");
			break;
		}
	}
	return 0;
}

int Driver::execute(std::vector<std::string>& tokens) {
	// TODO : Change to C++11 lamda later
	if(tokens.empty())
		return DriverStatus::COMMAND_EMPTY;
	else if(tokens[0] == "q" || tokens[0] == "quit")
		return c_quit(tokens);
	else if(tokens[0] == "help")
		return c_help(tokens);
	else if(tokens[0] == "inp")
		return c_inp(tokens);
	else if(tokens[0] == "set")
			return c_set(tokens);
	else {
		tokens.clear();
		logObj.log(LogLevel::L_INFO, "driver.cpp", "UNKNOWN COMMAND in execute()\n");
		return DriverStatus::COMMAND_UNKNOWN;
	}
	return DriverStatus::QUIT_FAILURE;
}
bool Driver::commandLineArgs(int argc, char** argv) {
	if(argc != 1) {
		logObj.log(LogLevel::L_ERROR, "driver.cpp", "Argument error\n");
		msg.print(MsgLevel::M_MSG, "Argument Error\n");
		return false;
	}
	return true;
}
void Driver::getUserInput(std::vector<std::string>& tokens){
	/*
	 * TODO : Allow shuffled order inputs and reorder them here to match remaining
	 * functions.
	 */
	tokens.clear();
	std::string line;
	if(!std::getline(std::cin,line))
		logObj.log(LogLevel::L_ERROR,"driver.cpp","UNKNOWN ERROR with user input\n");
	std::istringstream buffer(line);
	std::copy(std::istream_iterator<std::string>(buffer),
		  std::istream_iterator<std::string>(),
		  std::back_inserter(tokens));
#ifdef _DEBUG_
	if(!tokens.empty()) {
		std::string arg;
		for(std::vector<std::string>::iterator it = tokens.begin(); it != tokens.end(); ++it)
			arg += *it + "|";
		logObj.log(LogLevel::L_DEBUG,"driver.cpp","Received input :" + arg + "\n");
	} else
		logObj.log(LogLevel::L_DEBUG,"driver.cpp","Received input :EMPTY\n");

#endif /* _DEBUG_ */
}
void Driver::printPrompt(){
 	msg.print(MsgLevel::M_MSG, "WITCH-e$ ");
}


/*
 *  Command definitions
 */
DriverStatus Driver::c_help(std::vector<std::string>& tokens){
	if(tokens.size() != 1) {
		msg.print(MsgLevel::M_MSG, "Incorrect usage\n");
		return DriverStatus::COMMAND_ARGUMENT_ERROR;
	}
	std::string helpString = "The WITCH_On_A_Board Project\n"
				"-----------------------------\n"
				 "For detailed usage description of each command refer to the " DIR_COMMANDS "\n\n"
				 "Help Topics\n\n"
				 "\thelp          : Bring up this help menu\n"
				 "\tquit,q        : Exit the simulator\n\n"
				 "\tinp INPUT_FILE [OUTPUT FILE] :\n"
				 "\t                Specifies the input file to read from. The file specified\n"
				 "\t                should be a valid file on the disk. Optionally, an OUTPUT_FILE\n"
				 "\t                can be specified for writing WITCH printer outputs to.\n";

	msg.print(MsgLevel::M_MSG,helpString);
	return DriverStatus::COMMAND_SUCCESS;
}
DriverStatus Driver::c_quit(std::vector<std::string>& tokens){
	if(tokens.size() != 1) {
		msg.print(MsgLevel::M_MSG, "Incorrect usage\n");
		return DriverStatus::COMMAND_ARGUMENT_ERROR;
	}
	return DriverStatus::QUIT_SUCCESS;
}
DriverStatus Driver::c_set(std::vector<std::string>& tokens){
	// EXPECTED FORMAT : set INDEX VALUE
	// TODO : Add an argument to store 9 digits as well
	if(tokens.size() != 3) {
		msg.print(MsgLevel::M_MSG, "Incorrect usage\nUsage: set INDEX VALUE [-c]");
		return DriverStatus::COMMAND_ARGUMENT_ERROR;
	}
	int row, col;
	std::string str_val;
	if(tokens[1].length() != 2){
		msg.print(MsgLevel::M_MSG, "Incorrect index. Index has to be two digits long\n");
		return DriverStatus::COMMAND_ARGUMENT_ERROR;
	} else {
		if(!getDigitAt(tokens[1],0, row) ||
				!getDigitAt(tokens[1],1,col)){
			msg.print(MsgLevel::M_MSG, "Incorrect index\n");
					return DriverStatus::COMMAND_ARGUMENT_ERROR;
		}
		tempStore1 = witch.getStore(tokens[1]);
		if(tempStore1 == NULL) {
			msg.print(MsgLevel::M_MSG, "Cannot access store.\nMake sure index obeys NO_OF_STORE_ROW "
					"and NO_OF_STORE_COL defined in " DIR_DEFINITIONS "\n");
			return DriverStatus::COMMAND_ARGUMENT_ERROR;
		}
	}
	if(tokens[2].length() != 9 && tokens[2].length() != 6){
		msg.print(MsgLevel::M_MSG, "VALUE length not correct.\n");
		return DriverStatus::COMMAND_ARGUMENT_ERROR;
	} else if(tokens[2].length() == 9){
		if(tokens[2][0] == '+'){
			// +ve 8 digit
			int i = 1,j;
			std::string num = "0";
			while(i < 9){
				if(!getDigitAt(tokens[2],i,j)){
					msg.print(MsgLevel::M_MSG, "Invalid Value.\nValue should either be a 8 digit "
							"number with a leading + or - sign, or a 5 digit number with "
							"leading *.\n");
					return DriverStatus::COMMAND_ARGUMENT_ERROR;
				} else
					num += std::to_string(j);
				i++;
			}
			tempStore1->setStoreValue(num,tempDekatronArr);
		} else if(tokens[2][0] == '-'){
			// +ve 8 digit
			int i = 1,j;
			std::string num = "9";
			while(i < 9){
				if(!getDigitAt(tokens[2],i,j)){
					msg.print(MsgLevel::M_MSG, "Invalid Value.\nValue should either be a 8 digit "
							"number with a leading + or - sign, or a 5 digit number with "
							"leading *.\n");
					return DriverStatus::COMMAND_ARGUMENT_ERROR;
				} else
					num += std::to_string(9 - j);
				i++;
			}
			tempStore1->setStoreValue(num,tempDekatronArr);
		} else {
			msg.print(MsgLevel::M_MSG, "Incorrect VALUE\n");
			return DriverStatus::COMMAND_ARGUMENT_ERROR;
		}
	} else{
		// * and 5 digits
		if(tokens[2][0] != '*') {
			msg.print(MsgLevel::M_MSG, "Incorrect VALUE\n");
			return DriverStatus::COMMAND_ARGUMENT_ERROR;
		}
		int i = 1,j;
		std::string num = "0";
		while(i <= 5){
			if(!getDigitAt(tokens[2],i,j)){
				msg.print(MsgLevel::M_MSG, "Invalid Value.\nValue should either be a 8 digit "
						"number with a leading + or - sign, or a 5 digit number with "
						"leading *.\n");
				return DriverStatus::COMMAND_ARGUMENT_ERROR;
			} else
				num += std::to_string(j);
			i++;
		}
		num += "000";
		tempStore1->setStoreValue(num,tempDekatronArr);
	}
	msg.print(MsgLevel::M_MSG,"Store value set to " + tempStore1->getStringStateInStore() +"\n");
	return DriverStatus::COMMAND_SUCCESS;
}
DriverStatus Driver::c_inp(std::vector<std::string>& tokens){
	return DriverStatus::COMMAND_SUCCESS;
}

bool Driver::getDigitAt(std::string s,int index, int& num){
	num = s.at(index) - '0';
	logObj.log(LogLevel::L_DEBUG,"driver.cpp",std::to_string(num)+"\n");
	return (num >= 0 && num <= 9);
}
