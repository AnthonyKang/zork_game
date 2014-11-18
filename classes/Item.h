#ifndef ITEM_H_
#define ITEM_H_
#include <string>

#include "Triggers.h"
#include "Status.h"

using namespace std;

class Item{
public:
	Item();

	string getName();
	void setName(string);
 
	Status getStatus();
	void setStatus(Status);

	string getWriting();
	void setWriting(string);

	string getOnFlag();
	void setOnFlag(string);

	string getDescription();
	void setDescription(string);
	
	Triggers * getTriggers();
	void setTriggers(Triggers*);

	void turn_on();
	void turn_off();

private:
	string name;
	Status status;
	string writing;
	string description;
	Triggers * triggers;
	int on_off;
	string onFlag;
	

};
#endif