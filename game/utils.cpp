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


string loadRoom(Room room, vector<Item> gameItems, vector<Container> gameContainers, vector<Creature> gameCreatures, vector<Item> inventory){
	cout << room.getDescription() << endl;
	string command;
	int in_room = 1;
	string stay = "";
	while(in_room){
		getline(cin,command);
		/*
		if(commandValid(command, room, gameItems, gameContainers, gameCreatures, inventory)){
			//executeCommand();
		}*/
		stay = executeCommand(command, room, gameItems, gameContainers, gameCreatures, inventory);
		if(stay != "stay"){
			return stay;
		}
	}
	
}

string executeCommand(string playerCommand, Room room, vector<Item> gameItems, vector<Container> gameContainers, vector<Creature> gameCreatures, vector<Item> inventory){
	cout << playerCommand << endl;
	string commands[6] = {"n","s","e","w","i","open exit"};
	int valid = 0;

	vector<Item> roomItem = room.getItems();
	vector<Container> roomContainer = room.getContainers();
	vector<Creature> roomCreature = room.getCreatures();
	vector<Border> roomBorders = room.getBorders();
	

	//cout << roomItem[0].getName();
	/*for(int i = 0; i < 6; i++){
		if(playerCommand == commands[i]){
			valid = 1;
		}
	}*/
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
			vector<Container>::iterator a = roomContainer.begin();
			for(a = roomContainer.begin(); a != roomContainer.end(); a++){
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
						vector<Container>::iterator a = roomContainer.begin();
						for(a = roomContainer.begin(); a != roomContainer.end(); a++){
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
						vector<Creature>::iterator b = roomCreature.begin();
						for(b = roomCreature.begin(); b != roomCreature.end(); b++){
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
		*/
	}
	if(valid == 1){
		cout << "valid" << endl;
		return "error";

	}else{
		cout << "notvalid" << endl;
		return "error";
	}
}