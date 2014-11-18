#ifndef ATTACK_H_
#define ATTACK_H_
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Attack{
private:
	string object;
	string status;
	string print;


public:
	string getObject();
	void setObject(string);

	string getStatus();
	void setStatus(string);

	string getPrint();
	void setPrint(string);

	Attack();

};
#endif