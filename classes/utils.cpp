#include <iostream>
#include <string>
#include <cstring>
#include "Room.h"
#include "Item.h"
#include "Owner.h"
#include "Conditions.h"
#include "Creature.h"
#include "Attack.h"
#include "Triggers.h"
//#include "utils.h"
#include "../rapidxml/rapidxml.hpp"
#include "../rapidxml/rapidxml_utils.hpp"
#include "../rapidxml/rapidxml_print.hpp"
//#include "../rapidxml/rapidxml_iterators.hpp"
using namespace std;
using namespace rapidxml;
Item makeItem(xml_node<> * item){
	
	// Initialize a new Item
	Item newItem = Item();

	// Fill in item elements
	xml_node<> *itemElement = NULL;
	for(itemElement = item->first_node(); itemElement; itemElement = itemElement->next_sibling()){
		//cout << itemElement->name() << endl;
		if(strcmp(itemElement->name(),"name") == 0){
			newItem.setName(itemElement->value());
		}
		if(strcmp(itemElement->name(),"writing") == 0){
			newItem.setWriting(itemElement->value());
		}
		if(strcmp(itemElement->name(),"status") == 0){
			Status itemStatus = Status();
			itemStatus.setStatus("lit"); 
			itemStatus.setObject(newItem.getName());
			newItem.setStatus(itemStatus);
		}
		if(strcmp(itemElement->name(),"turnon") == 0){
			newItem.setOnFlag((itemElement->first_node())->value());
		}

	}
	
	return newItem;

}

Container makeContainer(xml_node<> * container, vector<Item> gameItems){
	
	// Iterator to look for items to correspond with container
	vector<Item>::iterator i = gameItems.begin();

	// Initialize a new Container
	Container newContainer = Container();

	// Fill in container elements
	xml_node<> *containerElement = NULL;
	for(containerElement = container->first_node(); containerElement; containerElement = containerElement->next_sibling()){
		//cout << itemElement->name() << endl;
		// Set container name
		if(strcmp(containerElement->name(),"name") == 0){
			newContainer.setName(containerElement->value());
		}
		// Insert items in container
		if(strcmp(containerElement->name(),"item") == 0){
			// Iterate through item list
			for(i = gameItems.begin(); i != gameItems.end(); i++){
				// If item in item list matches item specified in XML, add it
				if((i->getName() == containerElement->value()) == 0){
					newContainer.setItemList(*i);
				}
			}
		
		}
		// Set status of container
		if(strcmp(containerElement->name(),"status") == 0){
			Status containerStatus = Status();
			containerStatus.setStatus("lit"); 
			containerStatus.setObject(newContainer.getName());
			newContainer.setStatus(containerStatus);
		}
		// Insert accepted item names in to accept vector
		if(strcmp(containerElement->name(),"accept") == 0){
			newContainer.setAccept(containerElement->value());
		}
		// Insert triggers in to trigger vector
		if(strcmp(containerElement->name(),"trigger") == 0){
			xml_node<> * triggerElement = NULL;
			Owner conditionOwner = Owner();
			Conditions triggerCondition = Conditions();
			
			// Iterate through trigger tag
			for(triggerElement = containerElement->first_node(); triggerElement; triggerElement = triggerElement->next_sibling()){
				if(strcmp(triggerElement->name(),"condition") == 0){
					xml_node<> * conditionElement = NULL;
					for(conditionElement = triggerElement->first_node(); conditionElement; conditionElement = conditionElement->next_sibling()){
						if((conditionElement->name()) == "has"){
							if(triggerElement->value() == "yes"){
								conditionOwner.have(1);
							}else{
								conditionOwner.have(0);
							}
						}
						if((triggerElement->name()) == "object"){
							conditionOwner.setObject(triggerElement->value());
						}
						if((triggerElement->name()) == "owner"){
							conditionOwner.setOwner(triggerElement->value());
						}

					}
					
					triggerCondition.setOwner(conditionOwner);
					newContainer.setTriggers(triggerCondition);
				}
				if(triggerElement->name() == "print"){
					newContainer.setConditionSatisfy(triggerElement->value());
				}
			}

			

		}
	

	}
	return newContainer;
}
Creature makeCreature(xml_node<> * creature){
	// Initialize a new Creature
	Creature newCreature = Creature();

	// Fill in Creature Elements
	xml_node<> * creatureElement = NULL;
	for(creatureElement = creature->first_node(); creatureElement; creatureElement = creatureElement->next_sibling()){
		if(creatureElement->name() == "name"){
			newCreature.setName(creatureElement->value());
		}
		if(creatureElement->name() == "vulnerability"){
			newCreature.setName(creatureElement->value());
		}
		if(creatureElement->name() == "attack"){
			xml_node<> * attackElement = NULL;
			xml_node<> * attackCondition = NULL;
			Attack creatureAttacked = Attack();
			for(attackElement = creatureElement->first_node(); attackElement; attackElement = attackElement->next_sibling()){
				if(attackElement->name() == "condtion"){
					for(attackCondition = attackElement->first_node(); attackCondition; attackCondition = attackCondition->next_sibling()){
						if(attackCondition->name() == "object"){
							creatureAttacked.setObject(attackCondition->value());
						}
						if(attackCondition->name() == "status"){
							creatureAttacked.setStatus(attackCondition->value());
						}
					}
				}
				if(attackElement->name() == "print"){
					creatureAttacked.setPrint(attackElement->value());
				}
			}
			newCreature.setAttack(creatureAttacked);
		}
		if(creatureElement->name() == "trigger"){
			Conditions triggerCondition = Conditions();
			Status triggerConditionStatus = Status();
			xml_node<> * triggerElement = NULL;
			for(triggerElement = creatureElement->first_node(); triggerElement; triggerElement = triggerElement->next_sibling()){
				string type = "";
				if(triggerElement->name() == "type"){
					type = triggerElement->value();
				}
				if(triggerElement->name() == "condition"){
					triggerCondition = Conditions();
					triggerConditionStatus = Status();
					xml_node<> * conditionElement = NULL;
					for(conditionElement = triggerElement->first_node(); conditionElement; conditionElement = conditionElement->next_sibling()){
						if(conditionElement->name() == "object"){
							triggerConditionStatus.setObject(conditionElement->value());
						}
						if(conditionElement->name() == "status"){
							triggerConditionStatus.setStatus(conditionElement->value());
						}
					}
					triggerCondition.setStatus(triggerConditionStatus);
				}
			}	
		newCreature.setTriggers(triggerCondition);
		}
	}
}

