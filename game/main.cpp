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
	//cout << map->name() << endl;

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
		if(strcmp(mapElement->name(),"container") == 0){
			Container newContainer = Container(mapElement);
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

	vector<Room>::iterator r = gameRooms.begin();	
	/*
	for(r = gameRooms.begin(); r != gameRooms.end(); r++){
		cout << r->getName() << endl;
	}*/
	//cout << "hui";

	vector<Item>::iterator i = gameItems.begin();
	/*
	for(i = gameItems.begin(); i != gameItems.end(); i++){
		cout << i->getName() << endl;
		//cout << "hi" << endl;
	}*/
	vector<Container>::iterator a = gameContainers.begin();
	/*
	for(a = gameContainers.begin(); a != gameContainers.end(); a++){
		cout << a->getName() << endl;
		//cout << "hi" << endl;
	}*/

	vector<Creature>::iterator b = gameCreatures.begin();
	
	/*for(b = gameCreatures.begin(); b != gameCreatures.end(); b++){
		cout << b->getName() << endl;
		//cout << "hi" << endl;
	}*/

	
	// Initialize Game Loop
	int gameOver = 0;
	string roomName = gameRooms[0].getName();
	cout << roomName << endl;
	int roomFind = 0;
	int roomCount = 0;
	
	while(!gameOver){
		roomCount = 0;
		for(r = gameRooms.begin(); r != gameRooms.end(); r++){
			if(r->getName() == roomName){
				roomFind = roomCount;
			}
			roomCount++;
		}
		//roomName = loadRoom(gameRooms[roomFind], gameItems, gameContainers, gameCreatures, Inventory);
		Room currRoom = gameRooms[roomFind];
		cout << currRoom.getDescription() << endl;
		string command;
		int in_room = 1;
		string stay = "";
		while(in_room){
			getline(cin,command);
						
			cout << command << endl;
	
			string commands[6] = {"n","s","e","w","i","open exit"};
			int valid = 0;
			int error = 1;
			int has_check = 0;
			int ret = 0;

			//cout << currRoom.getName();

			vector<Item> currRoomItem = currRoom.getItems();
			vector<Container> currRoomContainer = currRoom.getContainers();
			vector<Creature> currRoomCreature = currRoom.getCreatures();
			vector<Border> currRoomBorders = currRoom.getBorders();
			vector<Trigger> currRoomTrigger = currRoom.getTrigger();

			//currRoomItem.erase(currRoomItem.begin());
			
			//cout << currRoomItem[0].getName();			
			if(command == "n" || command == "s" || command == "e" || command == "w"){
				// check trigger
				
				vector<Trigger>::iterator trigg = currRoomTrigger.begin();
				for(trigg = currRoomTrigger.begin(); trigg != currRoomTrigger.end(); trigg++){
					if(trigg->getCommand() == command){
						Condition triggCondition = trigg->getCondition();
						string has = triggCondition.has;
						if(triggCondition.owner == "inventory"){
							vector<Item>::iterator inv = Inventory.begin();
							if(has == "yes"){
								for(inv = Inventory.begin(); inv != Inventory.end(); inv++){
									if(inv->getName() == triggCondition.object){
										cout << trigg->getPrint() << endl;
									}
								}
							}else if(has == "no"){
								for(inv = Inventory.begin(); inv != Inventory.end(); inv++){
									if(inv->getName() == triggCondition.object){
										has_check = 1;
									}
								}
								if(!has_check || Inventory.empty()){
									cout << trigg->getPrint() << endl;
									ret = 1;
								}
							}
						}
						else{
							// get the object of condition
							string conditionObject = triggCondition.object;

							// find the object in items, creatures, or containers
							vector<Item>::iterator currRoomItemIt = currRoomItem.begin();
							for(currRoomItemIt = currRoomItem.begin(); currRoomItemIt != currRoomItem.end(); currRoomItemIt++){
								if(currRoomItemIt->getName() == conditionObject){
									// check status
									if(currRoomItemIt->getStatus() == triggCondition.status){
										cout << trigg->getPrint();
										ret = 1;
									}
								}
							}
							vector<Container>::iterator currRoomItemCon = currRoomContainer.begin();
							for(currRoomItemCon = currRoomContainer.begin(); currRoomItemCon != currRoomContainer.end(); currRoomItemCon++){
								if(currRoomItemCon->getName() == conditionObject){
									// check status
									if(currRoomItemCon->getStatus() == triggCondition.status){
										cout << trigg->getPrint();
										ret = 1;
									}
								}
							}
						}
					}
				}
				cout << ret << endl;
				if(!ret){			

					// iterate through borders to see if there is a north
					vector<Border>::iterator bord = currRoomBorders.begin();
					for(bord = currRoomBorders.begin(); bord != currRoomBorders.end(); bord++){
						if(command == "n"){
							if(bord->direction == "north"){
								stay = bord->name;
								error = 0;
								in_room = 0;
								//cout << bord->name;
							}
						}
						if(command == "e"){
							if(bord->direction == "east"){
								stay = bord->name;
								error = 0;
								in_room = 0;
								//cout << bord->name;
							}
						}
						if(command == "w"){
							if(bord->direction == "west"){
								stay = bord->name;
								error = 0;
								in_room = 0;
								//cout << bord->name;
							}
						}
						if(command == "s"){
							if(bord->direction == "south"){
								stay = bord->name;
								error = 0;
								in_room = 0;
								//cout << bord->name;
							}
						}
					}
					if(error == 1){
						cout << "cannot move that direction" << endl;
					}
				}
			}/*
			else if(command == "e"){
				// check trigger
				
				vector<Trigger>::iterator trigg = currRoomTrigger.begin();
				for(trigg = currRoomTrigger.begin(); trigg != currRoomTrigger.end(); trigg++){
					if(trigg->getCommand() == "e"){
						Condition triggCondition = trigg->getCondition();
						string has = triggCondition.has;
						if(triggCondition.owner == "inventory"){
							vector<Item>::iterator inv = Inventory.begin();
							if(has == "yes"){
								for(inv = Inventory.begin(); inv != Inventory.end(); inv++){
									if(inv->getName() == triggCondition.object){
										cout << trigg->getPrint() << endl;
									}
								}
							}else if(has == "no"){
								for(inv = Inventory.begin(); inv != Inventory.end(); inv++){
									if(inv->getName() == triggCondition.object){
										has_check = 1;
									}
								}
								if(!has_check || Inventory.empty()){
									cout << trigg->getPrint() << endl;
									ret = 1;
								}
							}
						}
					}
				}
				if(!ret){
					// iterate through borders to see if there is a east
					vector<Border>::iterator bord = currRoomBorders.begin();
					for(bord = currRoomBorders.begin(); bord != currRoomBorders.end(); bord++){
						if(bord->direction == "east"){
							stay = bord->name;
							error = 0;
						}
					}
					if(error ==1){
						cout << "cannot move east" << endl;
					}
				}
			}
			else if(command == "s"){
				vector<Trigger>::iterator trigg = currRoomTrigger.begin();
				for(trigg = currRoomTrigger.begin(); trigg != currRoomTrigger.end(); trigg++){
					if(trigg->getCommand() == "e"){
						Condition triggCondition = trigg->getCondition();
						string has = triggCondition.has;
						if(triggCondition.owner == "inventory"){
							vector<Item>::iterator inv = Inventory.begin();
							if(has == "yes"){
								for(inv = Inventory.begin(); inv != Inventory.end(); inv++){
									if(inv->getName() == triggCondition.object){
										cout << trigg->getPrint() << endl;
									}
								}
							}else if(has == "no"){
								for(inv = Inventory.begin(); inv != Inventory.end(); inv++){
									if(inv->getName() == triggCondition.object){
										has_check = 1;
									}
								}
								if(!has_check || Inventory.empty()){
									cout << trigg->getPrint() << endl;
									ret = 1;
								}
							}
						}
					}
				}
				if(!ret){
					// iterate through borders to see if there is a south
					vector<Border>::iterator bord = currRoomBorders.begin();
					for(bord = currRoomBorders.begin(); bord != currRoomBorders.end(); bord++){
						if(bord->direction == "south"){
							stay = bord->name;
						}
					}
					if(error == 1){
						cout << "cannot move south" << endl;
					}
				}
			}
			else if(command == "w"){
				vector<Trigger>::iterator trigg = currRoomTrigger.begin();
				for(trigg = currRoomTrigger.begin(); trigg != currRoomTrigger.end(); trigg++){
					if(trigg->getCommand() == "e"){
						Condition triggCondition = trigg->getCondition();
						string has = triggCondition.has;
						if(triggCondition.owner == "inventory"){
							vector<Item>::iterator inv = Inventory.begin();
							if(has == "yes"){
								for(inv = Inventory.begin(); inv != Inventory.end(); inv++){
									if(inv->getName() == triggCondition.object){
										cout << trigg->getPrint() << endl;
									}
								}
							}else if(has == "no"){
								for(inv = Inventory.begin(); inv != Inventory.end(); inv++){
									if(inv->getName() == triggCondition.object){
										has_check = 1;
									}
								}
								if(!has_check || Inventory.empty()){
									cout << trigg->getPrint() << endl;
									ret = 1;
								}
							}
						}
					}
				}
				if(!ret){
					// iterate through borders to see if there is a west
					vector<Border>::iterator bord = currRoomBorders.begin();
					for(bord = currRoomBorders.begin(); bord != currRoomBorders.end(); bord++){
						if(bord->direction == "west"){
							stay = bord->name;
						}
					}
				}
			}*/
			else if(command == "i"){
				// display items in inv

				if(Inventory.empty()){
					cout << "Inventory: empty" << endl;
				}
				vector<Item>::iterator inv = Inventory.begin();
				for(inv = Inventory.begin(); inv != Inventory.end(); inv++){
					cout << inv->getName();
					cout << ',';
				}
				stay = "stay";

			}	
			else if(command == "open exit"){
				if(currRoom.getType() == "exit"){
					cout << "Game Over" << endl;
					stay = "GameOver";
				}
			}
			else{
				string delim = " ";
				size_t pos = command.find(delim);
				string actionCommand = command.substr(0,pos);
				//cout << actionCommand << endl;
				string item;
				string container;
				string creature;
				
				// if command is take, check if item exists in currRoom
				if(actionCommand == "take"){

					// get the item that user is trying to take
					item = command.erase(0, pos + delim.length());
					
					// iterate through currRoom items and check if that item belongs to currRoom
					vector<Item>::iterator roomItemIt = currRoomItem.begin();				
					for(roomItemIt = currRoomItem.begin(); roomItemIt != currRoomItem.end(); roomItemIt++){
						if(roomItemIt->getName() == item){

							// if the item is in the currRoom, add item to Inventory, take away item from currRoom vector
							Inventory.push_back(*roomItemIt);
							//cout << Inventory[0].getName() << endl;
							currRoomItem.erase(currRoomItem.begin());
							//cout << Inventory[0].getName() << endl;
							cout << "Item " << item << " added to Inventory.";
							stay = "stay";
							break;
						}else{
							cout << item << " not found in room" << endl;
						}
					}
				}

				// if command is open, check if container exists in currRoom
				else if(actionCommand == "open"){
					
					// get the container that user is trying to open 
					container = command.erase(0, pos + delim.length());
					
					// iterate through currRoom containers and check if that container belongs to currRoom
					vector<Container>::iterator a = currRoomContainer.begin();
					for(a = currRoomContainer.begin(); a != currRoomContainer.end(); a++){
						if(a->getName() == container){
							
							// if the container is in the currRoom, display whats in chest, add contents to currRoom so you can take it
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
										currRoomItem.push_back(*gItem);
										container_items.erase(conItems);
										stay = "stay";
									}
								}
							}
						}
					}
				}

				// if command is read, check if item exists in Inventory
				else if(actionCommand == "read" || actionCommand == "drop" || actionCommand == "turn on"){

					// get the item that user is trying to read
					item = command.erase(0, pos + delim.length());

					// iterate through Inventory items and check if item is in Inventory
					vector<Item>::iterator inv = Inventory.begin();
					for(inv = Inventory.begin(); inv != Inventory.end(); inv++){
						if(inv->getName() == item){
							if(actionCommand == "read"){

								// display the description of the item
								cout << inv->getDescription() << endl;
								stay = "stay";
							}
							else if(actionCommand == "drop"){

								// change item ownership from Inventory to present currRoom
								cout << inv->getName();
								cout << " dropped" << endl;
								currRoomItem.push_back(*inv);
								Inventory.erase(inv);
								stay = "stay";
							}
							else if(actionCommand == "turn on"){
								turn_on commandOn = inv->getTurnOn();
								cout << commandOn.print << endl;
								updateItem(*inv, commandOn.action);
								//executeCommand
								stay = "stay";
							}
						}
					}
					cout << item;
					cout << " not in Inventory";
					stay = "stay";
				}

				// if command is put, check if item exists in Inventory, check if container exists in currRoom
				else if(actionCommand == "put"){
					
					// get rid of "put" from command
					pos = command.find(delim);
					command.erase(0, pos + delim.length());

					// get item
					pos = command.find(delim);
					item = command.substr(0,pos);

					//check if next word is "in"
					command.erase(0, pos + delim.length());
					pos = command.find(delim);

					if(command.substr(0,pos) == "in"){
						// get container
						command.erase(0, pos + delim.length());
						container = command;
						

						// iterate through Inventory items and check if item is in Inventory
						vector<Item>::iterator inv = Inventory.begin();
						for(inv = Inventory.begin(); inv != Inventory.end(); inv++){
							if(inv->getName() == item){

								// if item is in Inventory, check if container exists in currRoom
								vector<Container>::iterator a = currRoomContainer.begin();
								for(a = currRoomContainer.begin(); a != currRoomContainer.end(); a++){
									if(a->getName() == container){
										valid = 1;
									}
								}
							}
						}
					}
				}

				// if command is attack, check item exists in Inventory and if creature exists in currRoom and if item is within creatures vulnerability
				else if(actionCommand == "attack"){
					
					// get rid of "attack" from command
					pos = command.find(delim);
					command.erase(0, pos + delim.length());

					// get creature
					pos = command.find(delim);
					creature = command.substr(0,pos);

					// check if next word is "with"
					command.erase(0, pos + delim.length());
					pos = command.find(delim);

					if(command.substr(0, pos) == "with"){
						
						// get item
						command.erase(0, pos + delim.length());
						item = command;

						// iterate through Inventory items and check if item is in Inventory
						vector<Item>::iterator inv = Inventory.begin();
						for(inv = Inventory.begin(); inv != Inventory.end(); inv++){
							if(inv->getName() == item){

								// if item is in Inventory, check if creature exists in currRoom
								vector<Creature>::iterator b = currRoomCreature.begin();
								for(b = currRoomCreature.begin(); b != currRoomCreature.end(); b++){
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
							
			}
			//cout << "test" << endl;
		}
		cout << stay;
		if(stay != "stay"){
			roomName = stay;
			//cout << roomName << endl;
		}
	}
	if(roomName == "GameOver"){
		gameOver = 1;
	}
}

