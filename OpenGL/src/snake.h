#pragma once
#include <tuple>
class snakenode {
private:
	int x;// x coordinate
	int y;// y coordinate
	int r;//radius
	char text;//text
	snakenode* prev;// previous node
	snakenode* next;//next node
public:
	snakenode(char c);//constructor without location
	snakenode(char c, int _x, int _y);//constructor with location
	~snakenode();//destructor
	std::tuple<int, int,char,snakenode*,snakenode*> getter();
};

class snake {
private:
	snakenode* head;
public:
	snake(int _x, int _y);//constructor: create an empty snake with a head only
	~snake();//destuctor
	snakenode* getehad();
};
