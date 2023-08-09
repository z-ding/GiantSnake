#pragma once
#include <iostream>
#include <memory>
#include "./utils/draw.h"
#include<unordered_set>;

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
class items;
class snake {
private:
	std::shared_ptr<snakenode> head;
	std::shared_ptr<snakenode> tail;
	std::vector<std::pair<float, float>> shootline;
public:
	bool alive;
	bool addlen;
	snake(int _x, int _y);//constructor: create an empty snake with a head only
	~snake();//destuctor
	std::shared_ptr<snakenode> gethead();
	std::shared_ptr<snakenode> gettail();
	void move(std::shared_ptr<items> i);
	void checkalive(float x, float y);
	void emplace_back(float x, float y, char t);
	void drawsnake();
	void shooting();
	void erase(float x, float y);
	void displayshootline();
};
void fillgrid(int x, int y, std::shared_ptr < snakenode> node);
class items {
private:
	std::unordered_set< std::shared_ptr<snakenode>> itemlist;
	int capacity;//maximum items on the screen
public:
	items(int _cap, std::unordered_set< std::shared_ptr<snakenode>> &_list);//default contructor, create an empty list
	~items();
	void generateoneitem();
	void removeoneitem(int _x, int _y);//after collision with the snakehead
	void drawitems();
	std::unordered_set< std::shared_ptr<snakenode>> listgetter();
	int sizegetter();
};
