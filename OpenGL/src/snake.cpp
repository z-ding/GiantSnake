#include "snake.h"
#include "./utils/global.h"

int default_radius = 10;
std::vector<std::vector<std::shared_ptr<snakenode>>> grid;
void fillgrid(int x, int y, std::shared_ptr < snakenode> s) {
	for (int i = 0; i <= x; i++) {
		std::vector<std::shared_ptr<snakenode>> v;
		for (int j = 0; j <= y; j++) {
			v.push_back(s);			
		}
		grid.push_back(v);
	}
}

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
snakenode::snakenode(char c, int _x, int _y, int _r) {
	text = c;
	x = _x;
	y = _y;
	r = _r;
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
	head = std::make_shared<snakenode>('h', _x, _y, default_radius);
	tail = head;
	alive = true;
	grid[_x][_y] = head;//snake
	addlen = true;
}
snake::~snake() {

}
std::shared_ptr<snakenode> snake::gethead() {
	return head;
}
std::shared_ptr<snakenode> snake::gettail() {
	return tail;
}
void snake::emplace_back(float x, float y, char t) {//add a node on the back
	std::shared_ptr<snakenode> node = std::make_shared<snakenode>(t, x, y, default_radius);//green body node
	grid[x][y] = node;//snake
	connectnodes(tail, node);
	tail = node;
}

void snake::move() {
	// Move the snake
	float dx = 0, dy = 0;
	float speed = default_radius * 2;
	switch (snakedir) {
	case 0://up
		dy = -speed;
		break;
	case 1://down
		dy = speed;
		break;
	case 2://left
		dx = -speed;
		break;
	case 3://right
		dx = speed;
		break;
	}
	std::shared_ptr<snakenode> cur = head;
	float prevx = cur->getter().x;
	float prevy = cur->getter().y;
	float nextx = prevx + dx;
	float nexty = prevy + dy;
	checkalive(nextx, nexty);//check whether new head location is valid
	if (!alive) return;
	while (cur != nullptr) {
		prevx = cur->getter().x;
		prevy = cur->getter().y;
		std::shared_ptr < snakenode> e = std::make_shared<snakenode>('e');//dummy node
		grid[prevx][prevy] = e;//clear prev loc
		cur->nodexysetter(nextx, nexty);
		grid[nextx][nexty] = cur;//mark current loc as snake
		nextx = prevx;
		nexty = prevy;
		cur = cur->getter().next;
	}
	if (addlen) {//add a body node at the next loc and set it as tail
		int x = rand() % 4;//random number between 0 and 3
		char t = 'g';
		if (x == 1) t = 'b';
		else if (x == 2) t = 'y';
		else if (x == 3) t = 'w';
		this->emplace_back(nextx, nexty,t);
	}
	//std::cout << "moving " << headx + dx << "," << heady + dy << std::endl;
}
void snake::checkalive(float x, float y) {
	if (x <= 0 || y <= 0 || x >= grid[0].size() || y >= grid.size() || grid[x][y] -> getter().text != 'e') {
		std::cout << "game over" << std::endl;
		alive = false;
		return;
	}

};
void snake::erase(float x, float y) {
	std::shared_ptr<snakenode> prevnodes = grid[x][y]->getter().prev;
	std::shared_ptr<snakenode> nextnodes = grid[x][y]->getter().next;
	if (nextnodes == nullptr) {//shoot on tail, set prenodes as tail
		tail = prevnodes;
	}
	else {
		connectnodes(prevnodes, nextnodes);
	}	
}
void snake::shooting() {
	if (shoot) {	
		float headx = head->getter().x;
		float heady = head->getter().y;
		switch (snakedir) {
		case 0://up
			std::cout << "shooting" << std::endl;
			this->addlen = false;
			for (float i = heady + 1; i < grid.size(); i += 1) {
				if (grid[headx][i]-> getter().text != 'e') {//erase this node
					erase(headx, i);
					break;
				}
			}
			break;
		case 1://down
			break;
		case 2://left
			break;
		case 3://right
			break;
		}
	}
	
	shoot = false;//shooting complete
}


void snake::drawsnake() {
	std::shared_ptr<snakenode> current = head;
	while (current != nullptr) {//simulation, moving upwnward
		snode node = current->getter();
		drawCircle(node.x, node.y, default_radius, node.text);
		current = node.next;
	}
};
	