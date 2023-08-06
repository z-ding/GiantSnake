#include "inputhandler.h"
# include "./global.h"
int snakedir = 0;
bool shoot = false;//the snake will shoot itself and erase a node if shoot in correct direction
// Function to handle keyboard input
void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        switch (key) {
        case GLFW_KEY_UP:
            snakedir = 0;//up
            break;
        case GLFW_KEY_DOWN:
            snakedir = 1;//down
            break;
        case GLFW_KEY_LEFT:
            snakedir = 2;//left
            break;
        case GLFW_KEY_RIGHT:
            snakedir = 3;//right
            break;
        case GLFW_KEY_SPACE:
            shoot = true;
            break;
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, GLFW_TRUE);
            break;
        }
    }
}
