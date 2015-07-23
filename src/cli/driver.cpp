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
			msg.print(MsgLevel::M_MSG, "Unknown Error in execution\n");
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
	else if(tokens[0] == "print")
		return c_print(tokens);
	else if(tokens[0] == "order" || tokens[0] == "o")
		return c_order(tokens);
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
	 * functions. Do this in the respective functions since getUserInput has no easy
	 * way of knowing what the format specifications for each function are.
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

bool Driver::getDigitAt(std::string s,int index, int& num){
	num = s.at(index) - '0';
	//logObj.log(LogLevel::L_DEBUG,"driver.cpp",std::to_string(num)+"\n");
	return (num >= 0 && num <= 9);
}

DriverStatus Driver::witchErrorHandler(WitchStatus status){
	switch(status){
	case WitchStatus::INVALID_STORE_INDEX:
		msg.print(MsgLevel::M_MSG, "Incorrect index. Index has to be two digits long\n");
		return DriverStatus::COMMAND_ARGUMENT_ERROR;

	case WitchStatus::INVALID_STORE_ACCESS:
		msg.print(MsgLevel::M_MSG, "Cannot access store.\nMake sure index obeys NO_OF_STORE_ROW "
				"and NO_OF_STORE_COL defined in " DIR_DEFINITIONS "\n");
		return DriverStatus::COMMAND_ARGUMENT_ERROR;

	case WitchStatus::INVALID_STORE_VALUE_H:
		msg.print(MsgLevel::M_MSG, "VALUE is invalid\n");
		return DriverStatus::COMMAND_ARGUMENT_ERROR;

	case WitchStatus::INVALID_STORE_VALUE_R:
		msg.print(MsgLevel::M_MSG, "VALUE is invalid\n");
		return DriverStatus::COMMAND_ARGUMENT_ERROR;

	case WitchStatus::INVALID_WITCH_ORDER:
		msg.print(MsgLevel::M_MSG, "ORDER is invalid\n");
		return DriverStatus::COMMAND_ARGUMENT_ERROR;

	// TODO: Verify the following case
	case WitchStatus::NOT_SET_ORDER:
		msg.print(MsgLevel::M_WARNING,"ORDER not set\n");
		return DriverStatus::COMMAND_SUCCESS;

	case WitchStatus::OPERATION_SUCCESSFUL:
		return DriverStatus::COMAND_SUCCESS;
	case WitchStatus::OPERATION_NOT_DEFINED:
		msg.print(MsgLevel::MSG,"The operation is not yet supported\n");
		return DriverStatus::COMAND_SUCCESS;

	case WitchStatus::OPERATION_FAILURE:
		msg.print(MsgLevel::M_ERROR,"Operation error!\n");
		return DriverStatus::UNKNOWN_ERROR;
	default:
		break;
	}
	return DriverStatus::SUCCESS;
}
/********************************
 *****  Command definitions *****
 ********************************/
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
	/*
	 *  EXPECTED FORMAT : 'set INDEX VALUE'
	 *  Do a reordering if necessary
	 */
	// TODO : Add an argument to store 9 digits as well
	if(tokens.size() != 3) {
		msg.print(MsgLevel::M_MSG, "Incorrect usage\nUsage: set INDEX VALUE\n");
		return DriverStatus::COMMAND_ARGUMENT_ERROR;
	}
	WitchStatus status = witch.translateAndStore(tokens[1],tokens[2]);
	if(status != WitchStatus::OPERATION_SUCCESSFUL)
		return witchErrorHandler(status);
	else{
		std::string value;
		witch.translateAndLoad(tokens[1],value);
		msg.print(MsgLevel::M_MSG,"Store value set to " + value +"\n");
	}
	return DriverStatus::COMMAND_SUCCESS;
}

DriverStatus Driver::c_print(std::vector<std::string>& tokens){
	std::unordered_map<std::string, int> args;
	args = {{"print",0},{"-r",0}, {"-d",0}};
	for(std::vector<std::string>::iterator it = tokens.begin(); it != tokens.end() - 1; ++it){
		try{
			args.at(*it) = 1;
		} catch (const std::out_of_range& e){
			msg.print(MsgLevel::M_MSG, "Unknown argument " + *it + "\n");
			return DriverStatus::COMMAND_ARGUMENT_ERROR;
		}
	}
	std::string str_index = tokens.back();
	WitchStatus status;
	std::string out;
	if(args["-r"] == 1 && args["-d"] == 1){
		msg.print(MsgLevel::M_MSG, "-r and -d both not allowed\n");
		return DriverStatus::COMMAND_ARGUMENT_ERROR;
	} else if(args["-r"] == 1){
		status = witch.rawLoad(str_index,out);
	} else {
		status = witch.translateAndLoad(str_index,out);
	}
	if(status != WitchStatus::OPERATION_SUCCESSFUL)
		return witchErrorHandler(status);
	else
		msg.print(MsgLevel::M_MSG,"Store value is " + out +"\n");
	return DriverStatus::COMMAND_SUCCESS;
}
DriverStatus Driver::c_order(std::vector<std::string>& tokens){
	if(tokens.size() != 2){
		msg.print(MsgLevel::M_MSG, "Incorrect usage\nUsage: order ORDER\n");
		return DriverStatus::COMMAND_ARGUMENT_ERROR;
	}
	WitchStatus status = witch.setCurrentOrder(tokens[1]);
	if(status != WitchStatus::OPERATION_SUCCESSFUL)
		return witchErrorHandler(status);
	return witch.executeCurrentOrder();
}

DriverStatus Driver::c_inp(std::vector<std::string>& tokens){
	return DriverStatus::COMMAND_SUCCESS;
}
