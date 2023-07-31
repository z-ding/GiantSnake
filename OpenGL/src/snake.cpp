#include "snake.h"
snakenode::snakenode(char c) {
	text = c;
	prev = nullptr;
	next = nullptr;
}
snakenode::snakenode(char c, int _x, int _y) {
	text = c;
	x = _x;
	y = _y;
	prev = nullptr;
	next = nullptr;
}
snakenode::~snakenode() {

}
std::tuple<int, int, char, snakenode*, snakenode*> snakenode::getter() {
	return { x,y, text,prev,next};
};

snake::snake(int _x, int _y) {
	head = new snakenode('>',_x,_y);
}
snakenode* snake::getehad() {
	return head;
}
	