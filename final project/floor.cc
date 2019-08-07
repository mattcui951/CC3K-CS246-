#include "floor.h"
#include "object.h"
#include "character.h"
#include "treasure.h"
#include "potion.h"
#include "dragon.h"
#include "merchant.h"
#include "human.h"
#include "drow.h"
#include "vampire.h"
#include "troll.h"
#include "goblin.h"
#include "dwarf.h"
#include "orcs.h"
#include "elf.h"
#include "halfling.h"
#include "player.h"
#include <iostream>
#include <random>
#include <sstream>
#include <utility>

using namespace std;

random_device random_d;
mt19937 gen(random_d());

bool Floor::game_is_on(){
	return game_on;
};

bool Floor::new_game(){
	cout << "Select a race:" << endl;
	cout << "s: Shade HP: 125, Atk: 25, Def: 25" << endl;
	cout << "d: Drow HP: 150, Atk: 25, Def: 15, All potions have their effect magnified by 1.5" << endl;
	cout << "v: Vampire HP: 50, Atk: 25, Def: 25, Gain 5 HP every successful attack and has no maximum HP" << endl;
	cout << "t: Troll HP: 120, Atk: 25, Def: 15, Regain 5 HP every turn" << endl;
	cout << "g: Goblin HP: 110, Atk: 15, Def: 20, Steals 5 gold from every slain enemy"<< endl;
	game_on = true;
	enemy_move = true;
	floor_number = 1;
	initialize();
	player = new Player;
	Display();
	prev = '.';
	char race;
	enemies_pos.resize(25);
	for(int i = 0; i < 25; i ++){
		enemies_pos[i].resize(80);
		for(int q = 0; q < 80; q++){
			enemies_pos[i][q] = nullptr;
		}
	}
	while(cin >> race){
		if(race == 'q'){
			return false;
		} else if(race == 's'){
			break;
		} else if(race == 'd'){
			delete player;
			player = new Drow;
			break;
		} else if(race == 'v'){
			delete player;
			player = new Vampire;
			break;
		} else if(race == 't'){
			delete player;
			player = new Troll;
			break;
		} else if(race == 'g'){
			delete player;
			player = new Goblin;
			break;
		} else {
			cin.ignore();
			cin.clear();
		}
	}
	newfloor();
	Display();
	return true;
}

bool Floor::restart(){
	endinfo();
	delete player;
	return new_game();
};

void Floor::quit(){
	endinfo();
};

void Floor::set_enemy(){
	uniform_int_distribution<int> type(0, 17);
	uniform_int_distribution<int> cha_num(0, 4);
	for(int i = 0; i < 20; i++){
		Enemy *enemy;
		int name = type(gen);
		int cham = cha_num(gen);
		if(name <= 3){
			enemy = new Human;
		} else if(name <= 6){
			enemy = new Dwarf;
		} else if(name <= 11){
			enemy = new Halfling;
		} else if(name <= 13){
			enemy = new Elf;
		} else if(name <= 15){
			enemy = new Orcs;
		} else {
			enemy = new Merchant;
		}
		enemies.emplace_back(enemy);
		while(true){
			int x = chambers[cham]->getx();
			int y = chambers[cham]->gety();
			if(cham == 1){
				if(x <= 51 && y >= 10){
					continue;
				}
			}
			if(display[y][x] == '.'){
				display[y][x] = enemy->getname();
				enemies_pos[y][x] = enemy;
				break;
			}
		}
	}
};

void Floor::set_potion(){
	uniform_int_distribution<int> type(0, 5);
	uniform_int_distribution<int> cha_num(0, 4);
	for(int i = 0; i < 10; i++){
		int name = type(gen);
		int cham = cha_num(gen);
		while(true){
			int x = chambers[cham]->getx();
			int y = chambers[cham]->gety();
			if(cham == 1){
				if(x <= 51 && y >= 10){
					continue;
				}
			}
			if(display[y][x] == '.'){
				if(name == 0){
					display[y][x] = '0';
				} else if(name == 1){
					display[y][x] = '1';
				} else if(name == 2){
					display[y][x] = '2';
				} else if(name == 3){
					display[y][x] = '3';
				} else if(name == 4){
					display[y][x] = '4';
				} else {
					display[y][x] = '5';
				}
				break;
			}
		}
	}
};

