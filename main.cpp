#include "battlecraft.h"
#include "Game.h"

void GLFWCALL __glfwKeyCallback(int,int);
void GLFWCALL __glfwCharCallback(int,int);
void GLFWCALL __glfwMouseButtonCallback(int,int);

Game* __game;
int main(int argc, char* argv)
{
    __game = new Game(1440,900);
    if (!__game->init())
    {
        printf("Engine initialization failed.\n");
        __game->quit();
        return 1;
    }

    glfwSetKeyCallback(__glfwKeyCallback);
    glfwSetCharCallback(__glfwCharCallback);
    glfwSetMouseButtonCallback(__glfwMouseButtonCallback);

    __game->run();
    __game->quit();
    delete __game;
    
    return 0;
}

void GLFWCALL __glfwKeyCallback(int key, int action)
{
    if (action == GLFW_PRESS)
        __game->keyDown(key);
    if (action == GLFW_RELEASE)
        __game->keyUp(key);
}

void GLFWCALL __glfwCharCallback(int character, int action)
{

}

void GLFWCALL __glfwMouseButtonCallback(int button, int action)
{
    int x, y;
    glfwGetMousePos(&x, &y);

    if (action == GLFW_PRESS)
        __game->mouseDown(x, y, button);
    if (action == GLFW_RELEASE)
        __game->mouseUp(x, y, button);
}