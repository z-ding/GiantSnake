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
snode snakenode::getter() {
	return { x,y, r,text,prev,next};
};
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

void snake::emplace_back() {//add a node on the back
	std::shared_ptr<snakenode> node = std::make_shared<snakenode>('g');//green body node
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
	