#include "draw.h"
void drawCircle(float x, float y, float radius, char type) {
	const int numSegments = 100;
	glBegin(GL_TRIANGLE_FAN);
	if (type == 'g' || type == 'G') {
		glColor3f(0.0f, 1.0f, 0.0f); // Green color for greenbody
	}
	else if (type == 'b' || type == 'B') {
		glColor3f(0.3, 0.5, 0.902);
	}
	else if (type == 'y' || type == 'Y') {
		glColor3f(1.0f, 0.8f, 0.0f);
	}
	else if (type == 'w' || type == 'W') {
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else if (type == 'e') {//erase: black color
		glColor3f(0.0f, 0.0f, 0.0f);
	}
	else if (type == 'p') {
		glColor3f(1.0f, 0.0f, 0.8f);
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