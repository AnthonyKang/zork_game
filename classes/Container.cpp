#include "Container.h"
#include <iostream>
#include <string>
#include <vector>
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

string Container::getConditionSatisfy(){
	return conditionSatisfy;
}
void Container::setConditionSatisfy(string print){
	this->conditionSatisfy = print;
}

vector<string> Container::getAccept(){
	return accept_list;
}
void Container::setAccept(string accept){
	(this->accept_list).push_back(accept);
}

Item * Container::getItem(){
	return item;
}
void Container::setItem(Item* item){
	this->item = item;
}

vector<Triggers> Container::getTriggers(){
	return triggers;
}
void Container::setTriggers(Triggers triggers){
	(this->triggers).push_back(triggers);
}

vector<Item> Container::getItemList(){
	return item_list;
}

void Container::setItemList(Item item){
	(this->item_list).push_back(item);
}
