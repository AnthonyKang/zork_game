#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include "../rapidxml/rapidxml.hpp"
#include "../rapidxml/rapidxml_utils.hpp"
#include "../rapidxml/rapidxml_print.hpp"
#include "utils.h"
#include "Room.h"

//#include "../rapidxml/rapidxml_iterators.hpp"
using namespace std;
using namespace rapidxml;
/*
Room * makeRoom(Room * room, xml_node<> * room_node){
	
	//Room * new_room = new Room();
	cout<< room_node->name() << endl;
	//return new_room;
}
*/
int main(){

	// Initialize and parse xml file
	rapidxml::file<>xmlFile("../map1.xml");
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());

	// Initialize root xml node
	xml_node<> *map = doc.first_node();

	// Initialize Item Vector
	vector<Item> gameItems;
	int item_count = 0;

	// Create all game items
	xml_node<> *mapElement = NULL;
	for(mapElement = map->first_node(); mapElement; mapElement = mapElement->next_sibling()){
		//cout << mapElement->name() << endl;
		if(strcmp(mapElement->name(),"item") == 0){
			gameItems.push_back(makeItem(mapElement)); 
		}
	}

	// Initialize Container Vector
	vector<Container> gameContainers;
	int container_count = 0;

	// Create all game containers
	mapElement = NULL;
	for(mapElement = map->first_node(); mapElement; mapElement = mapElement->next_sibling()){
		//cout << mapElement->name() << endl;
		if(strcmp(mapElement->name(),"container") == 0){
			gameContainers.push_back(makeContainer(mapElement, gameItems)); 
		}
	}

	// Initialize Creature Vector
	vector<Creature> gameCreatures;
	int creature_count = 0;

	// Create all game Creatures
	mapElement = NULL;
	for(mapElement = map->first_node(); mapElement; mapElement = mapElement->next_sibling()){
		if(mapElement->name() == "creature"){
			gameCreatures.push_back(makeCreature(mapElement));
		}
	}

	vector<Item>::iterator i = gameItems.begin();
	for(i = gameItems.begin(); i != gameItems.end(); i++){
		cout << i->getName() << endl;
	}
	
	
	
	//Room * room_list = new Room[3];
	//cout << "hi";
	//room_list[0] = makeRoom(0, map);
	//cout << room_list[0].getDescription();
	/*while((buffer = buffer->next_sibling()) != NULL){
		cout << buffer->name() << endl;
	}*/
}