#include "controls.h"

Controls::Controls(GLFWwindow* window, Camera *camera):m_Camera(camera),m_Window(window), speed(4), mouseSpeed(0.5)
{
    glfwGetWindowSize(window, &width, &height);
}

void Controls::setSpeed(float newSpeed)
{
    speed = newSpeed;
}

void Controls::setMouseSpeed(float newMouseSpeed)
{
    mouseSpeed = newMouseSpeed;
}

