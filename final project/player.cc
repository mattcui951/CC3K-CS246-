#include "player.h"
#include "enemy.h"
#include <iostream>
#include <string>
#include <random>

using namespace std;

random_device rd4;
mt19937 gen4(rd4());

Player::Player() {
    hp = 125;
    maxhp = 125;
    attack = 25;
    defence = 25;
    gold = 0;
    name = 's';
}

void Player::addHP(int value) {
    hp += value;
    if (hp >= maxhp) {
        hp = maxhp;
    }
    if (hp <= 0) {
        hp = 0;
    }
    return;
}


void Player::addgold(int value) {
    gold += value;
    return;
}

void Player::addAttack(int value) {
    attack += value;
    return;
}

void Player::addDef(int value) {
    defence += value;
    return;
}
int Player::getgold(){
    return gold;
};

void Player::move(){};

int Player::attack_enemy(Character *rival){
    int atk = attack;
    int def = rival->getdefence();
    int hp = (100 * atk /(100+def));
    uniform_int_distribution<int> miss(0, 1);
    int miss_or_not = miss(gen4);
    if(rival->getname() == 'H'){
        if(miss_or_not == 1){
            hp = 0;
        } 
    }
    return hp;
};

void Player::be_attacked(int hp){
    addHP(-hp);
};


void Player::reset() {
    char n = getname();
    if(n == 's'){
        attack = 25;
        defence = 25;
    }
    if(n == 'd'){
        attack = 25;
        defence = 15;
    }
    if(n == 'v'){
        attack = 25;
        defence = 25;
    }
    if(n == 't'){
        attack = 25;
        defence = 15;
    }
    if(n == 'g'){
        attack = 15;
        defence = 20;
    }
}

Player::~Player(){};
