/**
 * @file Application.cpp
 * @author Marco Silva (msilva2203)
 */

#include "Application.h"
#include "Rendering/Renderer.h"
#include "Sandbox/SandboxInstance.h"
#include "Globals.h"

#include <iostream>

#include "World/Chunk.h"

Application::Application() {
    
}

Application::~Application() {
    delete AppWindow;
    delete GameInstance;
}

void Application::Run() {
    // Create window
    Window::WindowProperties WindowProps;
    WindowProps.Name = "Mallocraft";
    WindowProps.Width = 720;
    WindowProps.Height = 720;
    AppWindow = new Window(WindowProps);
    Globals::AppWindow = AppWindow;

    // Init function modules
    Renderer::Init();
    Input::Init();

    // Create the game instace
    GameInstance = new SandboxInstance();
    GameInstance->Setup();
    Globals::CurrentInstance = GameInstance;

    f32 LastFrameTime = 0.0f;

    // Application loop
    while (IsRunning()) {
        f32 CurrentFrameTime = glfwGetTime();
        f32 DeltaTime = CurrentFrameTime - LastFrameTime;

        AppWindow->Clear();

        GameInstance->Update(DeltaTime);
        GameInstance->Draw();
        
        AppWindow->SwapBuffers();
        AppWindow->PollEvents();

        std::cout << "FPS: " << (i32)(1.0f / DeltaTime) << std::endl;

        LastFrameTime = CurrentFrameTime;
    }
    AppWindow->Close();
}

bool Application::IsRunning() const {
    return !AppWindow->ShouldClose();
}
