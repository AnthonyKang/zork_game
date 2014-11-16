#ifndef CONTAINER_H_
#define CONTAINER_H_
#include <string>
using namespace std;

class Creature{
public:

private:
	string name;
	Status status;
	string description;
	Item vulnerability[];
	Attack attack;
	Trigger trigger[];


};
#endif