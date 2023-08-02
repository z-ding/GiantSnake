#pragma once
#include <glew.h>
#include <glfw3.h>
#include <tuple>
#include <iostream>
#include <memory>
struct snode;
class snakenode {
private:
	float x;// x coordinate
	float y;// y coordinate
	float r;//radius
	char text;//text
	snakenode* prev;// previous node
	snakenode* next;//next node
public:
	snakenode(char c);//constructor without location
	snakenode(char c, int _x, int _y);//constructor with location
	~snakenode();//destructor
	snode getter();	
	friend void connectnodes(snakenode* n1, snakenode* n2);
	
};
struct snode {
	float x;// x coordinate
	float y;// y coordinate
	float r;//radius
	char text;//text
	snakenode* prev;// previous node
	snakenode* next;//next node
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
	void emplace_back();
	void drawsnake(float prevx, float prevy);
};
