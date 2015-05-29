/*
 * interface_additiontest.cpp
 *
 * @author Don Dennis (metastableB)
 * donkdennis [at] gmail [dot] com
 * 29-May-2015
 * 
 */
#include <iostream>
#include <string>
#include "testdekatron.h"
#include "testdekatronstore.h"
#include "testtransferunit.h"

int main(int argc , char *argv[]) {
	DekatronStore source,destination;
	Dekatron bufferDekatron[9];
	TransferUnit transferUnit;
	std::cout << "Addition test\n"
		     "Input two 9-digit numbers, one per line without spaces\n";
	std::string s,d;
	int i_s = 0, i_d = 0;
	while(1) {
		// get source
		if( i_s == 0) {
			std::cout << "Enter source\n";
			std::cin >> s;
			if(!source.setStoreValue(s, bufferDekatron))
				i_s =1;
			else
				std::cout << "Please try again\n";
		}
		//get destination
		if(i_s == 1 && i_d == 0) {
			std::cout << "Enter destination\n";
			std::cin >> d;
			if(!destination.setStoreValue(d, bufferDekatron))
				i_d = 1;
			else
				std::cout << "Please try again\n";
		}
		if(i_s == 1 && i_d == 1) {
			transferUnit.transfer(&source,&destination);
			std::cout << destination.getStringStateInStore() << " Ans.\n\n";
			i_s = 0;
			i_d = 0;
		}
	}

}



