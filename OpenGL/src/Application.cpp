#include <glfw3.h>
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

    /* Loop until the user closes the window */
    snake* player = new snake(0, 0);
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        // Draw the snake
        glColor3f(1.0f, 0.0f, 0.0f);       
        snakenode* current = player->getehad();
        std::tuple<int, int, char, snakenode*, snakenode*> info = current->getter();
        glRectf(std::get<0>(info), std::get<1>(info), std::get<0>(info) + WIDTH / GRIDS, std::get<1>(info) + HEIGHT / GRIDS);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}