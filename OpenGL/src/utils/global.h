#pragma once
#include <vector>
#include "../snake.h"
extern int snakedir;
extern int default_radius;
extern int logicalWidth;
extern int logicalHeight;
extern int windowWidth;
extern int windowHeight;
extern std::vector<std::vector<std::shared_ptr<allpurposenode>>> grid; //record whether a grid is occupied by something
extern bool shoot;
extern bool locksnakedir;
extern std::unique_ptr<map> fibonaccimap;
extern std::unique_ptr<snake> player;
extern std::unique_ptr<items> itemlist;
extern std::vector<std::shared_ptr<enemies>> Enemies;
extern std::shared_ptr<allpurposenode> snakeloc;
extern int cap;