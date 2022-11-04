#include "Window.h"

#include <iostream>


Window::Window(int windowWidth, int windowHeight):
    width(windowWidth), height(windowHeight)
{
    glfwWindow = glfwCreateWindow(windowWidth, windowHeight, "SCHEngine", nullptr, nullptr);
    if (glfwWindow == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
}

Window::~Window()
{
    if(glfwWindow)
    {
        glfwSetWindowShouldClose(glfwWindow, true);
    }
}

void Window::Init()
{
    if(glfwWindow)
    {
        glfwMakeContextCurrent(glfwWindow);
    }
    else
    {
        std::cout << "GLFW window is null" << std::endl;
    }
}

void Window::Close()
{
    if(glfwWindow)
    {
        glfwSetWindowShouldClose(glfwWindow, true);
    }
}

void Window::SetWindowSize(int windowWidth, int windowHeight)
{
    glfwSetWindowSize(glfwWindow, windowWidth, windowHeight);
    width = windowWidth;
    height = windowHeight;
}
