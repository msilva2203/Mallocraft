/**
 * @file main.cpp
 * @author Marco Silva (msilva2203)
 */

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Application.h"

#include <iostream>

int main(void) {
    Application* App = new Application();
    App->Run();
    delete App;

    return 0;
}