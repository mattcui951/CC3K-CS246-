#include "vampire.h"
#include "enemy.h"
#include <iostream>
#include <random>

using namespace std;

random_device rd6;
mt19937 gen6(rd6());

Vampire::Vampire() {
	hp = 50;
	attack = 25;
	defence = 25;
	gold = 0;
	name = 'v';
}


Vampire::~Vampire() {}

void Vampire::addHP(int value) {
	hp += value;
	if(hp < 0){
		hp = 0;
	}
}

int Vampire::attack_enemy(Character *rival){
	int addhp = 5;
	if(rival->getname() == 'W'){
		addhp = -5;
	}
	int atk = attack;
    int def = rival->getdefence();
    int hp = (100 * atk /(100+def));
    uniform_int_distribution<int> miss(0, 1);
    int miss_or_not = miss(gen6);
    if(rival->getname() == 'H'){
        if(miss_or_not == 1){
            hp = 0;
            addhp = 0;
        } 
    }
    addHP(addhp);
    return hp;
};








