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
void connectnodes(snakenode* n1, snakenode* n2) {
	n1->next = n2;
	n2->prev = n1;
};

snake::snake(int _x, int _y) {
	head = new snakenode('h',_x,_y);
	tail = head;
}
snakenode* snake::gethead() {
	return head;
}
snakenode* snake::gettail() {
	return tail;
}

void snake::emplace_back() {//add a node on the back
	snakenode* node = new snakenode('g');//green body node
	connectnodes(tail, node);
	tail = node;
}
void drawCircle(float x, float y, float radius, char type) {
	const int numSegments = 100;
	glBegin(GL_TRIANGLE_FAN);
	if (type =='g') {
		glColor3f(0.0f, 1.0f, 0.0f); // Green color for greenbody
	}
	else {
		glColor3f(1.0f, 0.0f, 0.0f); // Red color for snake head
	}
	glVertex2f(x, y);
	for (int i = 0; i <= numSegments; i++) {
		float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);
		float dx = radius * cosf(theta);
		float dy = radius * sinf(theta);
		glVertex2f(x + dx, y + dy);
	}
	glEnd();
}

void snake::drawsnake() {
	snakenode* current = head;
	int prevx = 0.0f;
	int prevy = 0.0f;
	while (current != nullptr) {//simulation, moving upwnward
		std::tuple<int, int, char, snakenode*, snakenode*> info = current->getter();
		if (current == head) drawCircle(prevx, prevy, 0.05f, std::get<2>(info));
		else {
			drawCircle(prevx, prevy-0.1f, 0.05f,std::get<2>(info));
		}
		current = std::get<4>(info);
		prevy = prevy - 0.1f;
	}
};
	