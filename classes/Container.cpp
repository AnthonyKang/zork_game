#include "Container.h"
#include <iostream>
#include <string>
using namespace std;

Container::Container(){}

string Container::getName(){
	return name;
}
void Container::setName(string name){
	this->name = name;
}

Status Container::getStatus(){
	return status;
}
void Container::setStatus(Status status){
	this->status = status;
}

string Container::getDescription(){
	return description;
}
void Container::setDescription(string description){
	this->description = description;
}

Item * Container::getAccept(){
	return accept;
}
void Container::setAccept(Item* accept){
	this->accept = accept;
}

Item * Container::getItem(){
	return item;
}
void Container::setItem(Item* item){
	this->item = item;
}

Triggers * Container::getTriggers(){
	return triggers;
}
void Container::setTriggers(Triggers* triggers){
	this->triggers = triggers;
}

