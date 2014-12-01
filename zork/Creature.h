#ifndef CREATURE_H_
#define CREATURE_H_
#include <string>
#include <vector>
#include <iostream>
#include "gameObjects.h"
#include "../rapidxml/rapidxml.hpp"
#include "../rapidxml/rapidxml_utils.hpp"
#include "../rapidxml/rapidxml_print.hpp"

using namespace std;
using namespace rapidxml;

class Creature: public gameObjects{
private:
	vector<string> vulnerability;
	Attack attack;
	Condition creature_condition;
	//vector<Trigger> trigger;

public:
	Creature(xml_node<> * creatureTag);

	void setVulnerability(string);
	vector<string> getVulnerability();

	void setAttack(Condition, string, vector<string>);
	Attack getAttack();



};
#endif