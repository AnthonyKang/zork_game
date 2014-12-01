#include <iostream>
#include <string>
#include <vector>
#include "../rapidxml/rapidxml.hpp"
#include "../rapidxml/rapidxml_utils.hpp"
#include "../rapidxml/rapidxml_print.hpp"
#include "Container.h"
#include "gameObjects.h"
#include "Creature.h"
#include "Trigger.h"
#include "Item.h"
#include "Room.h"
#include "utils.h"
#include <cstring>

using namespace std;
using namespace rapidxml;

int main(){

	// Initialize and parse xml file
	rapidxml::file<>xmlFile("../map1.xml");
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());

	// Initialize root xml node
	xml_node<> *map = doc.first_node();

	// Initialize Object Vectors
	vector<Item> gameItems;
	int item_count = 0;

	vector<Container> gameContainers;
	int container_count = 0;

	vector<Creature> gameCreatures;
	int creature_count = 0;

	// Create all game objects
	xml_node<> *mapElement = NULL;
	for(mapElement = map->first_node(); mapElement; mapElement = mapElement->next_sibling()){
		//cout << mapElement->name() << endl;
		if(strcmp(mapElement->name(),"item") == 0){
			Item newItem = Item(mapElement);
			gameItems.push_back(newItem);
			//cout << "hi" << endl;
		}		
		if(strcmp(mapElement->name(),"creature") == 0){
			Creature newCreature = Creature(mapElement);
			gameCreatures.push_back(newCreature);
		}
		
	}
	for(mapElement = map->first_node(); mapElement; mapElement = mapElement->next_sibling()){
		if(strcmp(mapElement->name(),"container") == 0){
			Container newContainer = Container(mapElement, gameItems);
			gameContainers.push_back(newContainer);
		}
	}

	// Initialize Room Vector
	vector<Room> gameRooms;
	int room_count = 0;

	// Create all game rooms
	for(mapElement = map->first_node(); mapElement; mapElement = mapElement->next_sibling()){
		if(strcmp(mapElement->name(),"room") == 0){
			Room newRoom = Room(mapElement, gameItems, gameCreatures, gameContainers);
			gameRooms.push_back(newRoom);
		}
	}

	// Initialize Player Inventory
	vector<Item> Inventory;

	// Initialize Game Object Iterators
	vector<Room>::iterator roomIt = gameRooms.begin();	
	vector<Item>::iterator itemIt = gameItems.begin();
	vector<Container>::iterator ContainerIt = gameContainers.begin();	
	vector<Creature>::iterator CreatureIt = gameCreatures.begin();

	// Initialize Game Loop
	string gameStatus = "";

	// Set initial room to be the first room
	string roomName = gameRooms[0].getName();
	int roomFind = 0;
	int roomCount = 0;

	while(roomName != "Game Over"){
		roomCount = 0;
		for(roomIt = gameRooms.begin(); roomIt != gameRooms.end(); roomIt++){
			if((roomIt)->getName() == roomName){
				roomFind = roomCount;
			}
			roomCount++;
		}
		roomName = loadRoom(&(gameRooms[roomFind]), &gameItems, &gameContainers, &gameCreatures, &Inventory);
		
	}
}