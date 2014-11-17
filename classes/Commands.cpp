#include "Commands.h"
#include <iostream>
#include <string>
using namespace std;

Commands::Commands(){}

string Commands::getCommand(){
	return command;
}
void Commands::setCommand(string command){
	this->command = command;
}
