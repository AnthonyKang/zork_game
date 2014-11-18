#include "Attack.h"
#include <iostream>
#include <string>
using namespace std;

Attack::Attack(){}

string Attack::getObject(){
	return object;
}
void Attack::setObject(string object){
	this->object = object;
}

string Attack::getPrint(){
	return print;
}
void Attack::setPrint(string print){
	this->print = print;
}

string Attack::getStatus(){
	return status;
}
void Attack::setStatus(string status){
	this->status = status;
}