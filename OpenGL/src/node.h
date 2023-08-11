#pragma once
#pragma once
#include <iostream>
#include <memory>
#include "./utils/draw.h"
#include<unordered_set>

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
