#ifndef CONTAINER_H_
#define CONTAINER_H_
#include <string>
#include <vector>

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

	string getConditionSatisfy();
	void setConditionSatisfy(string);
	
	vector<string> getAccept();
	void setAccept(string);

	Item * getItem();
	void setItem(Item*);
	
	vector<Triggers> getTriggers();
	void setTriggers(Triggers);

	vector<Item> getItemList();
	void setItemList(Item);

private:
	string name;
	Status status;
	string description;
	vector<string> accept_list;
	Item * item;
	vector<Item> item_list;
	vector<Triggers> triggers;
	string conditionSatisfy;


};
#endif