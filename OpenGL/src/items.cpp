#include "items.h"
#include "./utils/global.h"
items::items(int _cap, std::unordered_set< std::shared_ptr<allpurposenode>>& _list) {
	itemlist = _list;
	capacity = _cap;
}
items::~items() {

}
std::unordered_set< std::shared_ptr<allpurposenode>> items::listgetter() {
	return itemlist;
}
int items::sizegetter() {
	return itemlist.size();
};
void items::generateoneitem() {
	char t = randomcolorgenerator();
	//generate a random position
	int x = -1;
	int y = -1;
	while (x < 0 || grid[x][y]->getter().text != 'e') {//generate a random position until it's a empty cell
		x = rand() % (logicalWidth - 30) + 15;
		y = rand() % (logicalHeight - 30) + 15;
	}
	std::shared_ptr<allpurposenode> node = std::make_shared<allpurposenode>(t, x, y, default_radius);
	itemlist.emplace(node);
	grid[x][y] = node;
}

void items::drawitems() {
	for (auto& e : itemlist) {
		drawCircle(e->getter().x, e->getter().y, default_radius, e->getter().text,colorToShape[char(int(e->getter().text) + 32)]);
	}
}

void items::removeoneitem(int _x, int _y) {
	std::shared_ptr < allpurposenode> e = std::make_shared<allpurposenode>('e');//dummy node
	std::shared_ptr<allpurposenode> curritem = grid[_x][_y];
	grid[_x][_y] = e;
	itemlist.erase(curritem);
}
void items::clearitems() {
	std::shared_ptr < allpurposenode> empty = std::make_shared<allpurposenode>('e');//dummy node
	for (auto &e : itemlist) {
		float x = e->getter().x;
		float y = e->getter().y;
		grid[x][y] = empty;
	}
	itemlist.clear();
}