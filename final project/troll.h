#ifndef TROLL_H
#define TROLL_H
#include "player.h"
#include <string>

class Troll: public Player {
public:
	Troll();
	void move();
	~Troll();
};

#endif
