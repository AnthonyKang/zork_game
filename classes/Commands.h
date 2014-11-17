#ifndef COMMANDS_H_
#define COMMANDS_H_
#include <string>
#include "Triggers.h"
using namespace std;

class Commands: public Triggers{
public:
	Commands();

	string getCommand();
	void setCommand(string);

private:
	string command;	
};
#endif