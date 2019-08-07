#ifndef TREASURE_H
#define TREASURE_H
#include <string>
#include "object.h"

class Treasure: public Object{
	std::string name;
public:
	Treasure();
	void settype(std::string type);
	
};

#endif