/*
Room makeRoom(int room_number, xml_node<> * map){
	
	Room room = Room();
	xml_node<> *room_node = map->first_node();
	for(int i = 0; i < room_number; i++){
		room_node = room_node->next_sibling();
	}
	// Set buffer to equal the first node under room, which is always name
	xml_node<> *buffer = room_node->first_node();
	
	// Set room name
	//room->setName(buffer->value());
	
	// count how many items, creatures, in this room and allocate arrays for them
	int item_count = 0;
	int creature_count = 0;
	int trigger_count = 0;
	xml_node<> * content_buffer = buffer;
	xml_node<> * trigger_buffer = NULL;
	//xml_node<> * finder = room_node;
	while((content_buffer = content_buffer->next_sibling()) != NULL){
		if(strcmp(content_buffer->name(),"item") == 0){
			item_count = item_count++;
		}
		if(strcmp(content_buffer->name(),"creature") == 0){
			creature_count = creature_count++;
		}
		if(strcmp(content_buffer->name(),"trigger") == 0){
			trigger_buffer = content_buffer -> first_node();
			//cout << trigger_buffer->name() << endl;
			while((trigger_buffer = trigger_buffer->next_sibling()) != NULL){
				//cout << trigger_buffer->name() << endl;
				trigger_count = trigger_count++;
			}
		}
	}
	Item * item_list = new Item[item_count+1];
	Creature * creature_list = new Creature[creature_count+1];
	Triggers * trigger_list = new Triggers[trigger_count+1];

	item_count = creature_count = trigger_count = 0;
	
	for(buffer = room_node->first_node(); buffer; buffer = buffer->next_sibling()){
		//cout << buffer->name() << endl;
		if(strcmp((buffer->name()),"description") == 0){
			room.setDescription(buffer->value());
		}
		if(strcmp((buffer->name()),"item") == 0){
			string itemName = buffer->value();
			//item_list[item_count] = makeItem(itemName, map);
			item_list[item_count] = makeItem(itemName,map);
		}
		

	}

	return room;
}
*/
