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
	int random = rand() % 4;//random number between 0 and 3
	char t = 'G';
	if (random == 1) t = 'B';
	else if (random == 2) t = 'Y';
	else if (random == 3) t = 'W';
	//generate a random position
	int x = -1;
	int y = -1;
	while (x < 0 || grid[x][y]->getter().text != 'e') {//generate a random position until it's a empty cell
		x = rand() % (grid[0].size() - 30) + 15;
		y = rand() % (grid.size() - 30) + 15;
	}
	std::shared_ptr<allpurposenode> node = std::make_shared<allpurposenode>(t, x, y, default_radius);
	itemlist.emplace(node);
	grid[x][y] = node;
}

void items::drawitems() {
	for (auto& e : itemlist) {
		drawCircle(e->getter().x, e->getter().y, default_radius, e->getter().text);
	}
}

void items::removeoneitem(int _x, int _y) {
	std::shared_ptr < allpurposenode> e = std::make_shared<allpurposenode>('e');//dummy node
	std::shared_ptr<allpurposenode> curritem = grid[_x][_y];
	grid[_x][_y] = e;
	itemlist.erase(curritem);
}