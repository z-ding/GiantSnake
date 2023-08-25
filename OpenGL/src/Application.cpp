#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include "node.h"
#include "snake.h"
#include "items.h"
#include "enemies.h"
#include "map.h"
#include "utils/inputhandler.h"
#include "utils/global.h"
#include "utils/gamelogic.h"
#include <WinSock2.h>
#define MOVE_INTERVAL 0.5
// Adjust the speed by changing this value
std::unique_ptr<map> fibonaccimap;
std::unique_ptr<snake> player;
std::unique_ptr<items> itemlist;
std::vector<std::shared_ptr<enemies>> Enemies;
std::shared_ptr<allpurposenode> snakeloc;
int cap;
int main(void)
{


    GLFWwindow* window;
    double lastMoveTime = glfwGetTime();
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(windowWidth, windowHeight, "Giant Snake", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, keyboardCallback);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, windowWidth, windowHeight, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (glewInit() != GLEW_OK) {
        std::cout << "error glew init" << std::endl;
    }
    /* Loop until the user closes the window */
    initializegame();
    while (!glfwWindowShouldClose(window) && player -> alive)
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        fibonaccimap->drawMap();
        if (itemlist->sizegetter() < cap) {
            itemlist->generateoneitem();
        }
        bool showshootline = player->shooting(Enemies);//shoot if space key is pressed
        player->displayshootline();
        //move snake

        double currentTime = glfwGetTime();
        if (currentTime - lastMoveTime >= MOVE_INTERVAL) {
            player->move(itemlist, snakeloc,fibonaccimap); // Update the snake's position
            for (auto& e : Enemies) {
                e->move(player->gethead());
                e->rotate();//move and rotate the enemy
                if (e->kill(player->gethead())) {
                    player->alive = false;
                    std::cout << "killed by enemy gameover" << std::endl;
                    return 0;
                }
                e->movebullet();
            }
            lastMoveTime = currentTime; // Reset the timer
        }        
        // Draw the items and snake
        itemlist->drawitems();
        player->drawsnake();
        for (auto& e : Enemies) {
            e->drawenemy();
            e->drawbullets();

        }
        currentTime = glfwGetTime();                         
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}