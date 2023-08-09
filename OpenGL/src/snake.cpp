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

void snake::move(std::shared_ptr<items> itemlist) {
	// Move the snake
	float dx = 0, dy = 0;
	float speed = default_radius*2;
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
	std::shared_ptr < snakenode> e = std::make_shared<snakenode>('e');//dummy nodem
	float prevx = cur->getter().x;
	float prevy = cur->getter().y;
	float nextx = prevx + dx;
	float nexty = prevy + dy;
	checkalive(nextx, nexty);//check whether new head location is valid
	if (!alive) return;
	char itemt;
	for (auto& e : itemlist->listgetter()) {
		int itemx = e->getter().x;
		int itemy = e->getter().y;
		if ((nextx - itemx) * (nextx - itemx) + (nexty - itemy) * (nexty - itemy) < 4 * default_radius * default_radius) {
			addlen = true;
			itemt = e->getter().text;
			//remove the item
			itemlist->removeoneitem(itemx, itemy);
			break;
		}
	}
	while (cur != nullptr) {
		prevx = cur->getter().x;
		prevy = cur->getter().y;
		grid[prevx][prevy] = e;//clear prev loc
		cur->nodexysetter(nextx, nexty);
		grid[nextx][nexty] = cur;//mark current loc as snake
		nextx = prevx;
		nexty = prevy;
		cur = cur->getter().next;
	}

	if (addlen) {//add a body node at the next loc and set it as tail
		this->emplace_back(nextx, nexty,char(int(itemt)+32));
		addlen = false;
	}
	//std::cout << "moving " << headx + dx << "," << heady + dy << std::endl;
}
void snake::checkalive(float x, float y) {
	int ascii = int(grid[x][y]->getter().text);
	if (ascii >= 65 && ascii <= 90) return;//collision with an item
	if (x <= 0 || y <= 0 || x >= grid[0].size() || y >= grid.size() || grid[x][y] -> getter().text != 'e') {
		std::cout << "game over" << std::endl;
		alive = false;
		return;
	}

};
void snake::erase(float x, float y) {
	std::shared_ptr<snakenode> prevnodes = grid[x][y]->getter().prev;
	std::shared_ptr<snakenode> nextnodes = grid[x][y]->getter().next;
	std::shared_ptr < snakenode> e = std::make_shared<snakenode>('e');//dummy node
	if (nextnodes == nullptr) {//shoot on tail, set prenodes as tail
		tail = prevnodes;
		grid[x][y] = e;
	}
	else {
		connectnodes(prevnodes, nextnodes);
		//update the x,y coordinate info for next nodes
		auto cur = nextnodes;
		int prevx = grid[x][y]->getter().x;
		int prevy = grid[x][y]->getter().y;
		while (cur != nullptr) {
			int nextx = cur->getter().x;
			int nexty = cur->getter().y;
			grid[nextx][nexty] = e;
			cur->nodexysetter(prevx, prevy);
			grid[prevx][prevy] = cur;
			prevx = nextx;
			prevy = nexty;
			cur = cur->getter().next;
		}
	}	
}
void snake::shooting() {
	if (shoot) {	
		float headx = head->getter().x;
		float heady = head->getter().y;
		switch (snakedir) {
		case 1://down
			for (float i = heady + 1; i < grid.size(); i += 1) {
				if (grid[headx][i]-> getter().text != 'e') {//erase this node
					erase(headx, i);
				}
				shootline.push_back({ headx,i });
			}
			break;
		case 0://up
			for (float i = heady - 1; i >=0; i -= 1) {
				if (grid[headx][i]->getter().text != 'e') {//erase this node
					erase(headx, i);
					break;
				}
				shootline.push_back({ headx,i });
			}
			break;
		case 2://left
			for (float i = headx - 1; i >= 0; i -= 1) {
				if (grid[i][heady]->getter().text != 'e') {//erase this node
					erase(i, heady);
					break;
				}
				shootline.push_back({ i,heady });
			}
			break;
		case 3://right
			for (float i = headx + 1; i < grid[0].size(); i += 1) {
				if (grid[i][heady]->getter().text != 'e') {//erase this node
					erase(i, heady);
					break;
				}
				shootline.push_back({ i,heady });
			}
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
void snake::displayshootline() {
	for (int i = 0; i < shootline.size(); i++) {
		drawCircle(shootline[i].first, shootline[i].second, 2.0, 'p');
	}
	shootline.clear();
}

items::items(int _cap, std::unordered_set< std::shared_ptr<snakenode>> &_list) {
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
		x = rand() % (grid[0].size()-30)+15;
		y = rand() % (grid.size()-30)+15;
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
