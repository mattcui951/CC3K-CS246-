#ifndef CHAMBER_H
#define CHAMBER_H
#include <vector>
#include <string>
#include <map>

struct pos;

class Chamber{
public:
	int number;
	int height;
	int width;
	std::vector<std::vector<char>> content;
	int start_x;
	int start_y;
	Chamber(int no);
	void initialize();
	int getx();
	int gety ();
	void display();
friend class Floor;
};
#endif
