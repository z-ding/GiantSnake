#pragma once
#include "node.h"

class items {
private:
	std::unordered_set< std::shared_ptr<snakenode>> itemlist;
	int capacity;//maximum items on the screen
public:
	items(int _cap, std::unordered_set< std::shared_ptr<snakenode>>& _list);//default contructor, create an empty list
	~items();
	void generateoneitem();
	void removeoneitem(int _x, int _y);//after collision with the snakehead
	void drawitems();
	std::unordered_set< std::shared_ptr<snakenode>> listgetter();
	int sizegetter();
};
