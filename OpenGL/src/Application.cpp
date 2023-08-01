#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include "snake.h"
#define WIDTH 800
#define HEIGHT 800
#define GRIDS 100



int main(void)
{
    GLFWwindow* window;

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
    if (glewInit() != GLEW_OK) {
        std::cout << "error glew init" << std::endl;
    }
    /* Loop until the user closes the window */
    snake* player = new snake(0.0f, 0.0f);
    int n = 0;

    while (n < 3) {
        player->emplace_back();
        n++;
    }
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        // Draw the snake
        player->drawsnake();
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}