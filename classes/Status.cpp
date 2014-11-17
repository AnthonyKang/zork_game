#include "Status.h"
#include <iostream>
#include <string>
using namespace std;

Status::Status(){}

string Status::getStatus(){
	return status;
}
void Status::setStatus(string status){
	this->status = status;
}

string Status::getObject(){
	return object;
}
void Status::setObject(string object){
	this->object = object;
}
