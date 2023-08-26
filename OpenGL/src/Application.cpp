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

// Adjust the speed by changing this value
std::unique_ptr<map> fibonaccimap;
std::unique_ptr<snake> player;
std::unique_ptr<items> itemlist;
std::vector<std::shared_ptr<enemies>> Enemies;
std::shared_ptr<allpurposenode> snakeloc;
int cap;
double MOVE_INTERVAL = 0.5;
double lastMoveTime = glfwGetTime();
double currentTime;
bool gameover = false;
bool allowextension = false;//allow the user to go to next stage via the top of the screen when this stage is cleared
int amountEnemy = 2;
int main(void)
{
    GLFWwindow* window;
    
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
        updategame();
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);   
        render();
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}