#ifndef VAMPIRE_H
#define VAMPIRE_H
#include "player.h"

class Enemy;

class Vampire final: public Player {
public:
    Vampire();
    ~Vampire() override;
    void addHP(int value)override;
    int attack_enemy(Character *rival) override;
};

#endif