void Floor::set_treasure(){
	uniform_int_distribution<int> type(0, 7);
	uniform_int_distribution<int> cha_num(0, 4);
	for(int i = 0; i < 10; i++){
		int name = type(gen);
		int cham = cha_num(gen);
		while(true){
			int x = chambers[cham]->getx();
			int y = chambers[cham]->gety();
			if(cham == 1){
				if(x <= 51 && y >= 10){
					continue;
				}
			}
			if(display[y][x] == '.'){
				if(name <= 4){
					display[y][x] = '6';
					break;
				} else if(name <= 6){
					display[y][x] = '7';
					break;
				} else {
					display[y][x] = '9';
					if(!pos_availble(x,y)){
						continue;
					}
					set_dragon(x,y);
					break;
				}
			}
		}
	}
};

void Floor::Display(){
	for(int i = 0; i < 25; i++){
		for(int q = 0; q < 80; q++){
			if(display[i][q] == 'N'){
				cout << " ";
			} else if(display[i][q] == '0' ||
				display[i][q] == '1' ||
				display[i][q] == '2' ||
				display[i][q] == '3' ||
				display[i][q] == '4' ||
				display[i][q] == '5' ){
				cout << "P";
			}else if(display[i][q] == '6' ||
				display[i][q] == '7' ||
				display[i][q] == '8' ||
				display[i][q] == '9'){
				cout << "G";
			}else{
				cout << display[i][q];
			}
		}
		cout << endl;
	}
	printplayer();
};

void Floor::set_player(){
	uniform_int_distribution<int> cha_num(0, 4);
	int cham = cha_num(gen);
	while(true){
		int x = chambers[cham]->getx();
		int y = chambers[cham]->gety();
		if(cham == 1){
			if(x <= 51 && y >= 10){
				continue;
			}
		}
		if(display[y][x] == '.'){
			display[y][x] = '@';
			Object *p = player;
			p->setx(x);
			p->sety(y);
			break;
		}
	}
};

void Floor::set_stairway(){
	uniform_int_distribution<int> cha_num(0, 4);
	int cham = cha_num(gen);
	while(true){
		int x = chambers[cham]->getx();
		int y = chambers[cham]->gety();
		if(cham == 1){
			if(x <= 51 && y >= 10){
				continue;
			}
		}
		if(display[y][x] == '.'){
			display[y][x] = '\\';
			break;
		}
	}
};

bool Floor::pos_availble(int x, int y){
	for(int q = -1; q < 2; q++){
		for(int p = -1; p < 2; p++){
			if(display[y+q][x+p] == '.'){
				return true;
			}
		}
	}
	return false;
}

void Floor::set_dragon(int x, int y){
	uniform_int_distribution<int> forx (0, 2);
	uniform_int_distribution<int> fory (0, 2);
	int x_add = forx(gen);
	int y_add = fory(gen);
	while(true){
		x_add = forx(gen);
		y_add = fory(gen);
		if(display[y+y_add-1][x+x_add-1] == '.'){
			display[y+y_add-1][x+x_add-1] = 'D';
			Enemy *enemy = new Dragon;
			enemies_pos[y+y_add-1][x+x_add-1] = enemy;
			enemies.emplace_back(enemy);
			Object *d = enemy;
			d->setx(x);
			d->sety(y);
			break;
		}
	}
};

