#ifndef CONTAINER_H_
#define CONTAINER_H_
#include <string>
#include <vector>
#include <iostream>
#include "gameObjects.h"
#include "../rapidxml/rapidxml.hpp"
#include "../rapidxml/rapidxml_utils.hpp"
#include "../rapidxml/rapidxml_print.hpp"

using namespace std;
using namespace rapidxml;

class Container: public gameObjects{
private:
	vector<string> accept;
	vector<string> item;
	vector<Trigger> trigger;

public:
	Container(xml_node<> * containerTag);
	vector<string> getItem();

};
#endif