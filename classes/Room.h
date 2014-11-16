#ifndef ROOM_H_
#define ROOM_H_
#include <string>
using namespace std;

class Room{
public:

private:
	string name;
	Status status;
	string type;
	string description;
	string border[];
	Container container[];
	Item item[];
	Creature creature[];
	Trigger trigger[];


};
#endif