void Floor::detect(bool add){
	Object *p = player;
	int damage;
	int cur_x = p->getx();
	int cur_y = p->gety();
	bool nothing = true;
	bool pick_set = false;
	for(int i = -1; i < 2; i++){
		for(int q = -1; q < 2; q++){
			char neighbor = display[cur_y+i][cur_x+q];
			if(neighbor == '0' ||
				neighbor == '1' ||
				neighbor == '2' ||
				neighbor == '3' ||
				neighbor == '4' ||
				neighbor == '5'){
				pick_set = true;
			    nothing = false;
			}
			if(neighbor == 'H' ||
				neighbor == 'W' ||
				neighbor == 'E' ||
				neighbor == 'O' ||
				neighbor == 'M' ||
				neighbor == 'L' ||
				neighbor == '9'){
				if(neighbor == '9' || !enemies_pos[cur_y+i][cur_x+q]->gethostile()){
					ostringstream name;
					if(neighbor != '9'){
						name << neighbor;
						damage = enemies_pos[cur_y+i][cur_x+q]->attack_enemy(player);
						player->be_attacked(damage);
						if(!combat && !add){
							cur_action = "";
						}
						cur_action += name.str();
						if(damage == 0){
							cur_action += " missed the attack. ";
						} else {
							cur_action += " deals 5 damage to PC. ";
						}
						combat = true;
						nothing = false;
					} else {
						bool dra = false;
						for(int k = -1; k < 2; k++){
							for(int p = -1; p < 2; p++){
								if(display[cur_y+k][cur_x+p] == 'D'){
									Object *d = enemies_pos[cur_y+k][cur_x+p];
									int x = d->getx();
									int y = d->gety();
									if(display[y][x] == '9'){
										dra = true;
										break;
									}
								}
							}
						}
						if(dra){
							Dragon d;
							name << "D";
							damage = d.attack_enemy(player);
							player->be_attacked(damage);
							if(!combat && !add){
								cur_action = "";
							}
							cur_action += name.str();
							if(damage == 0){
								cur_action += " missed the attack. ";
							} else {
								cur_action += " deals 5 damage to PC. ";
							}
							combat = true;
							nothing = false;
						}
					}
				}
			}
		}
	}
	int cur_hp = player->gethp();
	if(cur_hp <= 0){
		game_on = false;
	}
	if(!combat && pick_set && !add){
		if(cur_action != "PC"){
			cur_action += " and sees an unknown potion.";
		} else {
			cur_action += " sees an unknown potion.";
		}
	}
	if(nothing == true && !add && !combat){
		cur_action = "Player character has spawned.";
	}
};

void Floor::clearFloor(){
	int size = chambers.size();
	for(int i = 0; i < size; i++){
		delete chambers[i];
	}
	chambers.clear();
	int enemy = enemies.size();
	for(int i = 0; i < enemy; i++){
		delete enemies[i];
	}
	enemies.clear();
};

void Floor::endinfo(){
	int score = player->getgold();
	if(player->getname() == 's'){
		score *= 1.5;
	}
	cout << "The game ends. Your score is: " << score << "."<< endl;
};

void Floor::draw_passage(){
	for(int i = 0; i < 8; i++){
		display[4][30+i] = '#';
	}
	for(int i = 0; i < 10; i++){
		display[20][26+i] = '#';
	}
	for(int i = 0; i < 13; i++){
		display[8][31+i] = '#';
	}
	for(int i = 0; i < 19; i++){
		display[11][13+i] = '#';
	}
	for(int i = 0; i < 6; i++){
		display[11][54+i] = '#';
	}
	for(int i = 0; i < 24; i++){
		display[16][31+i] = '#';
	}
	for(int i = 0; i < 3; i++){
		display[5+i][33] = '#';
	}
	for(int i = 0; i < 1; i++){
		display[5+i][33] = '#';
	}
	for(int i = 0; i < 4; i++){
		display[12+i][54] = '#';
	}
	for(int i = 0; i < 6; i++){
		display[8+i][13] = '#';
	}
	for(int i = 0; i < 11; i++){
		display[9+i][31] = '#';
	}
	for(int i = 0; i < 4; i++){
		display[14+i][43] = '#';
	}
	display[14][69] = '#';
}

