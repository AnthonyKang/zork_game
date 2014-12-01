#ifndef CONTAINER_H_
#define CONTAINER_H_
#include <string>
#include <vector>
#include <iostream>
#include "gameObjects.h"
#include "Item.h"
#include "../rapidxml/rapidxml.hpp"
#include "../rapidxml/rapidxml_utils.hpp"
#include "../rapidxml/rapidxml_print.hpp"

using namespace std;
using namespace rapidxml;

class Container: public gameObjects{
private:
	vector<string> accept;
	vector<Item> item;
	//vector<Trigger> trigger;

public:
	Container(xml_node<> * containerTag, vector<Item> itemList);
	vector<Item> * getItem();
	vector<string> getAccept();
	void addItem(Item);
	void deleteItem(int);

};
#endif