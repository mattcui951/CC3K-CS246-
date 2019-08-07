#include <iostream>
#include <random>
#include "floor.h"

using namespace std;

int main()
{
	Floor f;
	if(!f.new_game()){
		return 0;
	}
	string ins;
	string dir;
	while(cin >> ins){
		if(ins == "q"){
			f.quit();
			return 0;
		} else if(ins == "u"){
			cin >> dir;
			f.pick_potion(dir);
		} else if(ins == "a"){
			cin >> dir;
			f.attack(dir);
		} else if(ins == "f"){
			f.stop_enemy();
		} else if(ins == "r"){
			if(!f.restart()){
				return 0;
			};
		} else{
			f.playermove(ins);
		}
		if(!f.game_is_on()){
			return 0;
		}
	}
}
