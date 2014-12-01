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

Container::Container(xml_node<> * containerTag, vector<Item> itemList){

	xml_node<> * containerElement = NULL;
	vector<Item>::iterator i = itemList.begin();
	deleted = 0;
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
			for(i = itemList.begin(); i != itemList.end(); i++){
				//cout << i->getName() << endl;
				if(((i)->getName()) == (containerElement->value())){
					item.push_back(*i);
				}
			}
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

vector<Item> * Container::getItem(){
	return &item;
}
vector<string> Container::getAccept(){
	return accept;
}
void Container::addItem(Item newitem){
	item.push_back(newitem);
}
void Container::deleteItem(int location){
	item.erase(item.begin() + location);
}