void Floor::initialize(){
	clearFloor();
	display.resize(25);
	for(int i = 0; i < 25; i++){
		display[i].resize(80);
	}
	for(int i = 1; i < 79; i++){
		display[0][i] = '-';
		display[24][i] = '-';
	}
	for(int i = 0; i < 25; i++){
		display[i][0] = '|';
		display[i][79] = '|';
	}
	for(int i = 1; i < 79; i++){
		for(int q = 1; q < 24; q++){
			display[q][i] = 'N';
		}
	}
	draw_passage();
	// initialize for chambers
	chambers.resize(5);
	int start_x;
	int start_y;
	int h;
	int w;
	for(int i = 0; i < 5; i++){
		chambers[i] = new Chamber(i);
		chambers[i]->initialize();
		start_x = chambers[i]->start_x;
		start_y = chambers[i]->start_y;
		h = chambers[i]->height;
		w = chambers[i]->width;
		for(int p = 0; p < h; p++){
			for(int q = 0; q < w; q++){
				if(chambers[i]->content[p][q] != 'N'){
					display[start_y+p][start_x+q] = chambers[i]->content[p][q];
				}
			}
		}
	}
};

void Floor::newfloor(){
	combat = false;
	prev = '.';
	set_player();
	set_stairway();
	set_potion(); 
	set_treasure();
	set_enemy();
	detect(false);
}



bool Floor::can_move(int x, int y){
	if(display[y][x] == '.'){
		return true;
	} else if(display[y][x] == '+'){
		return true;
	} else if(display[y][x] == '#'){
		return true;
	} else if(display[y][x] == '\\'){
		floor_number++;
		if(floor_number < 6){
			player->reset();
			clearFloor();
			initialize();
			newfloor();
		}
		return false;
	} else if(display[y][x] == '6'){
		display[y][x] = '.';
		player->addgold(1);
		return true;
	} else if(display[y][x] == '7'){
		display[y][x] = '.';
		player->addgold(2);
		return true;
	} else if(display[y][x] == '8'){
		display[y][x] = '.';
		player->addgold(4);
		return true;
	} else if(display[y][x] == '9'){
		bool dragon = false;
		for(int p = -1; p < 2; p++){
			for(int q = -1; q < 2; q++){
				if(display[y+p][x+q] == 'D'){
					Object *d = enemies_pos[y+p][x+q];
					int g_x = d->getx();
					int g_y = d->gety();
					if (g_x == x && g_y == y) {
						Dragon d;
						int damage = d.attack_enemy(player);
						player->be_attacked(damage);
						if(damage != 0){
							cur_action = "D deals 5 damage to PC. ";
						} else {
							cur_action = "D missed the attack. ";
						}
						cout << cur_action << endl;
						combat = true;
						dragon = true;
					}
				}
			}
		}
		if(dragon == false){
			player->addgold(6);
			display[y][x] = '.';
		}
		return true;
	}
	return false;
};

void Floor::playermove(string dir){
	combat = false;
	if(valid_dir(dir)){
		move();
		int pre_x;
		int pre_y;
		Object *p = player;
		int cur_x = p->getx();
		int cur_y = p->gety();	
		if(dir == "no"){
			pre_y = cur_y-1;
			pre_x = cur_x;
			cur_action += " moves North";
			cout << cur_action << endl;
		}
		if(dir == "so"){
			pre_y = cur_y+1;
			pre_x = cur_x;
			cur_action += " moves South";
		}
		if(dir == "ea"){
			pre_y = cur_y;
			pre_x = cur_x+1;
			cur_action += " moves East";
		}
		if(dir == "we"){
			pre_y = cur_y;
			pre_x = cur_x-1;
			cur_action += " moves West";
		}
		if(dir == "ne"){
			pre_y = cur_y-1;
			pre_x = cur_x+1;
			cur_action += " moves Northeast";
		}
		if(dir == "nw"){
			pre_y = cur_y-1;
			pre_x = cur_x-1;
			cur_action += " moves Northwest";
		}
		if(dir == "se"){
			pre_y = cur_y+1;
			pre_x = cur_x+1;
			cur_action += " moves Southeast";
		}
		if(dir == "sw"){
			pre_y = cur_y+1;
			pre_x = cur_x-1;
			cur_action += " moves Southwest";
		}
		if(can_move(pre_x, pre_y)){
			p->setx(pre_x);
			p->sety(pre_y);
			display[cur_y][cur_x] = prev;
			prev = display[pre_y][pre_x];
			display[pre_y][pre_x] = '@';
			player->move();
		}
		detect(false);
		if(floor_number <= 5){
			Display();
		} else {
			game_on = false;
		}
		if(!game_on){
			endinfo();
		}
	}
};

