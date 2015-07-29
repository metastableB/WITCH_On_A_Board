/*
 * commandhistory.cpp
 *
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 29-Jul-2015
 * 
 */

#include "commandhistory.h"

std::string CommandHistory::getNext(){
	if(numberOfElements == 0)
		return "";
	if(currentElement->next == nullptr)
		return "";
	currentElement = currentElement->next;
	return currentElement->command;
}

std::string CommandHistory::getPrevious(){
	if(numberOfElements == 0)
		return "";
	if(currentElement->previous == nullptr)
		return currentElement->command;
	currentElement = currentElement->previous;
	return currentElement->command;
}

int CommandHistory::add(std::string s){

	if(numberOfElements == maxCapacity)
		removeEarliest();
	// TODO : Catch Exception
	latestElement = new CommandList();
	latestElement->command = s;
	latestElement->next = nullptr;
	latestElement->previous = currentElement;
	currentElement = latestElement;
	numberOfElements++;
	if(numberOfElements == 1)
		earliestElement == currentElement;
}

void CommandHistory::removeEarliest(){
	if(numberOfElements == 0)
		return;
	CommandList* temp = earliestElement;
	earliestElement = earliestElement->next;
	earliestElement->previous = nullptr;
	free(temp);
	numberOfElements -=1 ;
}




