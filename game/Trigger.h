#ifndef TRIGGER_H_
#define TRIGGER_H_
#include <string>
#include <vector>
#include <iostream>
#include "../rapidxml/rapidxml.hpp"
#include "../rapidxml/rapidxml_utils.hpp"
#include "../rapidxml/rapidxml_print.hpp"
using namespace std;
using namespace rapidxml;

typedef struct _condition{
	string object;
	string status;
	string has;
	string owner;

} Condition;

class Trigger{
private:
	string type;
	string print;
	vector<string> action;
	string command;
	Condition condition;

public:
	Trigger(xml_node<> * triggerTag);

	void setType(string);
	string getType();

	void setPrint(string);
	string getPrint();

	void setCommand(string);
	string getCommand();

	void setAction(string);
	vector<string> getAction();

	void setCondition(string, string, string, string);
	Condition getCondition();


};
#endif