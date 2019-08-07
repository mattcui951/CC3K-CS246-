#ifndef PLAYER_H
#define PLAYER_H
#include "character.h"
#include <string>

class object;
class character;
class Enemy;

class Player: public Character {
  int gold;
  void addgold(int value);
  void addAttack(int value);
  void addDef(int value);
  int getgold();
  virtual void addHP(int value);
  virtual void move();
  virtual void reset();
  virtual int attack_enemy(Character *rival) override;
  virtual void be_attacked(int hp) override;
public:
  Player();
  ~Player() override;
friend class Floor;
friend class Potion;
friend class Vampire;
friend class Troll;
};

#endif
