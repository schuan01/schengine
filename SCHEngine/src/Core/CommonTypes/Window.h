/*
 * Generic Window using GLWindow
 */
#pragma once
#include <GLFW/glfw3.h>

class Window
{
private:
    int width;
    int height;
    GLFWwindow* glfwWindow;
public:
    Window(int windowWidth, int windowHeight);
    ~Window();

    void Init();
    void Close();
    void SetWindowSize(int windowWidth, int windowHeight);
    int GetWidth() const { return width; }
    int GetHeight() const { return height; }
    GLFWwindow* GetGLFWWindow() const { return glfwWindow; }

private:
    GLFWframebuffersizefun OnResize(GLFWwindow* window, int width, int height);
};
