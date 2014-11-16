#include <iostream>
#include <string.h>
#include "../rapidxml/rapidxml.hpp"
#include "../rapidxml/rapidxml_utils.hpp"
#include "../rapidxml/rapidxml_print.hpp"
//#include "../rapidxml/rapidxml_iterators.hpp"
using namespace std;
using namespace rapidxml;

int main(){
	rapidxml::file<>xmlFile("../map1.xml");
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());
	
	/*xml_node<> *map = doc.first_node();
	xml_node<> *room = map->first_node();
	cout << room->name() << endl;
	xml_node<> *name = room->first_node();
	cout << name->name() << endl;
	string strValue = name->value();
	cout << strValue << endl;
	xml_node<> *test = room->first_node("description");
	cout << test->value() << endl;
}	*/
	xml_node<> *map = doc.first_node();
	xml_node<> *buffer = map->first_node();
	cout << buffer->name() << endl;
	while((buffer = buffer->next_sibling()) != NULL){
		cout << buffer->name() << endl;
	}
}