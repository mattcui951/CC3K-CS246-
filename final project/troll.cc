#include "troll.h"
#include <iostream>

using namespace std;

Troll::Troll() {
	hp = 120;
	maxhp = 120;
	attack = 25;
    defence = 15;
	gold = 0;
	name = 't';
}


Troll::~Troll() {}

void Troll::move() {
	this->addHP(5);
}
