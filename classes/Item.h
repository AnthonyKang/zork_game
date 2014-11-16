#ifndef ITEM_H_
#define ITEM_H_
#include <string>
using namespace std;

class Item{
public:

private:
	string name;
	Status status;
	string writing;
	string description;
	Trigger trigger[];
	int on_off;

};
#endif