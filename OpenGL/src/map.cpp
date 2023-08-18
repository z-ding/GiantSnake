#include "map.h"
#include "./utils/global.h"
map::map(int n) {
	centers.insert({ 300,300 });
	for (int i = 1; i < n; i++) {
		float randx = rand() % grid[0].size();
		float randy = rand() % grid.size();
		auto p = std::make_pair(randx, randy);
		if (centers.find(p) == centers.end()) {
			centers.insert(p);
		}
		else {
			while (centers.find(p) != centers.end()) {
				float randx = rand() % grid[0].size();
				float randy = rand() % grid.size();
			}
			centers.insert(p);
		}
	}
	for (auto& e : centers) {
		auto coordinates = fibonaccispiral(1000,10
			, e.first,e.second,10.0);
		std::shared_ptr<allpurposenode> parentnode;
		for (int i = 0; i < coordinates.size(); i++) {
			int x = coordinates[i].first;
			int y = coordinates[i].second;
			auto node = std::make_shared<allpurposenode>('f', x, y, 1);
			if (i == 0) {
				mp.push_back(node);				
			}
			else {
				connectnodes(parentnode, node);
			}
			parentnode = node;
		}
	}
}
map::~map() {

}
void map::drawMap() {
	for (auto& e : mp) {
		auto cur = e;
		while (cur != nullptr) {
			drawCircle(cur->getter().x, cur->getter().y, cur->getter().r, cur->getter().text);
			cur = cur->getter().next;
		}
	}
}