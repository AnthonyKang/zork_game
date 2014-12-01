#include <iostream>
#include <string>
#include <vector>
#include "Room.h"
#include "Container.h"
#include "../rapidxml/rapidxml.hpp"
#include "../rapidxml/rapidxml_utils.hpp"
#include "../rapidxml/rapidxml_print.hpp"
#include <cstring>

using namespace std;
using namespace rapidxml;

Room::Room(xml_node<> * RoomTag, vector<Item> itemList, vector<Creature> creatureList, vector<Container> containerList){

	xml_node<> * roomElement = NULL;

	type = "regular";
	deleted = 0;
	Border newBorder;
	vector<Item>::iterator i = itemList.begin();
	vector<Container>::iterator c = containerList.begin();
	vector<Creature>::iterator b = creatureList.begin();

	for(roomElement = RoomTag->first_node(); roomElement; roomElement = roomElement->next_sibling()){
		if(strcmp(roomElement->name(),"name") == 0){
			name = roomElement->value();
		}
		if(strcmp(roomElement->name(),"status") == 0){
			status = roomElement->value();
		}
		if(strcmp(roomElement->name(),"description") == 0){
			description = roomElement->value();
		}
		if(strcmp(roomElement->name(),"type") == 0){
			type = roomElement->value();
		}
		if(strcmp(roomElement->name(),"border") == 0){

			xml_node<> * borderElement = roomElement->first_node();
			
			newBorder.direction = borderElement->value();
			borderElement = borderElement->next_sibling();
			newBorder.name = borderElement->value();

			borders.push_back(newBorder);
		}
		if(strcmp(roomElement->name(),"item") == 0){
			for(i = itemList.begin(); i != itemList.end(); i++){
				//cout << i->getName() << endl;
				if(((i)->getName()) == (roomElement->value())){
					items.push_back(*i);
				}
			}
		}
		if(strcmp(roomElement->name(), "container") == 0){
			for(c = containerList.begin(); c != containerList.end(); c++){
				if(((c)->getName()) == (roomElement->value())){
					containers.push_back(*c);
				}
			}
		}
		if(strcmp(roomElement->name(), "creature") == 0){
			for(b = creatureList.begin(); b != creatureList.end(); b++){
				if(((b)->getName()) == (roomElement->value())){
					creatures.push_back(*b);
				}
			}
		}
		if(strcmp(roomElement->name(), "trigger") == 0){
			Trigger newTrigger = Trigger(roomElement);
			triggers.push_back(newTrigger);
		}

	}

}

vector<Item> Room::getItems(){
	return items;
}

vector<Container> * Room::getContainers(){
	return &containers;
}

vector<Creature> * Room::getCreatures(){
	return &creatures;
}

vector<Border> Room::getBorders(){
	return borders;
}

vector<Trigger> * Room::getTriggers(){
	return &triggers;
}

void Room::itemErase(int location){
	items.erase(items.begin() + location);
}

void Room::itemAdd(Item newitem){
	items.push_back(newitem);
	//cout << "Added" << endl;
}

void Room::containerAdd(string containerName, Item item){
	vector<Container>::iterator containerIt = containers.begin();
	for(containerIt = containers.begin(); containerIt != containers.end(); containerIt++){
		if(containerIt->getName() == containerName){
			containerIt->addItem(item);
		}
	}
}