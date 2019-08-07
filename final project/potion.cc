#include "potion.h"
#include "player.h"

using namespace std;

Potion::Potion(string name): name{name}{}

Potion::~Potion(){}

void Potion::accept(Player *p) {
  char pname = p->getname();
  if(name == "RH"){
    if(pname == 'd'){
      p->addHP(15);
    } else {
      p->addHP(10);
    }
  }
  if(name == "BA"){
    if(pname == 'd'){
      p->addAttack(5 * 1.5);
    } else{
      p->addAttack(5);
    }
  }
  if(name == "BD"){
    if(pname == 'd'){
      p->addDef(5 * 1.5);
    } else{
      p->addDef(5);
    }
  }
  if(name == "PH"){
    if(pname == 'd'){
      p->addHP(-15);
    } else{
      p->addHP(-10);
    }
  }
  if(name == "WA"){
    if(pname == 'd'){
      p->addAttack(-5 * 1.5);
    } else{
      p->addAttack(-5);
    }
  }
  if(name == "WD"){
    if(pname == 'd'){
      p->addDef(- 5 * 1.5);
    } else{
      p->addDef(- 5);
    }
  }
}
