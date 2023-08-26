#include "enemies.h"
#include "./utils/global.h"
float defaultenemyradius = 1;
enemies::enemies(float centerx, float centery,  int length, int _type) {
	center_x = centerx;
	center_y = centery;
	type = _type;
	auto up = std::make_shared<allpurposenode>('x', centerx, centery + 1, defaultenemyradius);
	auto down = std::make_shared<allpurposenode>('x', centerx, centery - 1, defaultenemyradius);
	auto left = std::make_shared<allpurposenode>('x', centerx-1, centery, defaultenemyradius);
	auto right = std::make_shared<allpurposenode>('x', centerx + 1, centery, defaultenemyradius);
	location.emplace(up);
	location.emplace(down);
	location.emplace(left);
	location.emplace(right);
	//build the X shape in 4 directions
	auto prevnode = up;
	for (int j = 2; j <= length; j++) {
		auto tmp =std::make_shared<allpurposenode>('x', centerx, centery+j, defaultenemyradius);
		connectnodes(prevnode, tmp);
		prevnode = tmp;
		location.emplace(tmp);
	}
	prevnode = down;
	for (int j = 2; j <= length; j++) {
		auto tmp = std::make_shared<allpurposenode>('x', centerx, centery - j, defaultenemyradius);
		connectnodes(prevnode, tmp);
		prevnode = tmp;
		location.emplace(tmp);
	}
	prevnode = left;
	for (int j = 2; j <= length; j++) {
		auto tmp = std::make_shared<allpurposenode>('x', centerx-j, centery, defaultenemyradius);
		connectnodes(prevnode, tmp);
		prevnode = tmp;
		location.emplace(tmp);
	}
	prevnode = right;
	for (int j = 2; j <= length; j++) {
		auto tmp = std::make_shared<allpurposenode>('x', centerx + j, centery, defaultenemyradius);
		connectnodes(prevnode, tmp);
		prevnode = tmp;
		location.emplace(tmp);
	}
}
enemies::~enemies() {
	// std::cout << "enemy destroyed" << std::endl;
}

std::pair<float, float> enemies::getcenter() {
	return { center_x,center_y };
};
void enemies::drawenemy() {
	for (auto& e : location) {
		auto screenpos = logicalToScreenCoordinates(e->getter().x, e->getter().y);
		drawCircle(screenpos.first, screenpos.second, defaultenemyradius, e->getter().text,100);
	}
}
void enemies::rotate() {
	float angle = 30.0; // 30 degree
	for (auto& e : location) {
		std::pair<float,float> newxy = rotatePoint(e->getter().x, e->getter().y,center_x, center_y,angle);
		e->nodexysetter(newxy.first, newxy.second);
	}
}
void enemies::move(std::shared_ptr<allpurposenode> snakehead) {
	float middlex;
	float middley;
	if (type == 0) {//chase a random body node
		auto target = findRandomNodeOfList(snakehead);
		middlex = target->getter().x;
		middley = target->getter().y;
	}
	else if (type == 1) {//chase the middle of the snake body
		auto target = findMiddleOfList(snakehead);
		middlex = target->getter().x;
		middley = target->getter().y;
	}
	else {//move randomly
		middlex = rand() % logicalWidth;
		middley = rand() % logicalHeight;
	}
	float speed = 0.1;
	auto newcenter = interpolate(center_x, center_y, middlex, middley, speed);
	float dx = newcenter.first - center_x;
	float dy = newcenter.second - center_y;
	center_x = newcenter.first;
	center_y = newcenter.second;
	for (auto& e : location) {
		e->nodexysetter(e->getter().x + dx, e->getter().y + dy);
	}
}
bool enemies :: kill(std::shared_ptr<allpurposenode> snakehead) {
	if (locksnakedir) {
		return false; //snake wouldn't be killed if it's travelling on the fibonacci circle 
	}
	for (auto& e : location) {
		float ex = e->getter().x;
		float ey = e->getter().y;
		auto cur = snakehead;
		while (cur != nullptr) {
			float snakex = cur->getter().x;
			float snakey = cur->getter().y;
			if ((ex - snakex) * (ex - snakex) + (ey - snakey) * (ey - snakey) < (defaultenemyradius + cur->getter().r) * (defaultenemyradius + cur->getter().r)) {
				return true;
			}
			cur = cur->getter().next;
		}
	}
	return false;
}



