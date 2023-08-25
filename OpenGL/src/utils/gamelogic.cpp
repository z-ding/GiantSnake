#include "gamelogic.h"
#include "global.h"
void initializegame() {
    std::shared_ptr < allpurposenode> empty = std::make_shared<allpurposenode>('e');//dummy node
    fillgrid(logicalWidth, logicalHeight, empty);
    fibonaccimap = std::make_unique<map>(5
    );
    snakeloc = fibonaccimap->mp[0];
    player = std::make_unique<snake>(windowWidth / 2, windowHeight / 2);
    std::unordered_set< std::shared_ptr<allpurposenode>> emptylist;
    cap = 10;
    itemlist = std::make_unique<items>(cap, emptylist);
    Enemies;
    Enemies.emplace_back(std::make_shared<enemies>(30, 30, 20, 0));
    Enemies.emplace_back(std::make_shared<enemies>(570, 570, 20, 1));
    Enemies.emplace_back(std::make_shared<enemies>(30, 570, 20, 2));
    Enemies.emplace_back(std::make_shared<enemies>(570, 30, 20, 2));
}