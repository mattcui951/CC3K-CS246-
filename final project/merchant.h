#ifndef MERCHANT_H
#define MERCHANT_H

#include "enemy.h"

class Merchant final: public Enemy{
	static bool hostile;
	void be_attacked(int hp) override;
	bool gethostile() override;
public:
	Merchant();
	~Merchant() override;
};

#endif
