#include "Item.h"
#include <iostream>
#include <string>
using namespace std;

Item::Item(){}

string Item::getName(){
	return name;
}
void Item::setName(string name){
	this->name = name;
}

Status Item::getStatus(){
	return status;
}
void Item::setStatus(Status status){
	this->status = status;
}

string Item::getDescription(){
	return description;
}
void Item::setDescription(string description){
	this->description = description;
}

string Item::getOnFlag(){
	return onFlag;
}
void Item::setOnFlag(string onFlag){
	this->onFlag = onFlag;
}

string Item::getWriting(){
	return description;
}
void Item::setWriting(string description){
	this->description = description;
}

Triggers * Item::getTriggers(){
	return triggers;
}
void Item::setTriggers(Triggers* triggers){
	this->triggers = triggers;
}

void Item::turn_on(){
	this->on_off = 1;
	cout << this->onFlag << endl;
}

void Item::turn_off(){
	this->on_off = 0;
}