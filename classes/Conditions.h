#ifndef CONDITIONS_H
#define CONDITIONS_H_
#include <string>
#include "Owner.h"
#include "Status.h"
#include "Triggers.h"
using namespace std;

class Conditions: public Triggers{
public:
	Conditions();

	Owner getOwner();
	void setOwner(Owner);
 
	Status getStatus();
	void setStatus(Status);


private:
	Owner owner;
	Status status;	
};
#endif