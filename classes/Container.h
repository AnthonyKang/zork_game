#ifndef CONTAINER_H_
#define CONTAINER_H_
#include <string>
using namespace std;

class Container{
public:

private:
	string name;
	Status status;
	string description;
	Item accept[];
	Item item[];
	Trigger trigger[];


};
#endif