#include "merchant.h"
#include <random>

using namespace std;

random_device rd2;
mt19937 gen2(rd2());

bool Merchant::hostile = true;

Merchant::Merchant(){
	hp = 30;
	maxhp = 30;
	attack = 70;
	defence = 5;
	name = 'M';
};

void Merchant::be_attacked(int hp){
	hostile = false;
	this->hp -= hp;
	if(this->hp < 0){
		this->hp = 0;
	}
};

bool Merchant::gethostile(){
	return hostile;
};

Merchant::~Merchant(){};

