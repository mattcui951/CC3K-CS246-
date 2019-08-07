#ifndef FLOOR_H
#define FLOOR_H
#include <vector>
#include "chamber.h"


class Character;
class Potion;
class Treasure;
class Player;
class Enemy;

class Floor{
	bool game_on;
	bool enemy_move;
	bool combat;
	std::vector<Chamber *> chambers;
	std::vector<std::vector<char>> display;
	char prev;
	int floor_number;
	std::string cur_action;
	Player *player;
	std::vector<Enemy *> enemies;
	std::vector<std::vector<Enemy *>> enemies_pos;
	void draw_passage();
	void set_enemy();
	void set_potion();
	void set_treasure();
	void set_player();
	void set_stairway();
	void set_dragon(int x, int y);
	void detect(bool add);
	bool can_move(int x, int y);
	bool valid_dir(std::string dir);
	void Display();
	bool pos_availble(int x, int y);
	void initialize();
	void newfloor();
	void clearFloor();
	void endinfo();
	void move();
	bool is_attack(int x, int y);
	void printplayer();
public:
	void quit();
	bool restart();
	bool game_is_on();
	bool new_game();
	void pick_potion(std::string dir);
	void attack(std::string dir);
	void stop_enemy();
	void playermove(std::string dir);
	~Floor();
};

#endif
