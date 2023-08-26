#include "gamelogic.h"
#include "global.h"
void initializeEnemy() {
    for (int i = 0; i < amountEnemy; i++) {
        int randx = 30 + (rand() % (logicalWidth - 60));
        int randy = 30 + (rand() % (logicalHeight - 60));
        Enemies.emplace_back(std::make_shared<enemies>(randx, randy, 10, i));
    }
}
void initializegame() {
    std::shared_ptr < allpurposenode> empty = std::make_shared<allpurposenode>('e');//dummy node
    fillgrid(logicalWidth, logicalHeight, empty);
    fibonaccimap = std::make_unique<map>(5
    );
    snakeloc = fibonaccimap->mp[0];
    player = std::make_unique<snake>(snakeloc -> getter().x,snakeloc->getter().y);
    std::unordered_set< std::shared_ptr<allpurposenode>> emptylist;
    cap = 10;
    itemlist = std::make_unique<items>(cap, emptylist);
    initializeEnemy();
}

void updategame() {
    if (itemlist->sizegetter() < cap) {
        itemlist->generateoneitem();
    }
    bool showshootline = player->shooting(Enemies);//shoot if space key is pressed
    currentTime = glfwGetTime();
    if (currentTime - lastMoveTime >= MOVE_INTERVAL) {
        player->move(itemlist, snakeloc, fibonaccimap); // Update the snake's position
        for (auto& e : Enemies) {
            e->move(player->gethead());
            e->rotate();//move and rotate the enemy
            if (e->kill(player->gethead())) {
                player->alive = false;
                gameover = true;
                //std::cout << "killed by enemy gameover" << std::endl;
                //return;
            }
        }
        lastMoveTime = currentTime; // Reset the timer
        if (!Enemies.size()) {//enemy killed
            std::cout << "go to next stage via top of the screen" << std::endl;
            allowextension = true;
            
        }
    }
    if (gameover) {
        std::cout << "gameover" << std::endl;
        return;
    }
}

void render() {
    fibonaccimap->drawMap();
    player->displayshootline();
    currentTime = glfwGetTime();    // Draw the items and snake
    itemlist->drawitems();
    player->drawsnake();
    for (auto& e : Enemies) {
        e->drawenemy();
    }
}

void nextstageinitialze() {
    Enemies.clear();
    amountEnemy++;
    itemlist->clearitems();
    fibonaccimap = std::make_unique<map>(3);   
    initializeEnemy();
}