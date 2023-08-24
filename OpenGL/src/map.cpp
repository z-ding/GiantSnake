#include "map.h"
#include "./utils/global.h"
map::map(int n) {
	centers.push_back({ 300,300 });
	for (int i = 1; i < n; i++) {
		float randx = rand() % logicalWidth;
		float randy = rand() % logicalHeight;
		auto p = std::make_pair(randx, randy);
		if (find(centers.begin(),centers.end(),p) == centers.end()) {
			centers.push_back(p);
		}
		else {
			while (find(centers.begin(), centers.end(), p) != centers.end()) {
				float randx = rand() % logicalWidth;
				float randy = rand() % logicalHeight;
			}
			centers.push_back(p);
		}
	}
	for (auto& e : centers) {
		auto coordinates = fibonaccispiral(10000, e.first,e.second);
		std::cout << coordinates.size() << std::endl;
		std::shared_ptr<allpurposenode> parentnode = std::make_shared<allpurposenode>('f', coordinates[0].first, coordinates[0].second, 1);
		mp.emplace_back(parentnode);
		for (int i = 1; i < coordinates.size(); i++) {
			int x = coordinates[i].first;
			int y = coordinates[i].second;
			auto node = std::make_shared<allpurposenode>('f', x, y, 1);
			connectnodes(parentnode, node);			
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
			auto screenpos = logicalToScreenCoordinates(cur->getter().x, cur->getter().y);
			drawCircle(screenpos.first, screenpos.second, cur->getter().r, cur->getter().text);
			cur = cur->getter().next;
		}
	}
}