#ifndef CONTAINER_H_
#define CONTAINER_H_
#include <string>

#include "Item.h"
#include "Triggers.h"
#include "Status.h"

#include "Creature.h"
using namespace std;

class Container{
public:
	Container();

	string getName();
	void setName(string);
 
	Status getStatus();
	void setStatus(Status);

	string getDescription();
	void setDescription(string);
	
	Item * getAccept();
	void setAccept(Item*);

	Item * getItem();
	void setItem(Item*);

	Creature * getCreature();
	void setCreature(Creature*);

	Triggers * getTriggers();
	void setTriggers(Triggers*);

private:
	string name;
	Status status;
	string description;
	Item * accept;
	Item * item;
	Triggers * triggers;


};
#endif