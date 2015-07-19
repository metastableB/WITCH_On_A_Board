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
		return 1;
	std::string inp;
	while(true) {
		printPrompt();
		inp = getUserInput();
		execute(inp);
	}
	return 0;
}

void Driver::execute(std::string inp) {
	/*
	 * Make sure inp is valid, else print msg
	 * 	this will include checking if inp is among the supported commands
	 * 	and if is, also check for correct arguements.
	 * then executing the command.
	 * Saparate each command to its own functions for ease.
	 */
}
bool Driver::commandLineArgs(int argc, char** argv) {
	if(argc != 1) {
		logObj.log(LogLevel::ERROR, "driver.cpp", "Argument error\n");
		msg.print(MsgLevel::ERROR, "Argument Error\n");
		return false;
	}
	return true;
}
std::string Driver::getUserInput(){
	std::string inp;
	std::cin >> inp;
	return inp;
}
void Driver::printPrompt(){
 	msg.print(MsgLevel::MSG, "WITCH-e>>");
}


