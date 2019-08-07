#ifndef ELF_H
#define ELF_H
#include "enemy.h"

class Elf final: public Enemy{
	int attack_enemy(Character *rival) override;
public:
	Elf();
	~Elf() override;
};

#endif
