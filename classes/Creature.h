#ifndef CREATURE_H_
#define CREATURE_H_
#include <string>
#include <vector>
#include <iostream>
#include "Item.h"
#include "Attack.h"

using namespace std;

class Creature{
public:
	string getName();
	void setName(string);
 
	Status getStatus();
	void setStatus(Status);

	string getDescription();
	void setDescription(string);

	vector<Triggers> getTriggers();
	void setTriggers(Triggers);

	vector<string> getVulnerabilityList();
	void setVulnerabilityList(string);

	string getConditionSatisfy();
	void setConditionSatisfy(string);

	Attack getAttack();
	void setAttack(Attack);

	Creature();


private:
	string name;
	Status status;
	string description;
	vector<string> vulnerabilityList;
	vector<Triggers> triggers;
	string conditionSatisfy;
	Attack attack;

};
#endif