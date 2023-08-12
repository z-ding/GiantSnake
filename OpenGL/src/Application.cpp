#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include "node.h"
#include "snake.h"
#include "items.h"
#include "enemies.h"
#include "utils/inputhandler.h"
#define WIDTH 600
#define HEIGHT 600
#define MOVE_INTERVAL 0.5
// Adjust the speed by changing this value

int main(void)
{
    GLFWwindow* window;
    double lastMoveTime = glfwGetTime();
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WIDTH, HEIGHT, "Giant Snake", NULL, NULL);
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
    glOrtho(0, WIDTH, HEIGHT, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (glewInit() != GLEW_OK) {
        std::cout << "error glew init" << std::endl;
    }
    /* Loop until the user closes the window */
    std::shared_ptr < allpurposenode> empty = std::make_shared<allpurposenode>('e');//dummy node
    fillgrid(WIDTH, HEIGHT, empty);

    std::unique_ptr<snake> player = std::make_unique<snake>(WIDTH / 2, HEIGHT / 2);
    std::unordered_set< std::shared_ptr<allpurposenode>> emptylist;
    int cap = 10;
    std::shared_ptr<items> itemlist = std::make_shared<items>(cap,emptylist);
    std::shared_ptr<enemies> testingenemy = std::make_shared<enemies>(30, 30, 15);

    while (!glfwWindowShouldClose(window) && player -> alive)
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        if (itemlist->sizegetter() < cap) {
            itemlist->generateoneitem();
        }
        bool showshootline = player->shooting();//shoot if space key is pressed
        player->displayshootline();
        //move snake
        double currentTime = glfwGetTime();
        if (currentTime - lastMoveTime >= MOVE_INTERVAL) {
            player->move(itemlist); // Update the snake's position
            testingenemy->move(player->gethead());
            testingenemy->rotate();//move and rotate the enemy
            lastMoveTime = currentTime; // Reset the timer
        }        
        // Draw the items and snake
        itemlist->drawitems();
        player->drawsnake();
        testingenemy->drawenemy();
        currentTime = glfwGetTime();                         
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}