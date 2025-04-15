/**
 * @file Application.h 
 * @author Marco Silva (msilva2203)
 */

#pragma once

#include "Rendering/Window.h"
#include "Framework/Instance.h"

class Application
{
public:

    Application();
    virtual ~Application();

    void Run();
    bool IsRunning() const;

private:

    Window* AppWindow;
    Instance* GameInstance;

};
