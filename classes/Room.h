#ifndef ROOM_H_
#define ROOM_H_
#include <string>

#include "Status.h"
#include "Container.h"
#include "Item.h"
#include "Creature.h"
#include "Triggers.h"
#include <vector>


using namespace std;

class Room{
private:
	string name;
	Status status;
	string type;
	string description;
	string * border;
	Container * container;
	Item * item;
	Creature * creature;
	Triggers * triggers;
	vector<Item> item_list;
public:
	Room();

	string getName();
	void setName(string);
 
	Status getStatus();
	void setStatus(Status);

	string getType();
	void setType(string);

	string getDescription();
	void setDescription(string);

	string * getBorder();
	void setBorder(string*);

	Container * getContainer();
	void setContainer(Container*);

	Item * getItem();
	void setItem(Item*);

	Creature * getCreature();
	void setCreature(Creature*);

	Triggers * getTriggers();
	void setTriggers(Triggers*);

};
#endif/*ROOM_H*/
