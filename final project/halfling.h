#ifndef HALFLING_H
#define HALFLING_H
#include "enemy.h"

class Halfling final: public Enemy{
	Halfling();
	~Halfling() override;
	friend class Floor; 
};

#endif

