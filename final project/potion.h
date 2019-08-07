#ifndef POTION_H
#define POTION_H
#include <string>

class Player;



class Potion{
protected:
	std::string name;
public:
	Potion(std::string);
	~Potion();
	void accept(Player *p);
};



#endif




