void Floor::printplayer(){
	int g = player->getgold();
	int hp = player->gethp();
	int atk = player->getattack();
	int def = player->getdefence();
	ostringstream oss;
	oss << g;
	string gold = oss.str();
	int len = gold.length();
	int s_num = 51-len;
	string space = " ";
	for(int i = 1; i < s_num; i++){
		space += " ";
	}
	cout << "Race: Shade Gold: " << gold << space << "Floor " << floor_number << endl;
	cout << "HP: " << hp << endl;
	cout << "Atk: " << atk << endl;
	cout << "Def: " << def << endl;
	cout << "Action: " << cur_action << endl;
	cur_action = "PC";
};

bool Floor::valid_dir(std::string dir){
	if(dir == "no" || dir == "so" ||
		dir == "ea" || dir == "we" ||
		dir == "ne" || dir == "nw" ||
		dir == "se" || dir == "sw"){
		return true;
} else {
	return false;
}
};

void Floor::pick_potion(string dir){
	combat = false;
	if(valid_dir(dir)){
		move();
		Object *p = player;
		int cur_x = p->getx();
		int cur_y = p->gety();
		int potion_x;
		int potion_y;
		if(dir == "no"){
			potion_x = cur_x;
			potion_y = cur_y-1;
		}
		if(dir == "so"){
			potion_x = cur_x;
			potion_y = cur_y+1;
		}
		if(dir == "ea"){
			potion_x = cur_x+1;
			potion_y = cur_y;
		}
		if(dir == "we"){
			potion_x = cur_x-1;
			potion_y = cur_y;
		}
		if(dir == "ne"){
			potion_x = cur_x+1;
			potion_y = cur_y-1;
		}
		if(dir == "nw"){
			potion_x = cur_x-1;
			potion_y = cur_y-1;
		}
		if(dir == "se"){
			potion_x = cur_x+1;
			potion_y = cur_y+1;
		}
		if(dir == "sw"){
			potion_x = cur_x-1;
			potion_y = cur_y+1;
		}
		if(display[potion_y][potion_x] == '0'){
			cur_action = "PC uses RH. ";
			Potion rh("RH");
			rh.accept(player);
			display[potion_y][potion_x] = '.';
		} else if(display[potion_y][potion_x] == '1'){
			cur_action = "PC uses BA. ";
			Potion ba("BA");
			ba.accept(player);
			display[potion_y][potion_x] = '.';
		} else if(display[potion_y][potion_x] == '2'){
			cur_action = "PC uses BD. ";
			Potion bd("BD");
			bd.accept(player);
			display[potion_y][potion_x] = '.';
		} else if(display[potion_y][potion_x] == '3'){
			cur_action = "PC uses PH. ";
			Potion ph("PH");
			ph.accept(player);
			display[potion_y][potion_x] = '.';
		} else if(display[potion_y][potion_x] =='4'){
			cur_action = "PC uses WA. ";
			Potion wa("WA");
			wa.accept(player);
			display[potion_y][potion_x] = '.';
		} else if(display[potion_y][potion_x] == '5'){
			cur_action = "PC uses WD. ";
			Potion wd("WD");
			wd.accept(player);
			display[potion_y][potion_x] = '.';
		} else{
			cur_action = "There is no potion in the direction. ";
		}
		if(player->gethp() <= 0){
			game_on = false;
		}
		detect(true);
		Display();
		if(!game_on){
			endinfo();
		}
	}
};

