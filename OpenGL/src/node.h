#pragma once
#pragma once
#include <iostream>
#include <memory>
#include "./utils/draw.h"
#include<unordered_set>

struct snode;
class allpurposenode {
private:
	float x;// x coordinate
	float y;// y coordinate
	float r;//radius
	char text;//text
	std::shared_ptr<allpurposenode> prev;// previous node
	std::shared_ptr<allpurposenode> next;//next node
public:
	allpurposenode(char c);//constructor without location
	allpurposenode(char c, int _x, int _y);//constructor with location
	allpurposenode(char c, int _x, int _y, int _r);//constructor with location and radius
	~allpurposenode();//destructor
	snode getter();
	void nodexysetter(float _x, float _y);
	friend void connectnodes(std::shared_ptr<allpurposenode> n1, std::shared_ptr<allpurposenode> n2);

};
struct snode {
	float x;// x coordinate
	float y;// y coordinate
	float r;//radius
	char text;//text
	std::shared_ptr<allpurposenode> prev;// previous node
	std::shared_ptr<allpurposenode> next;//next node
};
