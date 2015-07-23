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
		case DriverStatus::UNKNOWN_ERROR :
			msg.print(MsgLevel::M_ERROR, "Unknown Error in execute\n");
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
		msg.print(MsgLevel::M_ERROR, "Argument Error\n");
		return false;
	}
	return true;
}
void Driver::getUserInput(std::vector<std::string>& tokens){
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
 	msg.print(MsgLevel::M_MSG, "WITCH-e>> ");
}


/*
 *  Command definitions
 */
DriverStatus Driver::c_help(std::vector<std::string>& tokens){
	std::string helpString = "The WITCH_On_A_Board Project\n\n"
				 "Help Topics\n"
				 "help          : Bring up this help menu\n"
				 "quit,q        : Exit the simulator.\n"
				 "inp INPUT_FILE [OUTPUT FILE] :\n"
				 "                Specifies the input file to read from. The file specified\n"
				 "                should be a valid file on the disk. Optionally, an OUTPUT_FILE\n"
				 "                can be specified for writing WITCH printer outputs to.\n";

	msg.print(MsgLevel::M_MSG,helpString);
	return DriverStatus::COMMAND_SUCCESS;
}
DriverStatus Driver::c_quit(std::vector<std::string>& tokens){
	// TODO PARSE INPUT
	return DriverStatus::QUIT_SUCCESS;
}
DriverStatus Driver::c_inp(std::vector<std::string>& tokens){
	return DriverStatus::COMMAND_SUCCESS;
}
