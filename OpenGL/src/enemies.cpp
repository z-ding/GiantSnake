#include "enemies.h"
float defaultenemyradius = 1;
enemies::enemies(float centerx, float centery,  int length) {
	center_x = centerx;
	center_y = centery;
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

}
void enemies::drawenemy() {
	for (auto& e : location) {
		drawCircle(e->getter().x, e->getter().y, defaultenemyradius, e->getter().text);
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
	auto target = findMiddleOfList(snakehead);
	float middlex = target->getter().x;
	float middley = target->getter().y;
	float speed = 0.05;
	auto newcenter = interpolate(center_x, center_y, middlex, middley, speed);
	float dx = newcenter.first - center_x;
	float dy = newcenter.second - center_y;
	center_x = newcenter.first;
	center_y = newcenter.second;
	for (auto& e : location) {
		e->nodexysetter(e->getter().x + dx, e->getter().y + dy);
	}
}