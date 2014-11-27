#ifndef GAMEOBJECTS_H_
#define GAMEOBJECTS_H_
#include <string>
#include <vector>
#include <iostream>
#include "Trigger.h"
#include "../rapidxml/rapidxml.hpp"
#include "../rapidxml/rapidxml_utils.hpp"
#include "../rapidxml/rapidxml_print.hpp" 

using namespace std;

/*
typedef struct _condition{
	string object;
	string status;
	string has;
	string owner;

} Condition;
*/

typedef struct _attk{
	Condition condition;
	string print;
	vector<string> action;
} Attack;


class gameObjects{
private:

protected:
		
	string name;
	string status;
	string type;
	string description;
	vector<Trigger> trigger;

public:

	gameObjects();

	void setName(string);
	string getName();

	void setStatus(string);
	string getStatus();

	void setType(string);
	string getType();

	void setDescription(string);
	string getDescription();

	void setTrigger(Trigger);
	vector<Trigger> getTrigger();

};
#endif