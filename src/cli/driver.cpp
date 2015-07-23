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
	std::vector<std::string> inp;
	while(true) {
		printPrompt();
		getUserInput(inp);
		switch(execute(inp)) {
		case DriverStatus::QUIT_SUCCESS :
			return DriverStatus::QUIT_SUCCESS;
		case DriverStatus::UNKNOWN_ERROR :
			msg.print(MsgLevel::ERROR, "Unknown Error in execute\n");
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
		logObj.log(LogLevel::ERROR, "driver.cpp", "UNKNOWN ERROR in execute()\n");
		return DriverStatus::UNKNOWN_ERROR;
	}
	return DriverStatus::QUIT_FAILURE;
}
bool Driver::commandLineArgs(int argc, char** argv) {
	if(argc != 1) {
		logObj.log(LogLevel::ERROR, "driver.cpp", "Argument error\n");
		msg.print(MsgLevel::ERROR, "Argument Error\n");
		return false;
	}
	return true;
}
void Driver::getUserInput(std::vector<std::string>& tokens){
	tokens.clear();
	std::string line;
	if(!std::getline(std::cin,line))
		logObj.log(LogLevel::ERROR,"driver.cpp","UNKNOWN ERROR with user input\n");
	std::istringstream buffer(line);
	std::copy(std::istream_iterator<std::string>(buffer),
		  std::istream_iterator<std::string>(),
		  tokens.begin());
#ifdef _DEBUG_
	if(!tokens.empty()) {
		std::string arg;
		for(std::vector<std::string>::iterator it = tokens.begin(); it != tokens.end(); ++it)
			arg += *it + " ";
		logObj.log(LogLevel::DEBUG,"driver.cpp","Received input: " + arg + "\n");
	} else
		logObj.log(LogLevel::DEBUG,"driver.cpp","Received input: EMPTY\n");

#endif /* _DEBUG_ */
}
void Driver::printPrompt(){
 	msg.print(MsgLevel::MSG, "WITCH-e>>");
}


/*
 *  Command definitions
 */
DriverStatus Driver::c_help(std::vector<std::string>& tokens){
	std::string helpString = "The WITCH_On_A_Board Project\n\n"
				 "Help Topics\n"
				 "help		:\n"
				 "		 Bring up this help menu\n"
				 "quit,q	:\n"
				 "		 Exit the simulator.\n"
				 "inp INPUT_FILE [OUTPUT FILE] :"
				 "		 Specifies the input file to read from. The file specified\n"
				 "               should be a valid file on the disk. Optionally, an OUTPUT_FILE\n"
				 " 		 can be specified for writing WITCH printer outputs to.\n";
	return DriverStatus::COMAND_SUCCESS;
}
