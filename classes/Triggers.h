#ifndef TRIGGERS_H_
#define TRIGGERS_H_
#include <string>
using namespace std;

class Triggers{
public:
	string getType();
	void setType(string);

private:
	//Command command[];
	//Condition condition;
	string type;
};
#endif/*TRIGGERS_H_*/