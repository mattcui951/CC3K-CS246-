#include "elf.h"
#include <random>

using namespace std;

random_device rd3;
mt19937 generator(rd3());

Elf::Elf(){
	hp = 140;
	maxhp = 140;
	attack = 30;
	defence = 10;
	name = 'E';
};

int Elf::attack_enemy(Character *rival){
	int atk = attack;
	int def = rival->getdefence();
	int hp = (100 * atk /(100+def));
	uniform_int_distribution<int> miss(0, 1);
	int miss_or_not = miss(generator);
	if(miss_or_not == 1){
		hp = 0;
	}
	if(rival->getname() == 'd'){
		return hp;
	} else {
		return hp * 2;
	}
};

Elf::~Elf(){};
