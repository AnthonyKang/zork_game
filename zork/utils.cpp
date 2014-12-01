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

void updateItem(Item item, string action){
	string delim = " ";
	string status;
	size_t pos = 0;
	while((pos = action.find(delim)) != std::string::npos){
		status = action.substr(0,pos);
		action.erase(0, pos + delim.length());
	}
	item.setStatus(status);
}

void updateContainer(Container container, string action){
	string delim = " ";
	string status;
	size_t pos = 0;
	while((pos = action.find(delim)) != std::string::npos){
		status = action.substr(0,pos);
		action.erase(0, pos + delim.length());
	}
	container.setStatus(status);
}


string loadRoom(Room * room, vector<Item>  * gameItems, vector<Container>  * gameContainers, vector<Creature>  * gameCreatures, vector<Item> * Inventory){
	cout << room->getDescription() << endl;
	string command;
	int in_room = 1;
	string stay = "";
	while(in_room){
		cout << ">";
		getline(cin,command);
		/*
		if(commandValid(command, room, gameItems, gameContainers, gameCreatures, inventory)){
			//executeCommand();
		}*/
		//checkTrigger(room, gameItems, gameContainers, gameCreatures, Inventory);
		stay = executeCommand(command, room, gameItems, gameContainers, gameCreatures, Inventory);
		//checkTrigger(room, gameItems, gameContainers, gameCreatures, Inventory);
		//cout << stay << endl;
		if(stay != "stay"){
			return stay;
		}
	}
	
}

void checkTrigger(Room * room, vector<Item>  * gameItems, vector<Container>  * gameContainers, vector<Creature>  * gameCreatures, vector<Item> * Inventory){
	vector<Item> roomItems = room->getItems();
	vector<Container> * roomContainer = room->getContainers();
	vector<Creature> * roomCreature = room->getCreatures();
	vector<Border> roomBorders = room->getBorders();
	vector<Trigger> * roomTriggers = room->getTriggers();

	// check triggers of items, containers, and creatures in room
	
	// check containers
	//cout << "hi" << endl;
	vector<Container>::iterator roomContainerTriggIt = roomContainer->begin();
	for(roomContainerTriggIt = roomContainer->begin(); roomContainerTriggIt != roomContainer->end(); roomContainerTriggIt++){
		// for each container, get all the triggers
		vector<Trigger> * roomContainerTriggers = roomContainerTriggIt->getTrigger();
		vector<Trigger>::iterator containerTriggerIt = roomContainerTriggers->begin();
		// iterate through each trigger
		//cout << "hiballs" << endl;
		for(containerTriggerIt = roomContainerTriggers->begin(); containerTriggerIt != roomContainerTriggers->end(); containerTriggerIt++){
			Condition contCondition = containerTriggerIt->getCondition();
			string has = contCondition.has;
			vector<string> contTriggAction = containerTriggerIt->getAction();
			// get items in container
			vector<Item> * contItem = roomContainerTriggIt->getItem();
			vector<Item>::iterator contItemIt = contItem->begin();
			// check if container contains item that matches condition
			//cout << "hi" << endl;
			//cout << "has: " << has << endl;
			if(has == "yes"){
				//cout << "hi" << endl;
				for(contItemIt = contItem->begin(); contItemIt != contItem->end(); contItemIt++){
					//cout << contItemIt->getName() << endl;
					if(contItemIt->getName() == contCondition.object){
						cout << containerTriggerIt->getPrint() << endl;
						// iterate through each action
						vector<string>::iterator actionIt = contTriggAction.begin();
						for(actionIt = contTriggAction.begin(); actionIt != contTriggAction.end(); actionIt++){
							executeCommand(*actionIt, room, gameItems, gameContainers, gameCreatures, Inventory);
						}
						return;
					}
				}
			}
		}
	}

	// check creatures
	vector<Creature>::iterator roomCreatureTriggIt = roomCreature->begin();
	for(roomCreatureTriggIt = roomCreature->begin(); roomCreatureTriggIt != roomCreature->end(); roomCreatureTriggIt++){
		// for each Creature, get all the triggers
		vector<Trigger> * roomCreatureTriggers = roomCreatureTriggIt->getTrigger();
		vector<Trigger>::iterator creatureTriggerIt = roomCreatureTriggers->begin();
		// iterate through each trigger
		for(creatureTriggerIt = roomCreatureTriggers->begin(); creatureTriggerIt != roomCreatureTriggers->end(); creatureTriggerIt++){
			string type = creatureTriggerIt->getType();
			//cout << type << endl;
			Condition creatureTriggerCondition = creatureTriggerIt->getCondition();
			string has = creatureTriggerCondition.has;
			string creaTriggCondStatus = creatureTriggerCondition.status;
			string creaTriggCondObject = creatureTriggerCondition.object;
			// iterate through game items
			vector<Item>::iterator gameItemsIt = gameItems->begin();
			if(type != "activated"){
				for(gameItemsIt = gameItems->begin(); gameItemsIt != gameItems->end(); gameItemsIt++){
					//cout << gameItemsIt->getName();
					if(gameItemsIt->getName() == creaTriggCondObject){
						if(gameItemsIt->getStatus() == creaTriggCondStatus){
							cout << creatureTriggerIt->getPrint() << endl;
							if(type == "single"){
								creatureTriggerIt->setType("activated");
							}
						}
					}
				}
			}

		}
	}


}

