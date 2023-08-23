#pragma once
#include "node.h"
#include "./utils/math.h"
#include <vector>
#include <set>

class map {
public:
	std::vector<std::shared_ptr<allpurposenode>> mp;
	std::vector<std::pair<float, float>> centers;
	map(int n);
	~map();
	void drawMap();
};
