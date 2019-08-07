#ifndef DWARF_H
#define DWARF_H

#include "enemy.h"

class Dwarf final: public Enemy{
public:
	Dwarf();
	~Dwarf() override;
};

#endif

