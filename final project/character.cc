#include "character.h"
#include <iostream>

using namespace std;

int Character::gethp(){
	return hp;
};

char Character::getname(){
	return name;
};

int Character::getattack(){
	return attack;
};

int Character::getdefence(){
	return defence;
};

int Character::attack_enemy(Character *rival){
	return 0;
};

void Character::be_attacked(int hp){};

Character::~Character(){};
