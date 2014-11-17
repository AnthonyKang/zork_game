#include "Conditions.h"
#include <iostream>
#include <string>
using namespace std;

Conditions::Conditions(){}

Status Conditions::getStatus(){
	return status;
}
void Conditions::setStatus(Status status){
	this->status = status;
}

Owner Conditions::getOwner(){
	return owner;
}
void Conditions::setOwner(Owner owner){
	this->owner = owner;
}
