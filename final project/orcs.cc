#include "orcs.h"
#include <random>

using namespace std;

random_device rd1;
mt19937 gen1(rd1());

Orcs::Orcs(){
	hp = 180;
	maxhp = 180;
	attack = 30;
	defence = 20;
	name = 'O';
};

int Orcs::attack_enemy(Character *rival){
	int atk = attack;
	int def = rival->getdefence();
	int hp = (100 * atk /(100+def));
	uniform_int_distribution<int> miss(0, 1);
	int miss_or_not = miss(gen1);
	if(miss_or_not == 1){
		hp = 0;
	}
	if(rival->getname() == 'g'){
		return hp * 1.5;
	} else {
		return hp;
	}
};

Orcs::~Orcs(){};
