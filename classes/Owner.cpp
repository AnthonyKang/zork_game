#include "Owner.h"
#include <iostream>
#include <string>
using namespace std;

Owner::Owner(){}

string Owner::getOwner(){
	return owner;
}
void Owner::setOwner(string owner){
	this->owner = owner;
}

string Owner::getObject(){
	return object;
}
void Owner::setObject(string object){
	this->object = object;
}

void Owner::have(int has){
	this->has = has;
}