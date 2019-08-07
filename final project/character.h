#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "object.h"


class Character: public Object {
protected:
	int hp;
	int maxhp;
	int attack;
	int defence;
	char name;
public:
	int gethp();
	char getname();
	int getattack();
	int getdefence();
	virtual ~Character() = 0;
private:
	virtual int attack_enemy(Character *rival);
	virtual void be_attacked(int hp);
friend class Floor;
};
#endif

