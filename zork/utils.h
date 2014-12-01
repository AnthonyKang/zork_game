#ifndef UTILS_H_
#define UTILS_H_
#include <iostream>
#include <string>
#include <vector>
#include "../rapidxml/rapidxml.hpp"
#include "../rapidxml/rapidxml_utils.hpp"
#include "../rapidxml/rapidxml_print.hpp"
#include "Container.h"
#include "gameObjects.h"
#include "Creature.h"
#include "Trigger.h"
#include "Item.h"
#include "Room.h"
#include <cstring>

using namespace std;
using namespace rapidxml;
void updateItem(Item , string);
void updateContainer(Container , string);
string loadRoom(Room *, vector<Item> *, vector<Container> *, vector<Creature> *, vector<Item> *);
string executeCommand(string, Room *, vector<Item> *, vector<Container> *, vector<Creature> *, vector<Item> *);
void checkTrigger(Room *, vector<Item> *, vector<Container> *, vector<Creature> *, vector<Item> *);





#endif