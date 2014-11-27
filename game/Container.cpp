#include <iostream>
#include <string>
#include <vector>
#include "Container.h"
#include "../rapidxml/rapidxml.hpp"
#include "../rapidxml/rapidxml_utils.hpp"
#include "../rapidxml/rapidxml_print.hpp"
#include <cstring>

using namespace std;
using namespace rapidxml;

Container::Container(xml_node<> * containerTag){

	xml_node<> * containerElement = NULL;

	for(containerElement = containerTag->first_node(); containerElement; containerElement = containerElement->next_sibling()){
		if(strcmp(containerElement->name(),"name") == 0){
			name = containerElement->value();
		}
		if(strcmp(containerElement->name(),"status") == 0){
			status = containerElement->value();
		}
		if(strcmp(containerElement->name(),"description") == 0){
			description = containerElement->value();
		}
		if(strcmp(containerElement->name(),"accept") == 0){
			accept.push_back(containerElement->value());
		}
		if(strcmp(containerElement->name(),"item") == 0){
			item.push_back(containerElement->value());
		}
		if(strcmp(containerElement->name(),"trigger") == 0){
			xml_node<> * triggerElements = NULL;
			for(triggerElements = containerElement->first_node(); triggerElements; triggerElements = triggerElements->next_sibling()){
				Trigger newTrigger = Trigger(containerElement);
				trigger.push_back(newTrigger);
			}
		}
	}

}

vector<string> Container::getItem(){
	return item;
}