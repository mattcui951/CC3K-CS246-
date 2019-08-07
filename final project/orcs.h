#ifndef ORCS_H
#define ORCS_H
#include "enemy.h"

class Orcs final: public Enemy{
	int attack_enemy(Character *rival) override;
public:
	Orcs();
	~Orcs();
};

#endif