void Floor::attack(string dir){
	combat = false;
	Object *p = player;
	int cur_x = p->getx();
	int cur_y = p->gety();
	int attack_x;
	int attack_y;
	if(valid_dir(dir)){
		move();
		if(dir == "no"){
			attack_x = cur_x;
			attack_y = cur_y-1;
		}
		if(dir == "so"){
			attack_x = cur_x;
			attack_y = cur_y+1;
		}
		if(dir == "ea"){
			attack_x = cur_x+1;
			attack_y = cur_y;
		}
		if(dir == "we"){
			attack_x = cur_x-1;
			attack_y = cur_y;
		}
		if(dir == "ne"){
			attack_x = cur_x+1;
			attack_y = cur_y-1;
		}
		if(dir == "nw"){
			attack_x = cur_x-1;
			attack_y = cur_y-1;
		}
		if(dir == "se"){
			attack_x = cur_x+1;
			attack_y = cur_y+1;
		}
		if(dir == "sw"){
			attack_x = cur_x-1;
			attack_y = cur_y+1;
		}
		if(display[attack_y][attack_x] == 'W' ||
			display[attack_y][attack_x] == 'E' ||
			display[attack_y][attack_x] == 'O' ||
			display[attack_y][attack_x] == 'L' ||
			display[attack_y][attack_x] == 'M' ||
			display[attack_y][attack_x] == 'H' ||
			display[attack_y][attack_x] == 'D'){
			int damage = player->attack_enemy(enemies_pos[attack_y][attack_x]);
			enemies_pos[attack_y][attack_x]->be_attacked(damage);
			ostringstream name;
			name << display[attack_y][attack_x];
			int hp = enemies_pos[attack_y][attack_x]->gethp();
			ostringstream cur_hp;
			cur_hp << hp;
		    if(damage == 0){
		    	cur_action += " missed the attack. ";
		    } else {
		    	cur_action += " deals 5 damage to ";
		    	cur_action += name.str();
		    	cur_action += " (";
		    	cur_action += cur_hp.str();
		    	cur_action += " HP). ";
		    }
		    if(hp <= 0){
		    	int g = enemies_pos[attack_y][attack_x]->dropgold(display[attack_y][attack_x]);
		    	player->addgold(g);
		    	if(display[attack_y][attack_x] == 'M' ||
		    		display[attack_y][attack_x] == 'H'){
		    		display[attack_y][attack_x] = '8';
		    	} else {
		    		display[attack_y][attack_x] = '.';
		    	}
		    	if(player->getname() == 'g'){
		    		player->addgold(5);
		    	}
		    }
		} else{
			cur_action = "There is no enemy in the direction. ";
		}
		detect(true);
		Display();
		if(!game_on){
			endinfo();
		}
	}
};

bool Floor::is_attack(int x, int y){
	for(int i = -1; i < 2; i++){
		for(int q = -1; q < 2; q++){
			if(display[y+i][x+q] == '@'){
				return true;
			}
		}
	}
	return false;
};

void Floor::move(){
	uniform_int_distribution<int> x_c(0, 2);
	uniform_int_distribution<int> y_c(0, 2);
	if(enemy_move){
		for(int q = 0; q < 25; q++){
			for(int p = 0; p < 80; p++){
				if(display[q][p] == 'H'||
					display[q][p] == 'W'||
					display[q][p] == 'E'||
					display[q][p] == 'O'||
					display[q][p] == 'M'||
					display[q][p] == 'L'){
					if(!is_attack(p,q)){
						if(pos_availble(p,q)){
							int x,y;
							while(true){
								x = x_c(gen);
								y = y_c(gen);
								if(display[q+y-1][p+x-1] == '.'){
									swap(display[q+y-1][p+x-1], display[q][p]);
									swap(enemies_pos[q+y-1][p+x-1], enemies_pos[q][p]);
									break;
								}
							}
						}
					}
				}
			}
		}
	};
}

void Floor::stop_enemy(){
	if(enemy_move){
		enemy_move = false;
	} else {
		enemy_move = true;
	}
};

Floor::~Floor(){
	clearFloor();
	delete player;
};


