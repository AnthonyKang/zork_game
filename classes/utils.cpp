#include <iostream>
#include <string>
#include "Room.h"
//#include "utils.h"
#include "../rapidxml/rapidxml.hpp"
#include "../rapidxml/rapidxml_utils.hpp"
#include "../rapidxml/rapidxml_print.hpp"
//#include "../rapidxml/rapidxml_iterators.hpp"
using namespace std;
using namespace rapidxml;
Room * makeRoom(Room * room, xml_node<> * room_node){
	
	//Room * new_room = new Room();
	cout<< room_node->name() << endl;
	xml_node<> *buffer = room_node->first_node();
	cout << buffer->value() << endl;
	
	//return new_room;
}