#pragma once
#include "node.h"
#include "items.h"
#include "enemies.h"
#include "map.h"
#include"./utils/gamelogic.h"

class snake {
private:
	std::shared_ptr<allpurposenode> head;
	std::shared_ptr<allpurposenode> tail;
	std::vector<std::pair<float, float>> shootline;
public:
	bool alive;
	bool addlen;
	snake(int _x, int _y);//constructor: create an empty snake with a head only
	~snake();//destuctor
	std::shared_ptr<allpurposenode> gethead();
	std::shared_ptr<allpurposenode> gettail();
	void move(std::unique_ptr<items> &i,  std::shared_ptr<allpurposenode> &curloc, std::unique_ptr<map> &fibonaccimap);
	void checkalive(float x, float y);
	void emplace_back(float x, float y, char t);
	void drawsnake();
	bool shooting(std::vector<std::shared_ptr<enemies>> &Enemies);
	void erase(float x, float y);
	void displayshootline();
	bool isPerfect();
};
void fillgrid(int x, int y, std::shared_ptr < allpurposenode> node);
