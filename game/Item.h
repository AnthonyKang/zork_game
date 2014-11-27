#ifndef ITEM_H_
#define ITEM_H_
#include <string>
#include <vector>
#include <iostream>
#include "gameObjects.h"

#include "../rapidxml/rapidxml.hpp"
#include "../rapidxml/rapidxml_utils.hpp"
#include "../rapidxml/rapidxml_print.hpp"

using namespace std;
using namespace rapidxml;

typedef struct _turn_on{
	string print;
	string action;
} turn_on;

class Item: public gameObjects{
private:
	string writing;
	turn_on turnOn;

public:
	Item(xml_node<> * itemTag);

	void setWriting(string);
	string getWriting();

	void setTurnOn(string, string);
	turn_on getTurnOn();
};
#endif