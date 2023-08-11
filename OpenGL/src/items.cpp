#include "items.h"
#include "./utils/global.h"
items::items(int _cap, std::unordered_set< std::shared_ptr<snakenode>>& _list) {
	itemlist = _list;
	capacity = _cap;
}
items::~items() {

}
std::unordered_set< std::shared_ptr<snakenode>> items::listgetter() {
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
	std::shared_ptr<snakenode> node = std::make_shared<snakenode>(t, x, y, default_radius);
	itemlist.emplace(node);
	grid[x][y] = node;
}

void items::drawitems() {
	for (auto& e : itemlist) {
		drawCircle(e->getter().x, e->getter().y, default_radius, e->getter().text);
	}
}

void items::removeoneitem(int _x, int _y) {
	std::shared_ptr < snakenode> e = std::make_shared<snakenode>('e');//dummy node
	std::shared_ptr<snakenode> curritem = grid[_x][_y];
	grid[_x][_y] = e;
	itemlist.erase(curritem);
}