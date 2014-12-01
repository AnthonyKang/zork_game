#ifndef ROOM_H_
#define ROOM_H_
#include <string>
#include <vector>
#include <iostream>
#include "Item.h"
#include "Trigger.h"
#include "Creature.h"
#include "Container.h"
#include "../rapidxml/rapidxml.hpp"
#include "../rapidxml/rapidxml_utils.hpp"
#include "../rapidxml/rapidxml_print.hpp"

using namespace std;
using namespace rapidxml;

typedef struct _border{
	string direction;
	string name;

} Border;

class Room: public gameObjects{
private:
	vector<Border> borders;
	vector<Container> containers;
	vector<Item> items;
	vector<Creature> creatures;
	vector<Trigger> triggers;

public:
	Room(xml_node<> * roomTag, vector<Item> itemList, vector<Creature> creatureList, vector<Container> containerList);

	void setBorders(Border);
	vector<Border> getBorders();

	void setContainers(Container*);
	vector<Container> * getContainers();

	void setItems(Item);
	vector<Item> getItems();

	void setCreatures(Creature*);
	vector<Creature> * getCreatures();

	vector<Trigger> * getTriggers();
	
	void itemErase(int);
	void itemAdd(Item);
	void containerAdd(string, Item);

};
#endif