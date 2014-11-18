#include "Triggers.h"
#include <iostream>
#include <string>
using namespace std;


string Triggers::getType(){
	return type;
}
void Triggers::setType(string type){
	this->type = type;
}