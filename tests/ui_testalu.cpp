/*
 * ui_testalu.cpp
 *
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 29-May-2015
 * 
 */
#include <iostream>
#include <string>
#include "../src/dekatron.h"
#include "../src/dekatronstore.h"
#include "../src/transferunit.h"
#include "../src/shiftcircuit.h"
#include "../src/alu.h"

int menu();
void printPrompt();
std::string getHumanReadableOutput(std::string inp,int size);

void add();
void subtract();
void multiply();

int main(int argc , char *argv[]) {

	std::cout << "\n\t\t\t# ALU test #\n"
				 "\n\t\t\tInstructions:\n"
				 "\tSelect the supported operation from the menu\n"	
		     	 "\tInput two 9-digit numbers, one per line without spaces\n"
		     	 "\tCompare the results and report any discrepancies\n"
		     	 "\tTo return back to the menu during an operation, enter 'm'\n";
	int option; 
	while(true) {
	    option = menu();
	    switch(option) {
	    	case 0 : 
	    		return 0;
	    	case 1 :
	    		add();
	    		break;
	    	case 2 :
	    		subtract();
	    		break;
	    	case 3 :
	    		multiply();
	    		break;
	    	default :
	    		std::cout << "*BUZZER* wrong option!\n";
	    }
	}
}

int menu() {
	std::string i;
	int ret = -1;
	std::cout << "\n\t\t\t## MENU ##\n"
				 "\tSupported Operations\n"
				 "\t1. Addition\n"
				 "\t2. Subtraction\n"
				 "\t3. Multiplication (++)(-+)\n\n"
				 "\t0. Quit\n";
	
	while(ret == -1) {
		printPrompt();
		std::cin >> i;
		try {
			ret = std::stoi(i);
		}catch (std::exception e) {
			std::cout << "Invalid argument\n";
			ret = -1;
		}
	}
	return ret;	
}

void printPrompt() {
	std::cout << "WITCH-e>>";
}
void add() {
	DekatronStore source,destination;
	Dekatron bufferDekatron[9];
	TransferUnit transferUnit;
	std::string s,d;
	int i_s = 0, i_d = 0;
	while(1) {
		// get source
		if( i_s == 0) {
			std::cout << "Enter source\n";
			printPrompt();
			std::cin >> s;
			if(s.compare("m") == 0)
				break;
			if(!source.setStoreValue(s, bufferDekatron))
				i_s =1;
			else
				std::cout << "Please try again\n";
		}
		//get destination
		if(i_s == 1 && i_d == 0) {
			std::cout << "Enter destination\n";
			printPrompt();
			std::cin >> d;
			if(d.compare("m") == 0)
				break;
			if(!destination.setStoreValue(d, bufferDekatron))
				i_d = 1;
			else
				std::cout << "Please try again\n";
		}
		if(i_s == 1 && i_d == 1) {
			transferUnit.transfer(&source,&destination);
			std::cout << "\nAns. " << getHumanReadableOutput(destination.getStringStateInStore(), 9) << " \n\n";
			i_s = 0;
			i_d = 0;
		}
	}
}

void subtract(){
	DekatronStore source,destination;
	Dekatron bufferDekatron[9];
	TransferUnit transferUnit;
	std::string s,d;
	int i_s = 0, i_d = 0;
	while(1) {
		// get source
		if( i_s == 0) {
			std::cout << "Enter source\n";
			printPrompt();
			std::cin >> s;
			if(s.compare("m") == 0)
				break;
			if(!source.setStoreValue(s, bufferDekatron))
				i_s =1;
			else
				std::cout << "Please try again\n";
		}
		//get destination
		if(i_s == 1 && i_d == 0) {
			std::cout << "Enter destination\n";
			printPrompt();
			std::cin >> d;
			if(d.compare("m") == 0)
				break;
			if(!destination.setStoreValue(d, bufferDekatron))
				i_d = 1;
			else
				std::cout << "Please try again\n";
		}
		if(i_s == 1 && i_d == 1) {
			transferUnit.transferComplement(&source,&destination);
			std::cout << "\nAns. " << getHumanReadableOutput(destination.getStringStateInStore(), 9) << " \n\n";
			i_s = 0;
			i_d = 0;
		}
	}

}
void multiply(){
	DekatronStore source,destination;
	Accumulator accum;
	Dekatron bufferDekatron[9];
	TransferUnit transferUnit;
	ALU alu;
	std::string s,d;
	int i_s = 0, i_d = 0;
	while(1) {
		// get source
		if( i_s == 0) {
			std::cout << "Enter source\n";
			printPrompt();
			std::cin >> s;
			if(s.compare("m") == 0)
				break;
			if(!source.setStoreValue(s, bufferDekatron))
				i_s =1;
			else
				std::cout << "Please try again\n";
		}
		//get destination
		if(i_s == 1 && i_d == 0) {
			std::cout << "Enter destination\n";
			printPrompt();
			std::cin >> d;
			if(d.compare("m") == 0)
				break;
			if(!destination.setStoreValue(d, bufferDekatron))
				i_d = 1;
			else
				std::cout << "Please try again\n";
		}
		if(i_s == 1 && i_d == 1) {
			accum.clearAccumulator();
			alu.multiply(&source,&destination,&accum);
			std::cout << "\nAns. " << getHumanReadableOutput(accum.getStringStateInStore(),16) << " \n\n";
			i_s = 0;
			i_d = 0;
		}
	}
}

std::string getHumanReadableOutput(std::string inp,int size){
	inp.insert(1," ");
	inp.insert(6," ");
	if(size == 16) {
		inp.insert(11," ");
		inp.insert(16," ");
	}
	return inp;
}



