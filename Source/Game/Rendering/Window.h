/**
 * @file Window.h
 * @author Marco Silva (msilva2203)
 */

#pragma once

#include "Utility.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <string>

class Window
{
public:

    struct WindowProperties {
        std::string Name;
        i32 Width, Height;
    };

    Window();
    Window(const WindowProperties& WindowProps);
    virtual ~Window();

    void Init(const WindowProperties& WindowProps);
    void Close();
    bool ShouldClose() const;

    void Clear();
    void SwapBuffers();
    void PollEvents();

    GLFWwindow* GetRawWindow() const;

private:

    GLFWwindow* RawWindow = nullptr;

};