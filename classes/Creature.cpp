#include "Creature.h"
#include <iostream>
#include <string>
using namespace std;

Creature::Creature(){}

string Creature::getName(){
	return name;
}
void Creature::setName(string name){
	this->name = name;
}

Status Creature::getStatus(){
	return status;
}
void Creature::setStatus(Status status){
	this->status = status;
}

string Creature::getDescription(){
	return description;
}
void Creature::setDescription(string description){
	this->description = description;
}

Item * Creature::getVulnerability(){
	return vulnerability;
}
void Creature::setVulnerability(Item* vulnerability){
	this->vulnerability = vulnerability;
}

Triggers * Creature::getTriggers(){
	return triggers;
}
void Creature::setTriggers(Triggers* triggers){
	this->triggers = triggers;
}