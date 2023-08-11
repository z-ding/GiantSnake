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
	shootline.clear();
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
bool snake::shooting() {
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
					//break;
				}
				shootline.push_back({ headx,i });
			}
			break;
		case 2://left
			for (float i = headx - 1; i >= 0; i -= 1) {
				if (grid[i][heady]->getter().text != 'e') {//erase this node
					erase(i, heady);
					//break;
				}
				shootline.push_back({ i,heady });
			}
			break;
		case 3://right
			for (float i = headx + 1; i < grid[0].size(); i += 1) {
				if (grid[i][heady]->getter().text != 'e') {//erase this node
					erase(i, heady);
					//break;
				}
				shootline.push_back({ i,heady });
			}
			break;
		}
		shoot = false;
		return true;
	}	
	return false;
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
	//if (shootline.size()) std::cout << shootline.size() << std::endl;
	for (int i = 0; i < shootline.size(); i++) {
		drawCircle(shootline[i].first, shootline[i].second, 1.0, 'p');
	}
}


