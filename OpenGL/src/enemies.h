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
	enemies(float centerx, float centery, int length);//constructor: create an empty snake with a head only
	~enemies();//destuctor
	void move();
	void rotate();
	void drawenemy();
	void erase(float x, float y);
};