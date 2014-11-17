#include "Room.h"
#include <iostream>
#include <string>
using namespace std;

Room::Room(){}

string Room::getName(){
	return name;
}
void Room::setName(string room_name){
	name = room_name;
}

Status Room::getStatus(){
	return status;
}
void Room::setStatus(Status status){
	this->status = status;
}

string Room::getType(){
	return type;
}
void Room::setType(string type){
	this->type = type;
}

string Room::getDescription(){
	return description;
}
void Room::setDescription(string description){
	this->description = description;
}

string * Room::getBorder(){
	return border; 
}
void Room::setBorder(string* border){
	this->border = border;
}

Container * Room::getContainer(){
	return container;
}
void Room::setContainer(Container* container){
	this->container = container;
}

Item * Room::getItem(){
	return item;
}
void Room::setItem(Item* item){
	this->item = item;
}

Creature * Room::getCreature(){
	return creature;
}
void Room::setCreature(Creature* creature){
	this->creature = creature;
}

Triggers * Room::getTriggers(){
	return triggers;
}
void Room::setTriggers(Triggers* triggers){
	this->triggers = triggers;
}