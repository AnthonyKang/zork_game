#include <iostream>
#include <string>
#include <vector>
#include "Item.h"
#include "../rapidxml/rapidxml.hpp"
#include "../rapidxml/rapidxml_utils.hpp"
#include "../rapidxml/rapidxml_print.hpp"
#include <cstring>

using namespace std;
using namespace rapidxml;

Item::Item(xml_node<> * itemTag){
	deleted = 0;
	xml_node<> *itemElement = NULL;

	for(itemElement = itemTag->first_node(); itemElement; itemElement = itemElement->next_sibling()){
		if(strcmp(itemElement->name(),"name") == 0){
			name = itemElement->value();
		}
		if(strcmp(itemElement->name(),"status") == 0){
			status = itemElement->value();
		}
		if(strcmp(itemElement->name(),"type") == 0){
			type = itemElement->value();
		}
		if(strcmp(itemElement->name(),"description") == 0){
			description = itemElement->value();
		}
		if(strcmp(itemElement->name(),"writing") == 0){
			writing = itemElement->value();
		}
		if(strcmp(itemElement->name(),"turnon") == 0){
			xml_node<> * turnOnElement = itemElement->first_node();
			turnOn.print = turnOnElement->value();
			turnOn.action = (turnOnElement->next_sibling())->value();
		}
	}
}

void Item::setWriting(string newWriting){
	this->writing = newWriting;
}
string Item::getWriting(){
	return writing;
}

void Item::setTurnOn(string print, string action){
	turnOn.print = print;
	turnOn.action = action;
}
turn_on Item::getTurnOn(){
	return turnOn;
}