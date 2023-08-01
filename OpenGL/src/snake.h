#pragma once
#include <glew.h>
#include <glfw3.h>
#include <tuple>
#include <iostream>
#include <vector>
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
	friend void connectnodes(snakenode* n1, snakenode* n2);
	
};

class snake {
private:
	snakenode* head;
	snakenode* tail;
public:
	snake(int _x, int _y);//constructor: create an empty snake with a head only
	~snake();//destuctor
	snakenode* gethead();
	snakenode* gettail();
	void settail(snakenode* node);
	void emplace_back();
	void drawsnake();	
};
