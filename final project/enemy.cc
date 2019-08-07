#include "enemy.h"
#include "player.h"
#include <random>
#include <iostream>

using namespace std;

random_device rd5;
mt19937 gen5(rd5());

int Enemy::attack_enemy(Character *rival){
	int atk = attack;
	int def = rival->getdefence();
	int hp = (100 * atk /(100+def));
	uniform_int_distribution<int> miss(0, 1);
	int miss_or_not = miss(gen5);
	if(miss_or_not == 1){
		return hp;
	} else {
		return 0;
	}
};

void Enemy::be_attacked(int hp){
	this->hp -= hp;
	if(this->hp < 0){
		this->hp = 0;
	}
};

int Enemy::dropgold(char name){
	if(name == 'E'||
		name == 'O' ||
		name == 'W' ||
		name == 'L'){
		uniform_int_distribution<int> type(0,1);
	    int drop = type(gen5);
	    if(drop == 0){
	    	return 1;
	    } else {
	    	return 2;
	    } 
	} else {
		return 0;
	}
};

bool Enemy::gethostile(){
	return false;
};

Enemy::~Enemy(){};
