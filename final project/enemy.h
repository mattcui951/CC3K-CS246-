#ifndef ENEMY_H
#define ENEMY_H
#include "character.h"

class Enemy: public Character{
	int attack_enemy(Character *rival) override;
	void be_attacked(int hp) override;
	int dropgold(char name);
	virtual bool gethostile();
public:
	~Enemy();
friend class Floor;
};

#endif
