#include "chamber.h"
#include <random>
#include <string>
#include <iostream>

using namespace std;

random_device rdevice;
mt19937 generat(rdevice());

Chamber::Chamber(int no){
	if(no == 0){
		number = 0;
		height = 6;
		width = 28;
		start_x = 2;
		start_y = 2;
	}
	if(no == 1){
		number = 1;
		height = 12;
		width = 39;
		start_x = 38;
		start_y = 2;
	}
	if(no == 2){
		number = 2;
		height = 5;
		width = 14;
		start_x = 37;
		start_y = 9;
	}
	if(no == 3){
		number = 3;
		height = 9;
		width = 23;
		start_x = 3;
		start_y = 14;

	}
	if(no == 4){
		number = 4;
		height = 8;
		width = 41;
		start_x = 36;
		start_y = 15;
	}
};

void Chamber::initialize(){
	content.resize(height);
	for(int i = 0; i < height; i++){
		content[i].resize(width);
	}
	// initialize the general display
	for(int i = 1; i < (width-1); i++){
		content[0][i] = '-';
		content[height - 1][i] = '-';
	}
	for(int i = 1; i < (width - 1); i++){
		for(int q = 1; q < (height - 1); q++){
			content[q][i] = '.';
		}
	}
	for(int i = 0; i < height; i++){
		content[i][0] = '|';
		content[i][width-1] = '|';
	}
	// change nuber 1 and 4
	if(number == 1){
		for(int i = 1; i < 22; i++){
			content[5][i] = '-';
		}
		for(int i = 5; i < 12; i++){
			content[i][22] = '|';
		}
		for(int h = 6; h < 12; h++){
			for(int w = 0; w < 22; w++){
				content[h][w] = 'N';
			}
		}
		for(int i = 24; i < 39; i++){
			if(i == 24){
				content[0][i] = '|';
				content[1][i] = '|';
				content[2][i] = '|';
			} else if(i < 32){
				content[0][i] = 'N';
				content[1][i] = 'N';
				content[2][i] = '-';
			} else if(i == 32){
				content[0][i] = 'N';
				content[1][i] = 'N';
				content[2][i] = '|';
				content[3][i] = '|';
			} else if(i < 35){
				content[0][i] = 'N';
				content[1][i] = 'N';
				content[2][i] = 'N';
				content[3][i] = '-';
			} else if(i == 35){
				content[0][i] = 'N';
				content[1][i] = 'N';
				content[2][i] = 'N';
				content[3][i] = '|';
				content[4][i] = '|';
			} else if(i < 38){
				content[0][i] = 'N';
				content[1][i] = 'N';
				content[2][i] = 'N';
				content[3][i] = 'N';
				content[4][i] = '-';
			} else {
				content[0][i] = 'N';
				content[1][i] = 'N';
				content[2][i] = 'N';
				content[3][i] = 'N';
			}
		}
	}
	if(number == 4){
		for(int i = 0; i < 29; i++){
			for(int h = 0; h < 4; h++){
				content[h][i] = 'N';
				if(h == 3 && i > 0){
					content[h][i] = '-';
				}
				if(i == 28){
					content[h][i] = '|';
				}
			}
		}
		content[3][0] = '|';
	}
	// initialize the exit
	if(number == 0){
		content[5][11] = '+';
		content[2][27] = '+';
	}
	if(number == 1){
		content[2][0] = '+';
		content[5][5] = '+';
		content[9][22] = '+';
		content[11][31] = '+';
	}
	if(number == 2){
		content[0][6] = '+';
		content[4][6] = '+';
	}
	if(number == 3){
		content[0][10] = '+';
		content[6][22] = '+';
	}
	if(number == 4){
		content[0][33] = '+';
		content[3][7] = '+';
		content[5][0] = '+';
	}
};
int Chamber::getx(){
	uniform_int_distribution<int> new_x(1, width-2);
	int x = new_x(generat);
	return start_x + x;
};

int Chamber::gety (){
	uniform_int_distribution<int> new_y(1, height-2);
	int y = new_y(generat);
	return start_y + y;
};

void Chamber::display(){
	for(int i = 0; i < height; i++){
		for(int w = 0; w < width; w++){
			if(content[i][w] == '|'){
				cout << "|";
			} else if(content[i][w] == '-'){
				cout << "-";
			} else if(content[i][w] == '.'){
				cout << ".";
			} else if(content[i][w] == '+'){
				cout << "+";
			} else {
				cout << " ";
			} 
		}
		cout << endl;
	}
};
