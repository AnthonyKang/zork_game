#ifndef STATUS_H_
#define STATUS_H_
#include <string>
using namespace std;

class Status{
public:
	Status();

	string getObject();
	void setObject(string);
 
	string getStatus();
	void setStatus(string);


private:
	string status;	
	string object;
};
#endif