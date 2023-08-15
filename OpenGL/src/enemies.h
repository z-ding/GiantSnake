#pragma once
#include "node.h"
#include "./utils/math.h"
 class bullet {
 public:
	float locationx;
	float locationy;
	float targetx;
	float targety;
	 bullet(float x1, float y1, float x2, float y2);
	 ~bullet();
};
class enemies {
private:
	float center_x;
	float center_y;	
	std::unordered_set< std::shared_ptr<allpurposenode>> location;
	int edges;
public:
	int type;
	std::vector< std::shared_ptr<bullet>> bullets;
	std::pair<float, float> getcenter();
	enemies(float centerx, float centery, int length, int _type);//constructor: create an empty snake with a head only
	~enemies();//destuctor
	void move(std::shared_ptr<allpurposenode> snakehead);
	void rotate();
	void drawenemy();
	bool kill(std::shared_ptr<allpurposenode> snakehead);
	void movebullet();
	void drawbullets();
};