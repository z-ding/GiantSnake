#pragma once
#include "node.h"
#include "./utils/math.h"

class enemies {
private:
	float center_x;
	float center_y;	
	std::unordered_set< std::shared_ptr<allpurposenode>> location;
	int edges;
public:
	int type;
	enemies(float centerx, float centery, int length, int _type);//constructor: create an empty snake with a head only
	~enemies();//destuctor
	void move(std::shared_ptr<allpurposenode> snakehead);
	void rotate();
	void drawenemy();
	bool kill(std::shared_ptr<allpurposenode> snakehead);
	void erase(float x, float y);
};