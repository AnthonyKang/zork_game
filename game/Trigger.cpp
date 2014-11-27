#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include "Trigger.h"
#include "../rapidxml/rapidxml.hpp"
#include "../rapidxml/rapidxml_utils.hpp"
#include "../rapidxml/rapidxml_print.hpp"

using namespace std;
using namespace rapidxml;

Trigger::Trigger(xml_node<> * triggerTag){
	
	xml_node<> * triggerElement = NULL;

	for(triggerElement = triggerTag->first_node(); triggerElement; triggerElement = triggerElement->next_sibling()){
		if(strcmp(triggerElement->name(),"type") == 0){
			type = triggerElement->value();
		}
		if(strcmp(triggerElement->name(),"print") == 0){
			print = triggerElement->value();
		}
		if(strcmp(triggerElement->name(),"command") == 0){
			command = triggerElement->value();
		}
		if(strcmp(triggerElement->name(),"action") == 0){
			action.push_back(triggerElement->value());
		}
		if(strcmp(triggerElement->name(),"condition") == 0){
			xml_node<> * conditionElements = NULL;
			for(conditionElements = triggerElement->first_node(); conditionElements; conditionElements= conditionElements->next_sibling()){
				if(strcmp(conditionElements->name(),"object") == 0){
					condition.object = conditionElements->value();
				}
				if(strcmp(conditionElements->name(),"status") == 0){
					condition.status = conditionElements->value();
				}
				if(strcmp(conditionElements->name(),"has") == 0){
					condition.has = conditionElements->value();
				}
				if(strcmp(conditionElements->name(),"owner") == 0){
					condition.owner = conditionElements->value();
				}
			}
		}
	}

}

void Trigger::setType(string type){
	this->type = type;
}
string Trigger::getType(){
	return type;
}

void Trigger::setPrint(string print){
	this->print = print;
}
string Trigger::getPrint(){
	return print;
}

void Trigger::setCommand(string command){
	this->command = command;
}
string Trigger::getCommand(){
	return command;
}

void Trigger::setAction(string action){
	(this->action).push_back(action);
}
vector<string> Trigger::getAction(){
	return action;
}

void Trigger::setCondition(string object, string status, string has, string owner){
	Condition condition;
	condition.object = object;
	condition.status = status;
	condition.has = has;
	condition.owner = owner;
	this->condition = condition;
}
Condition Trigger::getCondition(){
	return condition;
}

