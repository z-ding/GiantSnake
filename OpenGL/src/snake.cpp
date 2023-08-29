#include "snake.h"
#include "./utils/global.h"
//snake

int default_radius = 5;
int logicalWidth = 600;
int logicalHeight
= 600;
int windowWidth = 600;
int windowHeight = 600;
bool checkPerfect = false;
std::unordered_map<char, int> colorToShape = {
	{'g',4},
	{'b',3},
	{'y',100},
	{'w',4},
	{'o',3},
	{'v',100},
	{'h',6}
};
std::vector<std::vector<std::shared_ptr<allpurposenode>>> grid;
void fillgrid(int x, int y, std::shared_ptr < allpurposenode> s) {
	for (int i = 0; i <= x; i++) {
		std::vector<std::shared_ptr<allpurposenode>> v;
		for (int j = 0; j <= y; j++) {
			v.push_back(s);			
		}
		grid.push_back(v);
	}
}

snake::snake(int _x, int _y) {	
	head = std::make_shared<allpurposenode>('h', _x, _y, default_radius);
	tail = head;
	alive = true;
	grid[_x][_y] = head;//snake
}
snake::~snake() {

}
std::shared_ptr<allpurposenode> snake::gethead() {
	return head;
}
std::shared_ptr<allpurposenode> snake::gettail() {
	return tail;
}
void snake::emplace_back(float x, float y, char t) {//add a node on the back
	std::shared_ptr<allpurposenode> node = std::make_shared<allpurposenode>(t, x, y, default_radius);//green body node
	grid[x][y] = node;//snake
	connectnodes(tail, node);
	tail = node;
}