string executeCommand(string playerCommand, Room * room, vector<Item>  * gameItems, vector<Container>  * gameContainers, vector<Creature>  * gameCreatures, vector<Item> * Inventory){
	vector<Item> roomItems = room->getItems();
	vector<Container> * roomContainer = room->getContainers();
	vector<Creature> * roomCreature = room->getCreatures();
	vector<Border> roomBorders = room->getBorders();
	vector<Trigger> * roomTriggers = room->getTriggers();

	/*
	vector<Container>::iterator test = roomContainer->begin();
	for(test = roomContainer->begin(); test != roomContainer->end(); test++){
		cout<<test->getName()<< " :";
		vector<Item> containerItems = test->getItem();
		vector<Item>::iterator itemit = containerItems.begin();
		for(itemit = containerItems.begin(); itemit!= containerItems.end(); itemit++){
			cout<<itemit->getName()<<endl;
		}
	}*/
		
	if(playerCommand == "n" || playerCommand == "s" || playerCommand == "e" || playerCommand == "w"){
		
		// check trigger
		vector<Trigger>::iterator roomTriggerIt = roomTriggers->begin();
		// for each trigger in the room
		for(roomTriggerIt = roomTriggers->begin(); roomTriggerIt != roomTriggers->end(); roomTriggerIt++){
			// if the trigger command is the same as player command
			if(roomTriggerIt->getCommand() == playerCommand){
				// get the Condition of the trigger
				Condition roomTriggerCondition = roomTriggerIt->getCondition();
				string has = roomTriggerCondition.has;
				if(roomTriggerCondition.owner == "inventory"){
					vector<Item>::iterator inventoryIt = Inventory->begin();
					// if user has, check if item is in inventory
					if(has == "yes"){
						for(inventoryIt = Inventory->begin(); inventoryIt != Inventory->end(); inventoryIt++){
							if((inventoryIt)->getName() == roomTriggerCondition.object){
								cout << roomTriggerIt->getPrint() << endl;
							}
						}
					}
					// if user does not have
					else if(has == "no"){
						// search through inventory
						int has_check = 0;
						for(inventoryIt = Inventory->begin(); inventoryIt != Inventory->end(); inventoryIt++){
							if((inventoryIt)->getName() == roomTriggerCondition.object){
								has_check = 1;
							}
						}
						// if user has it, then it passes the check
						if(!has_check || Inventory->empty()){
							cout << roomTriggerIt->getPrint() << endl;
							return "stay";
						}
					}
				}
				else{
					// get the object of condition
					string conditionObject = roomTriggerCondition.object;

					// find the object in items, creatures, or containers
					vector<Item>::iterator roomItemIt = roomItems.begin();
					for(roomItemIt = roomItems.begin(); roomItemIt != roomItems.end(); roomItemIt++){
						if((roomItemIt)->getName() == conditionObject){
							if(!(roomItemIt->isDeleted())){
								// check status
								if((roomItemIt)->getStatus() == roomTriggerCondition.status){
									cout << roomTriggerIt->getPrint();
									return "stay";
								}
							}
						}
					}
					/*
					vector<Container>::iterator roomContainerIt = roomContainer->begin();
					for(roomContainerIt = roomContainer->begin(); roomContainerIt != roomContainer->end(); roomContainerIt++){
						if((roomContainerIt)->getName() == conditionObject){
							// check status
							if((roomContainerIt)->getStatus() == roomTriggerCondition.status){
								cout << roomTriggerIt->getPrint();
								return "stay";
							}
						}
					}*/
					vector<Container>::iterator gameContainerIt = gameContainers->begin();
					for(gameContainerIt = gameContainers->begin(); gameContainerIt != gameContainers->end(); gameContainerIt++){
						if((gameContainerIt)->getName() == conditionObject){
							// check status
							if((gameContainerIt)->getStatus() == roomTriggerCondition.status){
								cout << roomTriggerIt->getPrint();
								return "stay";
							}
						}
					}	
				}
			}
		}
		// iterate through borders to see if you can go the direction specified by command
		vector<Border>::iterator bord = roomBorders.begin();
		for(bord = roomBorders.begin(); bord != roomBorders.end(); bord++){
			if(playerCommand == "n"){
				if(bord->direction == "north"){
					return bord->name;
				}
			}
			if(playerCommand == "e"){
				if(bord->direction == "east"){
					return bord->name;
				}
			}
			if(playerCommand == "w"){
				if(bord->direction == "west"){
					return bord->name;
				}
			}
			if(playerCommand == "s"){
				if(bord->direction == "south"){
					return bord->name;
				}
			}

		}
		cout << "cannot move that direction" << endl;
	}
	else if(playerCommand == "i"){
		// display items in inv
		cout << "Inventory : ";
		if(Inventory->empty()){
			cout << " empty" << endl;
		}
		vector<Item>::iterator inv = Inventory->begin();

		for(inv = Inventory->begin(); inv != Inventory->end(); inv++){
			if(!(inv->isDeleted())){
				cout << (inv)->getName();
				cout << ' ';
			}
		}
		cout << endl;
		return "stay";
	}	
	else if(playerCommand == "open exit"){
		if(room->getType() == "exit"){
			cout << "Game Over" << endl;
			return "Game Over";
		}else{
			cout << "Ain't no exit here boi" << endl;
			return "stay";
		}
	}	
	else{
		string delim = " ";
		size_t pos = playerCommand.find(delim);
		string actionCommand = playerCommand.substr(0,pos);
		string item;
		string container;
		string creature;
		int count = 0;

		// if command is take, check if item exists in the room
		if(actionCommand == "take"){

			// get the item that user is trying to take
			item = playerCommand.erase(0, pos + delim.length());		
			
			// iterate through currRoom items and check if that item belongs to currRoom
			vector<Item>::iterator roomItemIt = roomItems.begin();				
			for(roomItemIt = roomItems.begin(); roomItemIt != roomItems.end(); roomItemIt++){
				if((roomItemIt)->getName() == item){

					if(!(roomItemIt->isDeleted())){
					// if the item is in the currRoom, add item to Inventory, take away item from currRoom vector
					Inventory->push_back(*roomItemIt);
					room->itemErase(count);
					cout << "Item " << item << " added to Inventory" << endl;
					return "stay";
					}
				}
				count++;
			}
			cout << item << " not found in room" << endl;
			return "stay";
		}

		// if command is open, check if container exists in room
		else if(actionCommand == "open"){
			int count = 0;
			// get the container that user is trying to open
			container = playerCommand.erase(0, pos + delim.length());
			vector<Container>::iterator roomContainerIt = roomContainer->begin();
			for(roomContainerIt = roomContainer->begin(); roomContainerIt != roomContainer->end(); roomContainerIt++){
				if(roomContainerIt->getName() == container){
					// if the container is in the room, display whats in the chest, add contents to room so you can take
					vector<Item> * roomContainerItems = roomContainerIt->getItem();
					vector<Item>::iterator roomContainerItemsIt = roomContainerItems->begin();
					//cout << roomContainerIt->getName();
					cout << container << " contains" ;

					for(roomContainerItemsIt = roomContainerItems->begin(); roomContainerItemsIt != roomContainerItems->end(); roomContainerItemsIt++){
						cout << roomContainerItemsIt->getName() << " " ;
						room->itemAdd(*roomContainerItemsIt);	
						//roomContainerItems->erase(roomContainerItemsIt);
						//cout << " blah" << endl;
						roomContainerIt->deleteItem(count);
						count++;				
					}
					roomContainerItems->clear();
					//cout << "blah" << endl;
					
				}
			}
			cout << endl;
			return "stay";
		}

		// if command requires something to do with the inventory
		else if(actionCommand == "read" || actionCommand == "drop" || actionCommand == "turn"){
			// get the item that user is trying to read
			item = playerCommand.erase(0, pos + delim.length());
			if(actionCommand == "turn"){
				pos = playerCommand.find(delim);
				item = playerCommand.erase(0, pos + delim.length());
			}
			// iterate through Inventory items and check if item is in Inventory
			vector<Item>::iterator inv = Inventory->begin();
			for(inv = Inventory->begin(); inv != Inventory->end(); inv++){
				if(inv->getName() == item){
					if(actionCommand == "read"){
						cout << "trying to read torch";
						// display the description of the item
						cout << inv->getWriting() << endl;;

						return "stay";
					}
					else if(actionCommand == "drop"){

						// change item ownership from Inventory to present currRoom
						cout << inv->getName();
						cout << " dropped" << endl;
						room->itemAdd(*inv);
						Inventory->erase(inv);
						return "stay";
					}
					else if(actionCommand == "turn"){
						turn_on commandOn = inv->getTurnOn();
						cout << "You activate the " << item << endl;
						cout << commandOn.print << endl;
						executeCommand(commandOn.action, room, gameItems, gameContainers, gameCreatures, Inventory);
						checkTrigger(room, gameItems, gameContainers, gameCreatures, Inventory);
						//executeCommand
						return "stay";
					}
				}
				else{
				cout << item;
				cout << " not in Inventory";
				}
			}

		}

		// if command is put, check if item exists in Invetory, check if container exists in room
		else if(actionCommand == "put"){
					
			// get rid of "put" from command
			pos = playerCommand.find(delim);
			playerCommand.erase(0, pos + delim.length());

			// get item
			pos = playerCommand.find(delim);
			item = playerCommand.substr(0,pos);

			//check if next word is "in"
			playerCommand.erase(0, pos + delim.length());
			pos = playerCommand.find(delim);

			if(playerCommand.substr(0,pos) == "in"){
				// get container
				playerCommand.erase(0, pos + delim.length());
				container = playerCommand;
				

				// iterate through Inventory items and check if item is in Inventory
				vector<Item>::iterator inv = Inventory->begin();
				for(inv = Inventory->begin(); inv != Inventory->end(); inv++){
					if(inv->getName() == item){

						// if item is in Inventory, check if container exists in currRoom
						vector<Container>::iterator roomContainerIt = roomContainer->begin();
						for(roomContainerIt = roomContainer->begin(); roomContainerIt != roomContainer->end(); roomContainerIt++){
							if(roomContainerIt->getName() == container){
								
								// check if container can accept item
								vector<string> contAccept = roomContainerIt->getAccept();
								vector<string>::iterator acceptIt = contAccept.begin();
								for(acceptIt = contAccept.begin(); acceptIt != contAccept.end(); acceptIt++){
									if((*acceptIt) == inv->getName()){
										roomContainerIt->addItem(*inv);
										Inventory->erase(inv);
										cout << "Item " << inv->getName() << " added to " << roomContainerIt->getName() << "."<< endl;
										checkTrigger(room, gameItems, gameContainers, gameCreatures, Inventory);
										return "stay";
									}
								}
							}
						}
					}
				}
			}
		}

		// if command is attack, check item exists in Inventory and if creature exists in room
		else if(actionCommand == "attack"){
			// get rid of "attack" from command
			pos = playerCommand.find(delim);
			playerCommand.erase(0, pos + delim.length());

			// get creature
			pos = playerCommand.find(delim);
			creature = playerCommand.substr(0,pos);

			// check if next word is "with"
			playerCommand.erase(0, pos + delim.length());
			pos = playerCommand.find(delim);

			if(playerCommand.substr(0, pos) == "with"){
				
				// get item
				playerCommand.erase(0, pos + delim.length());
				item = playerCommand;

				// iterate through Inventory items and check if item is in Inventory
				vector<Item>::iterator inv = Inventory->begin();
				for(inv = Inventory->begin(); inv != Inventory->end(); inv++){
					if(inv->getName() == item){
						// if item is in Inventory, check if creature exists in currRoom
						vector<Creature>::iterator b = roomCreature->begin();
						for(b = roomCreature->begin(); b != roomCreature->end(); b++){
							if(b->getName() == creature){
								//check if item is in creatures vulnerability list
								vector<Creature>::iterator cr = gameCreatures->begin();
								for(cr = gameCreatures->begin(); cr != gameCreatures->end(); cr++){
									if(cr->getName() == creature){
										vector<string> vulnerability_list = cr->getVulnerability();
										vector<string>::iterator vuln = vulnerability_list.begin();
										for(vuln = vulnerability_list.begin(); vuln != vulnerability_list.end(); vuln++){
											if(*vuln == item){
												//cout << "You assault the " << creature << " with " << item << endl;
												Attack attackElement = cr->getAttack();
												Condition attackCondition = attackElement.condition;
												//cout << attackCondition.object << endl;
												//cout << item << endl;
												// check condition of attack
												if(attackCondition.object == item){
													//cout << inv->getStatus() << endl;
													if(attackCondition.status == inv->getStatus()){
														cout << "You assault the " << creature << " with " << item << endl;
														cout << attackElement.print << endl;
														
														// implement the attack actions
														vector<string> attackAction = attackElement.action;
														vector<string>::iterator attackActionIt = attackAction.begin();
														for(attackActionIt = attackAction.begin(); attackActionIt != attackAction.end(); attackActionIt++){
															executeCommand(*attackActionIt, room, gameItems, gameContainers, gameCreatures, Inventory);
														}
														checkTrigger(room, gameItems, gameContainers, gameCreatures, Inventory);
														return "stay";
													}
													else{
														cout << "the item is not ready" << endl;
													}
												}
												else{
													cout << "Error" << endl;
													return "stay";
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		else if(actionCommand == "Update"){

			//cout << ((*Inventory)[0]).getStatus() << endl;

			string object;
			string status;

			// get rid of "update" from string
			pos = playerCommand.find(delim);
			playerCommand.erase(0, pos + delim.length());

			// get object
			pos = playerCommand.find(delim);
			object = playerCommand.substr(0,pos);

			// get rid of "to"
			playerCommand.erase(0, pos + delim.length());
			pos = playerCommand.find(delim);

			// get status
			playerCommand.erase(0, pos + delim.length());
			status = playerCommand;

			vector<Item>::iterator gameItemIt = gameItems->begin();
			for(gameItemIt = gameItems->begin(); gameItemIt != gameItems->end(); gameItemIt++){
				if(gameItemIt->getName() == object){
					gameItemIt->setStatus(status);
				}
			}

			vector<Item>::iterator inventoryIt = Inventory->begin();
			for(inventoryIt = Inventory->begin(); inventoryIt != Inventory->end(); inventoryIt++){
				if(inventoryIt->getName() == object){
					inventoryIt->setStatus(status);
				}
			}

			vector<Container>::iterator gameContainerIt = gameContainers->begin();
			for(gameContainerIt = gameContainers->begin(); gameContainerIt != gameContainers->end(); gameContainerIt++){
				if(gameContainerIt->getName() == object){
					gameContainerIt->setStatus(status);
				}
			}

			vector<Creature>::iterator gameCreatureIt = gameCreatures->begin();
			for(gameCreatureIt = gameCreatures->begin(); gameCreatureIt != gameCreatures->end(); gameCreatureIt++){
				if(gameCreatureIt->getName() == object){
					gameCreatureIt->setStatus(status);
				}
			}
		}

		else if(actionCommand == "Add"){

			string object;
			string destination;

			// get rid of "Add" from string
			pos = playerCommand.find(delim);
			playerCommand.erase(0, pos + delim.length());

			// get object
			pos = playerCommand.find(delim);
			object = playerCommand.substr(0,pos);

			// get rid of "to"
			playerCommand.erase(0, pos + delim.length());
			pos = playerCommand.find(delim);

			// get room or container name
			playerCommand.erase(0, pos + delim.length());
			destination = playerCommand;

			// check destination is room or object
			if(room->getName() == destination){
				// iterate through gameItems
				vector<Item>::iterator gameItemIt = gameItems->begin();
				for(gameItemIt = gameItems->begin(); gameItemIt != gameItems->end(); gameItemIt++){
					if(gameItemIt->getName() == object){
						room->itemAdd(*gameItemIt);
					}
				}
			}
			else{
				vector<Container>::iterator gameContainerIt = gameContainers->begin();
				for(gameContainerIt = gameContainers->begin(); gameContainerIt != gameContainers->end(); gameContainerIt++){
					if(gameContainerIt->getName() == destination){
						vector<Item>::iterator gameItemIt = gameItems->begin();
						for(gameItemIt = gameItems->begin(); gameItemIt != gameItems->end(); gameItemIt++){
							if(gameItemIt->getName() == object){
								gameContainerIt->addItem(*gameItemIt);
							}
						}
					}
				}
			}
		}
		else if(actionCommand == "Delete"){
			int count = 0;
			string object;
			// get rid of "Delete" from string
			pos = playerCommand.find(delim);
			playerCommand.erase(0, pos + delim.length());

			// get object
			pos = playerCommand.find(delim);
			object = playerCommand.substr(0,pos);

			vector<Item>::iterator gameItemIt = gameItems->begin();
			for(gameItemIt = gameItems->begin(); gameItemIt != gameItems->end(); gameItemIt++){
				if(gameItemIt->getName() == object){
					//gameItems->erase(gameItemIt);
				}
			}
			// Delete items from roomItems
			vector<Item>::iterator roomItemIt = roomItems.begin();
			for(roomItemIt = roomItems.begin(); roomItemIt != roomItems.end(); roomItemIt++){
				if(roomItemIt->getName() == object){
					room->itemErase(count);
					return "stay";
				}
				count++;
			}
			// Delete item from Inventory
			vector<Item>::iterator invItemIt = Inventory->begin();
			for(invItemIt = Inventory->begin(); invItemIt != Inventory->end(); invItemIt++){
				if(invItemIt->getName() == object){
					Inventory->erase(invItemIt);
					return "stay";
				}
			
			}
		}		
		else if(actionCommand == "Game"){
			string Over;

			// get rid of "Game" from string
			pos = playerCommand.find(delim);
			playerCommand.erase(0, pos + delim.length());

			// get Over
			pos = playerCommand.find(delim);
			Over = playerCommand.substr(0,pos);
			return "Game Over";
		}
		else{
			cout << "Error" << endl;
		}
				

	}

	
	



	/*
	vector<Item>::iterator itit = roomItems.begin();
	for(itit = roomItems.begin(); itit!= roomItems.end(); itit++){
		cout << itit->getName() << endl;
	}*/
	
	return "stay";
}




/*
string executeCommand(string playerCommand, Room room, vector<Item> gameItems, vector<Container> gameContainers, vector<Creature> gameCreatures, vector<Item> inventory){
	
	vector<Item> roomItem = room.getItems();
	vector<Container> roomContainer = room.getContainers();
	vector<Creature> roomCreature = room.getCreatures();
	vector<Border> roomBorders = room.getBorders();
		
	if(playerCommand == "n"){
		// iterate through borders to see if there is a north
		vector<Border>::iterator bord = roomBorders.begin();
		for(bord = roomBorders.begin(); bord != roomBorders.end(); bord++){
			if(bord->direction == "north"){
				return bord->name;
			}
		}
	}
	else if(playerCommand == "e"){
		// iterate through borders to see if there is a east
		vector<Border>::iterator bord = roomBorders.begin();
		for(bord = roomBorders.begin(); bord != roomBorders.end(); bord++){
			if(bord->direction == "east"){
				return bord->name;
			}
		}
	}
	else if(playerCommand == "s"){
		// iterate through borders to see if there is a south
		vector<Border>::iterator bord = roomBorders.begin();
		for(bord = roomBorders.begin(); bord != roomBorders.end(); bord++){
			if(bord->direction == "south"){
				return bord->name;
			}
		}
	}
	else if(playerCommand == "w"){
		// iterate through borders to see if there is a west
		vector<Border>::iterator bord = roomBorders.begin();
		for(bord = roomBorders.begin(); bord != roomBorders.end(); bord++){
			if(bord->direction == "west"){
				return bord->name;
			}
		}
	}
	else if(playerCommand == "i"){
		// display items in inv

		if(inventory.empty()){
			cout << "Inventory: empty" << endl;
		}
		vector<Item>::iterator inv = inventory.begin();
		for(inv = inventory.begin(); inv != inventory.end(); inv++){
			cout << inv->getName();
			cout << ',';
		}
		return "stay";

	}	
	else if(playerCommand == "open exit"){
		if(room.getType() == "exit"){
			cout << "Game Over" << endl;
			return "GameOver";
		}
	}
	else{
		string delim = " ";
		size_t pos = playerCommand.find(delim);
		string actionCommand = playerCommand.substr(0,pos);
		//cout << actionCommand << endl;
		string item;
		string container;
		string creature;
		
		// if command is take, check if item exists in room
		if(actionCommand == "take"){

			// get the item that user is trying to take
			item = playerCommand.erase(0, pos + delim.length());
			
			// iterate through room items and check if that item belongs to room
			vector<Item>::iterator i = roomItem.begin();				
			for(i = roomItem.begin(); i != roomItem.end(); i++){
				if(i->getName() == item){

					// if the item is in the room, add item to inventory, take away item from room vector
					inventory.push_back(*i);
					//cout << inventory[0].getName() << endl;
					roomItem.erase(i);
					//cout << inventory[0].getName() << endl;
					cout << "Item " << item << " added to inventory.";
					return "stay";
				}
			}
		}

		// if command is open, check if container exists in room
		else if(actionCommand == "open"){
			
			// get the container that user is trying to open 
			container = playerCommand.erase(0, pos + delim.length());
			
			// iterate through room containers and check if that container belongs to room
			vector<Container>::iterator a = roomContainer->begin();
			for(a = roomContainer->begin(); a != roomContainer->end(); a++){
				if(a->getName() == container){
					
					// if the container is in the room, display whats in chest, add contents to room so you can take it
					vector<string> container_items = a->getItem();
					vector<string>::iterator conItems = container_items.begin();
					vector<Item>::iterator gItem = gameItems.begin();
					cout << container;
					cout << " contains ";
					for(conItems = container_items.begin(); conItems != container_items.end(); conItems++){
						cout << *conItems;
						cout << ", ";
						for(gItem = gameItems.begin(); gItem != gameItems.end(); gItem++){
							if(gItem->getName() == *conItems){
								roomItem.push_back(*gItem);
								container_items.erase(conItems);
								return "stay";
							}
						}
					}
				}
			}
		}

		// if command is read, check if item exists in inventory
		else if(actionCommand == "read" || actionCommand == "drop" || actionCommand == "turn on"){

			// get the item that user is trying to read
			item = playerCommand.erase(0, pos + delim.length());

			// iterate through inventory items and check if item is in inventory
			vector<Item>::iterator inv = inventory.begin();
			for(inv = inventory.begin(); inv != inventory.end(); inv++){
				if(inv->getName() == item){
					if(actionCommand == "read"){

						// display the description of the item
						cout << inv->getDescription() << endl;
						return "stay";
					}
					else if(actionCommand == "drop"){

						// change item ownership from inventory to present room
						cout << inv->getName();
						cout << " dropped" << endl;
						roomItem.push_back(*inv);
						inventory.erase(inv);
						return "stay";
					}
					else if(actionCommand == "turn on"){
						turn_on commandOn = inv->getTurnOn();
						cout << commandOn.print << endl;
						updateItem(*inv, commandOn.action);
						//executeCommand
						return "stay";
					}
				}
			}
			cout << item;
			cout << " not in inventory";
			return "stay";
		}

		// if command is put, check if item exists in inventory, check if container exists in room
		else if(actionCommand == "put"){
			
			// get rid of "put" from command
			pos = playerCommand.find(delim);
			playerCommand.erase(0, pos + delim.length());

			// get item
			pos = playerCommand.find(delim);
			item = playerCommand.substr(0,pos);

			//check if next word is "in"
			playerCommand.erase(0, pos + delim.length());
			pos = playerCommand.find(delim);

			if(playerCommand.substr(0,pos) == "in"){
				// get container
				playerCommand.erase(0, pos + delim.length());
				container = playerCommand;
				

				// iterate through inventory items and check if item is in inventory
				vector<Item>::iterator inv = inventory.begin();
				for(inv = inventory.begin(); inv != inventory.end(); inv++){
					if(inv->getName() == item){

						// if item is in inventory, check if container exists in room
						vector<Container>::iterator a = roomContainer->begin();
						for(a = roomContainer->begin(); a != roomContainer->end(); a++){
							if(a->getName() == container){
								valid = 1;
							}
						}
					}
				}
			}
		}

		// if command is attack, check item exists in inventory and if creature exists in room and if item is within creatures vulnerability
		else if(actionCommand == "attack"){
			
			// get rid of "attack" from command
			pos = playerCommand.find(delim);
			playerCommand.erase(0, pos + delim.length());

			// get creature
			pos = playerCommand.find(delim);
			creature = playerCommand.substr(0,pos);

			// check if next word is "with"
			playerCommand.erase(0, pos + delim.length());
			pos = playerCommand.find(delim);

			if(playerCommand.substr(0, pos) == "with"){
				
				// get item
				playerCommand.erase(0, pos + delim.length());
				item = playerCommand;

				// iterate through inventory items and check if item is in inventory
				vector<Item>::iterator inv = inventory.begin();
				for(inv = inventory.begin(); inv != inventory.end(); inv++){
					if(inv->getName() == item){

						// if item is in inventory, check if creature exists in room
						vector<Creature>::iterator b = roomCreature->begin();
						for(b = roomCreature->begin(); b != roomCreature->end(); b++){
							if(b->getName() == creature){

								// check if item is in creatures vulnerability list
								vector<Creature>::iterator cr = gameCreatures.begin();
								for(cr = gameCreatures.begin(); cr != gameCreatures.end(); cr++){
									if(cr->getName() == creature){
										vector<string> vulnerability_list = cr->getVulnerability();
										vector<string>::iterator vuln = vulnerability_list.begin();
										for(vuln = vulnerability_list.begin(); vuln != vulnerability_list.end(); vuln++){
											if(*vuln == item){
												valid = 1;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}else{

		}



		
		/*
		while((pos = playerCommand.find(delim)) != std::string::npos){
			token = playerCommand.substr(0,pos);
			cout << token << endl;
			playerCommand.erase(0,pos + delim.length());
		}
		cout << playerCommand << endl;
		///*
	}
	if(valid == 1){
		cout << "valid" << endl;
		return "error";

	}else{
		cout << "notvalid" << endl;
		return "error";
	}
}*/