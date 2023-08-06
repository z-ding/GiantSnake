#pragma once
#include <vector>
#include "../snake.h"
extern int snakedir;
extern int default_radius;
extern std::vector<std::vector<std::shared_ptr<snakenode>>> grid; //record whether a grid is occupied by something
extern bool shoot;
