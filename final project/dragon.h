#ifndef DRAGON_H
#define DRAGON_H

#include "enemy.h"

class Dragon final: public Enemy{
public:
	Dragon();
	~Dragon() override; 
};

#endif
