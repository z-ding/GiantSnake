#pragma once
#include <iostream>
#include <memory>
#include "./utils/draw.h"

struct snode;
class snakenode {
private:
	float x;// x coordinate
	float y;// y coordinate
	float r;//radius
	char text;//text
	std::shared_ptr<snakenode> prev;// previous node
	std::shared_ptr<snakenode> next;//next node
public:
	snakenode(char c);//constructor without location
	snakenode(char c, int _x, int _y);//constructor with location
	snakenode(char c, int _x, int _y, int _r);//constructor with location and radius
	~snakenode();//destructor
	snode getter();	
	void nodexysetter(float _x, float _y);
	friend void connectnodes(std::shared_ptr<snakenode> n1, std::shared_ptr<snakenode> n2);
	
};
struct snode {
	float x;// x coordinate
	float y;// y coordinate
	float r;//radius
	char text;//text
	std::shared_ptr<snakenode> prev;// previous node
	std::shared_ptr<snakenode> next;//next node
};
class snake {
private:
	std::shared_ptr<snakenode> head;
	std::shared_ptr<snakenode> tail;
public:
	bool alive;
	snake(int _x, int _y);//constructor: create an empty snake with a head only
	~snake();//destuctor
	std::shared_ptr<snakenode> gethead();
	std::shared_ptr<snakenode> gettail();
	void move();
	void checkalive(float x, float y);
	void emplace_back();
	void drawsnake(float prevx, float prevy);
};
