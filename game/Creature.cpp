#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include "Creature.h"
#include "../rapidxml/rapidxml.hpp"
#include "../rapidxml/rapidxml_utils.hpp"
#include "../rapidxml/rapidxml_print.hpp"

using namespace std;
using namespace rapidxml;

Creature::Creature(xml_node<> * creatureTag){

	xml_node<> * creatureElement = NULL;

	for(creatureElement = creatureTag->first_node(); creatureElement; creatureElement = creatureElement->next_sibling()){
		if(strcmp(creatureElement->name(),"name") == 0){
			name = creatureElement->value();
		}
		if(strcmp(creatureElement->name(),"status") == 0){
			status = creatureElement->value();
		}
		if(strcmp(creatureElement->name(),"description") == 0){
			description = creatureElement->value();
		}
		if(strcmp(creatureElement->name(),"vulnerability") == 0){
			vulnerability.push_back(creatureElement->value());
		}
		if(strcmp(creatureElement->name(),"attack") == 0){
			xml_node<> * attackElement = NULL;
			for(attackElement = creatureElement->first_node(); attackElement; attackElement = attackElement->next_sibling()){
				if(strcmp(creatureElement->name(),"condition") == 0){
					xml_node<> * conditionElement = NULL;
					Condition condition;
					for(conditionElement = attackElement->first_node(); conditionElement; conditionElement = conditionElement->next_sibling()){
						if(strcmp(creatureElement->name(),"object") == 0){
							condition.object = conditionElement->value();
						}
						if(strcmp(creatureElement->name(),"status") == 0){
							condition.status = conditionElement->value();
						}					
					} 
					attack.condition = condition;
				}
				if(strcmp(creatureElement->name(),"print") == 0){
					attack.print = attackElement->value();
				}
				if(strcmp(creatureElement->name(),"action") == 0){
					attack.action.push_back(attackElement->value());
				}
			}
		}
		if(strcmp(creatureElement->name(),"trigger") == 0){
			Trigger newTrigger = Trigger(creatureElement);
			trigger.push_back(newTrigger);
		}

	}


}

void Creature::setVulnerability(string vulnerability){
	(this->vulnerability).push_back(vulnerability);
}
vector<string> Creature::getVulnerability(){
	return vulnerability;
}

void Creature::setAttackList(Condition, string, vector<string>){

}
Attack Creature::getAttackList(){

}