#include "Creature.h"
#include <iostream>
#include <string>
#include <vector>
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

vector<string> Creature::getVulnerabilityList(){
	return vulnerabilityList;
}
void Creature::setVulnerabilityList(string vulnerability){
	(this->vulnerabilityList).push_back(vulnerability);
}

vector<Triggers> Creature::getTriggers(){
	return triggers;
}
void Creature::setTriggers(Triggers triggers){
	(this->triggers).push_back(triggers);
}

string Creature::getConditionSatisfy(){
	return conditionSatisfy;
}
void Creature::setConditionSatisfy(string print){
	this->conditionSatisfy = print;
}

Attack Creature::getAttack(){
	return attack;
}

void Creature::setAttack(Attack attack){
	this->attack = attack;
}