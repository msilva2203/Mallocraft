/**
 * @file Window.cpp 
 * @author Marco Silva (msilva2203)
 */

#include "Window.h"

static i32 InitRefs = 0;

Window::Window() {
    WindowProperties DefaultProps;
    DefaultProps.Name = "Hello, World!";
    DefaultProps.Width = 640;
    DefaultProps.Height = 480;
    Init(DefaultProps);
}

Window::Window(const WindowProperties& WindowProps) {
    Init(WindowProps);
}

Window::~Window() {
    InitRefs--;
    if (InitRefs <= 0) {
        glfwTerminate();
    }
}

void Window::Init(const WindowProperties& WindowProps) {
    if (InitRefs <= 0) {
        InitRefs = 1;
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    }

    RawWindow = glfwCreateWindow(
        WindowProps.Width, 
        WindowProps.Height, 
        WindowProps.Name.c_str(), 
        nullptr, 
        nullptr
    );

    glfwMakeContextCurrent(RawWindow);
}

void Window::Close() {
    glfwSetWindowShouldClose(RawWindow, true);
}

bool Window::ShouldClose() const {
    return glfwWindowShouldClose(RawWindow);
}

void Window::Clear() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::SwapBuffers() {
    glfwSwapBuffers(RawWindow);
}

void Window::PollEvents() {
    glfwPollEvents();
}

GLFWwindow* Window::GetRawWindow() const {
    return RawWindow;
}