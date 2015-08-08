/*
 * commandhistory.h
 *
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 29-Jul-2015
 * 
 */


#ifndef COMMANDHISTORY_H
#define COMMANDHISTORY_H

#include "../lib/definitions.h"

struct CommandList{
	std::string command = "";
	CommandList* next = nullptr;
	CommandList* previous = nullptr;
};

class CommandHistory {
	/*New commands appended to the end. */
	CommandList* currentElement = nullptr;
	CommandList* earliestElement = nullptr;
	CommandList* latestElement = nullptr;

	int numberOfElements = 0;
	int maxCapacity = HISTORY_NUMBER;

	// Clears the earliest command and creates a new element
	void removeEarliest();
public :
	std::string getPrevious();
	std::string getNext();
	int add(std::string s);
};
#endif /*COMMANDHISTORY_H*/



