#ifndef UTILS_H_
#define UTILS_H_
#include "Room.h"
#include <vector>
#include "../rapidxml/rapidxml.hpp"
#include "../rapidxml/rapidxml_utils.hpp"
#include "../rapidxml/rapidxml_print.hpp"
using namespace std;
using namespace rapidxml;
Room makeRoom(int, xml_node<> *);
Item makeItem(xml_node<> *);
Container makeContainer(xml_node<> *, vector<Item>);
Creature makeCreature(xml_node<> *);
#endif