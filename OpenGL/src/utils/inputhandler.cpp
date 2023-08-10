#include "inputhandler.h"
# include "./global.h"
int snakedir = 0;
bool shoot = false;//the snake will shoot itself and erase a node if shoot in correct direction
// Function to handle keyboard input
void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        switch (key) {
        case GLFW_KEY_UP:
            if (snakedir != 1) snakedir = 0;//up          
            break;
        case GLFW_KEY_DOWN:
            if (snakedir != 0) snakedir = 1;//down
            break;
        case GLFW_KEY_LEFT:
            if (snakedir != 3) snakedir = 2;//left
            break;
        case GLFW_KEY_RIGHT:
            if (snakedir != 2) snakedir = 3;//right
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
