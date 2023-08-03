#include "snake.h"
#include "./utils/global.h"
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
snode snakenode::getter() {
	return { x,y, r,text,prev,next};
};
void snakenode::nodexysetter(float _x, float _y) {
	x = _x;
	y = _y;
}
void connectnodes(std::shared_ptr<snakenode> n1, std::shared_ptr<snakenode> n2) {
	n1 -> next = n2;
	n2->prev = n1;
};

snake::snake(int _x, int _y) {	
	head = std::make_shared<snakenode>('h', _x, _y);
	tail = head;
}
snake::~snake() {

}
std::shared_ptr<snakenode> snake::gethead() {
	return head;
}
std::shared_ptr<snakenode> snake::gettail() {
	return tail;
}
void snake::move(float f) {
	// Move the snake
	float dx = 0, dy = 0;
	std::cout << "moving " << snakedir << std::endl;
	switch (snakedir) {
	case 0://up
		dy = f;
		break;
	case 1://down
		dy = -f;
		break;
	case 2://left
		dx = -f;
		break;
	case 3://right
		dx = f;
		break;
	}
	float headx = head->getter().x;
	float heady = head->getter().y;
	head->nodexysetter(headx + dx, heady + dy);
}
void snake::emplace_back() {//add a node on the back
	std::shared_ptr<snakenode> node = std::make_shared<snakenode>('g');//green body node
	connectnodes(tail, node);
	tail = node;
}


void snake::drawsnake(float prevx, float prevy) {
	std::shared_ptr<snakenode> current = head;
	while (current != nullptr) {//simulation, moving upwnward
		snode node = current->getter();
		if (current != head) {
			prevy -= 0.1f;			
		}
		drawCircle(prevx, prevy, 0.05f, node.text);
		current = node.next;
	}
};
	