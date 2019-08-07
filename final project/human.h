#ifndef HUMAN_H
#define HUMAN_H

#include "enemy.h"

class Human final: public Enemy{
public:
	Human();
	~Human() override;
};

#endif