void snake::move(std::unique_ptr<items> &itemlist,  std::shared_ptr<allpurposenode> &curloc, std::unique_ptr<map> &fibonaccimap) {
	shootline.clear();
	// Move the snake
	float dx = 0, dy = 0;
	float speed = default_radius*2;
	auto cur = curloc;
	switch (snakedir) {
	case -4: //follow the fibonacci next ptrs
		if (curloc->getter().next != nullptr) {
			float curx = cur->getter().x;
			float cury = cur->getter().y;
			cur = cur->getter().next;
			curloc = cur;
			float nextx = cur->getter().x;
			float nexty = cur->getter().y;
			dx = nextx - curx;
			dy = nexty - cury;
			//std::cout << dx << "," << dy << std::endl;
		}
		else {
			locksnakedir = false;//force user to move after reaching the end
		}
		break;
	case 4://follow the fibonacci prev ptrs
		if (curloc->getter().prev != nullptr) {
			float curx = cur->getter().x;
			float cury = cur->getter().y;
			cur = cur->getter().prev;
			curloc = cur;
			float nextx = cur->getter().x;
			float nexty = cur->getter().y;
			dx = nextx - curx;
			dy = nexty - cury;
		}
		else {
			locksnakedir = false;//force user to move after reaching the end
		}
		break;
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
	cur = head;
	std::shared_ptr < allpurposenode> e = std::make_shared<allpurposenode>('e');//dummy nodem
	float prevx = cur->getter().x;
	float prevy = cur->getter().y;
	float nextx = prevx + dx;
	float nexty = prevy + dy;
	if (allowextension && nexty <= default_radius) {//next stage, y reducing, but suddenly increase. when tails y> head's y, extension finishes
		nexty = logicalHeight - default_radius-1;
		nextstageinitialze();
	}
	checkalive(nextx, nexty);//check whether new head location is valid
	//lock snake dir if next location is the center of a fibonacci spiral
	for (auto& e : fibonaccimap->mp) {
		float cx = e->getter().x;
		float cy = e->getter().y;
		if ((nextx - cx) * (nextx - cx) + (nexty - cy) * (nexty - cy) < (1 + default_radius) * (1 + default_radius)) {
			snakedir = -4;
			locksnakedir = true;
			curloc = e;
			break;
		}
	}
	if (!alive) return;
	char itemt = 'X';
	for (auto& e : itemlist->listgetter()) {
		int itemx = e->getter().x;
		int itemy = e->getter().y;
		if ((nextx - itemx) * (nextx - itemx) + (nexty - itemy) * (nexty - itemy) < 4 * default_radius * default_radius) {
			addlen = true;
			itemt = e->getter().text;
			//remove the item
			itemlist->removeoneitem(e);
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
		checkPerfect = true;
	}
	if (allowextension && tail->getter().y >= head->getter().y) allowextension = false;
	//std::cout << "moving " << headx + dx << "," << heady + dy << std::endl;
}
void snake::checkalive(float x, float y) {
	if (x < default_radius || y < default_radius || x >= logicalWidth - default_radius || y >= logicalHeight - default_radius) {//
		//std::cout << "snake game over" << std::endl;
		alive = false;
		gameover = true;
		return;
	}
	
	int ascii = int(grid[x][y]->getter().text);
	if (ascii >= 97 && ascii <= 122 && grid[x][y]->getter().text != 'e') {//snake head meet body node
		//std::cout << "snake game over" << std::endl;
		std::cout << ascii << std::endl;
		alive = false;
		gameover = true;
		return;
	}
	         
};
void snake::erase(float x, float y) {
	auto noneed = grid[x][y];
	//std::cout << "shooting at" << x << "," << y << std::endl;
	std::shared_ptr<allpurposenode> prevnodes = grid[x][y]->getter().prev;
	std::shared_ptr<allpurposenode> nextnodes = grid[x][y]->getter().next;
	std::shared_ptr < allpurposenode> e = std::make_shared<allpurposenode>('e');//dummy node
	if (nextnodes == nullptr) {//shoot on tail, set prenodes as tail	
		tail = tail->getter().prev;
		prevnodes->getter().next = nullptr;
		grid[x][y] = e;
	}
	else {
		connectnodes(prevnodes, nextnodes);
		//update the x,y coordinate info for next nodes
		auto cur = nextnodes;
		int prevx = grid[x][y]->getter().x;
		int prevy = grid[x][y]->getter().y;
		grid[x][y] = e;
		while (cur != nullptr) {
			int nextx = cur->getter().x;
			int nexty = cur->getter().y;
			grid[nextx][nexty] = e;
			//std::cout << "cleared at" << nextx << "," << nexty << std::endl;
			cur->nodexysetter(prevx, prevy);
			grid[prevx][prevy] = cur;
			//std::cout << "filledd at" << prevx << "," << prevy << std::endl;
			prevx = nextx;
			prevy = nexty;
			cur = cur->getter().next;

		}
	}
	std::cout << tail->getter().text << std::endl;
	noneed.reset();
}
bool snake::shooting(std::vector<std::shared_ptr<enemies>> &Enemies) {
	if (shoot ) {//&& !allowextension
		float headx = head->getter().x;
		float heady = head->getter().y;
		bool shootself = true;
		switch (snakedir) {
		case 1://down
			for (int i = Enemies.size() - 1; i >= 0; i--) {
				if (abs(Enemies[i]->getcenter().first - headx) < 10 && Enemies[i]->getcenter().second > heady) {
					Enemies.erase(Enemies.begin() + i);
				}
			}

			for (float i = heady + 1; i < logicalHeight; i += 1) {
				if (shootself && grid[headx][i]-> getter().text != 'e') {//erase this node
					erase(headx, i);
					checkPerfect = true;
					shootself = false;
				}
				shootline.push_back({ headx,i });
			}
			break;
		case 0://up
			for (int i=Enemies.size()-1; i>=0;i--) {
				if (abs(Enemies[i]->getcenter().first - headx) < 10 && Enemies[i]->getcenter().second < heady) {
					Enemies.erase(Enemies.begin()+i);
				}
			}
			for (float i = heady - 1; i >=0; i -= 1) {
				if (shootself && grid[headx][i]->getter().text != 'e') {//erase this node
					erase(headx, i);
					checkPerfect = true;
					shootself = false;
					//break;
				}
				shootline.push_back({ headx,i });
			}
			break;
		case 2://left
			for (int i = Enemies.size() - 1; i >= 0; i--) {
				if (abs(Enemies[i]->getcenter().second - heady) < 10 && Enemies[i]->getcenter().first < headx) {
					Enemies.erase(Enemies.begin() + i);
				}
			}
			for (float i = headx - 1; i >= 0; i -= 1) {
				if (shootself && grid[i][heady]->getter().text != 'e') {//erase this node
					erase(i, heady);
					checkPerfect = true;
					shootself = false;
					//break;
				}
				shootline.push_back({ i,heady });
			}
			break;
		case 3://right
			for (int i = Enemies.size() - 1; i >= 0; i--) {
				if (abs(Enemies[i]->getcenter().second - heady) < 10 && Enemies[i]->getcenter().first > headx) {
					Enemies.erase(Enemies.begin() + i);
				}
			}
			for (float i = headx + 1; i < logicalWidth; i += 1) {
				if (shootself && grid[i][heady]->getter().text != 'e') {//erase this node
					erase(i, heady);
					checkPerfect = true;
					shootself = false;
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
	std::shared_ptr<allpurposenode> current = head;
	while (current != nullptr) {//simulation, moving upwnward
		snode node = current->getter();
		auto screenpos = logicalToScreenCoordinates(node.x, node.y);
		drawCircle(screenpos.first, screenpos.second, default_radius, node.text,colorToShape[node.text]);
		current = node.next;
	}
};
void snake::displayshootline() {
	//if (shootline.size()) std::cout << shootline.size() << std::endl;
	for (int i = 0; i < shootline.size(); i++) {
		auto screenpos = logicalToScreenCoordinates(shootline[i].first, shootline[i].second);
		drawCircle(screenpos.first, screenpos.second, 1.0, 'p',100);
	}
}
/*
a perfect snake can be splitted into subarrays of either
	1. The subarray consists of exactly 2 same elements (same color and shape)
	2. The subarray consists of exactly 3 same elements (same color and shape)
	3. The subarray consists of exactly 3 same shape elements
*/

bool dfs(std::vector<char>& nums, int startpos, int len, std::vector<std::vector<int>> &memo) {
	if (startpos >= nums.size() && len == 0) return true;
	if (startpos + len >= nums.size()) return false;
	if (len > 2) return false;
	if (memo[startpos][len] != -1) return memo[startpos][len];
	bool res = false;
	if (len == 1) {
		if (nums[startpos] == nums[startpos + 1]) {
			res = res || dfs(nums, startpos + 2, 0,memo);
		}
	}
	else if (len == 2) {
		if (nums[startpos] == nums[startpos + 1] && nums[startpos] == nums[startpos + 2]) {
			res = res || dfs(nums, startpos + 3, 0,memo);
		}
		else if (colorToShape[nums[startpos]] == colorToShape[nums[startpos + 1]] && colorToShape[nums[startpos]] == colorToShape[nums[startpos + 2]]) {
			res = res || dfs(nums, startpos + 3, 0,memo);
		}
	}
	memo[startpos][len] = res || dfs(nums, startpos, len + 1,memo);
	return memo[startpos][len];
}
bool snake::isPerfect() {
	auto cur = head -> getter().next;
	std::vector<char> v;
	while (cur != nullptr) {
		v.push_back(cur->getter().text);
		cur = cur->getter().next;
	}
	std::vector<std::vector<int>> memo(v.size() + 2, { -1,-1,-1 });
	bool perfect = dfs(v, 0, 0, memo);
	return perfect;
}

