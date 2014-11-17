#ifndef CREATURE_H_
#define CREATURE_H_
#include <string>

#include "Item.h"

using namespace std;

class Creature{
public:
	string getName();
	void setName(string);
 
	Status getStatus();
	void setStatus(Status);

	string getDescription();
	void setDescription(string);

	Item * getVulnerability();
	void setVulnerability(Item*);

	Triggers * getTriggers();
	void setTriggers(Triggers*);

	Creature();


private:
	string name;
	Status status;
	string description;
	Item * vulnerability;
	//Attack attack;
	Triggers * triggers;


};
#endif