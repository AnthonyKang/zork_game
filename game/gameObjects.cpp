#include "gameObjects.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

gameObjects::gameObjects(){}

void gameObjects::setName(string newName){
	this->name = newName;
}
string gameObjects::getName(){
	return name;
}

void gameObjects::setStatus(string newStatus){
	this->status = newStatus;
}
string gameObjects::getStatus(){
	return status;
}

void gameObjects::setType(string newType){
	this->type = newType;
}
string gameObjects::getType(){
	return type;
}

void gameObjects::setDescription(string newDescription){
	this->description = newDescription;
}
string gameObjects::getDescription(){
	return description;
}

void gameObjects::setTrigger(Trigger trigger){
	(this->trigger).push_back(trigger);
}
vector<Trigger> gameObjects::getTrigger(){
	return trigger;
}