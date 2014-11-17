#ifndef UTILS_H_
#define UTILS_H_
#include "Room.h"
#include "../rapidxml/rapidxml.hpp"
#include "../rapidxml/rapidxml_utils.hpp"
#include "../rapidxml/rapidxml_print.hpp"
using namespace std;
using namespace rapidxml;
Room * makeRoom(Room *, xml_node<> *);
#endif