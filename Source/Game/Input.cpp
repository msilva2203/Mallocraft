/**
 * @file Input.cpp
 * @author Marco Silva (msilva2203)
 */

#include "Input.h"
#include "Globals.h"
#include "Rendering/Window.h"
#include "Framework/Instance.h"

namespace Input {

    static f64 LastMouseX = 0;
    static f64 LastMouseY = 0;
    static bool bFirstMouse = true;

    void Init() {
        // Bind key callback
        glfwSetKeyCallback(Globals::AppWindow->GetRawWindow(), [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            Instance* CurrentInstance = Globals::CurrentInstance;
            if (CurrentInstance) {
                Input::Key InKey = static_cast<Input::Key>(key);
                switch (action) {
                    case GLFW_PRESS: {
                        CurrentInstance->OnKeyPressed(InKey);
                        break;
                    }
                    case GLFW_RELEASE: {
                        CurrentInstance->OnKeyReleased(InKey);
                        break;
                    }
                    default: {
                        break;
                    }
                }
            }
        });

        // Bind mouse cursor position callback
        glfwSetCursorPosCallback(Globals::AppWindow->GetRawWindow(), [](GLFWwindow* window, double xpos, double ypos) {
            Instance* CurrentInstance = Globals::CurrentInstance;
            if (CurrentInstance) {
                if (bFirstMouse) {
                    LastMouseX = xpos;
                    LastMouseY = ypos;
                    bFirstMouse = false;
                }
                
                f64 OffsetX = xpos - LastMouseX;
                f64 OffsetY = LastMouseY - ypos;
                LastMouseX = xpos;
                LastMouseY = ypos;

                CurrentInstance->OnMouseMoved(OffsetX, OffsetY);
            }
        });
    }

    void SetMode(Mode NewValue) {
        i32 Value = GLFW_CURSOR_NORMAL;
        switch (NewValue) {
            case Mode::Game: {
                Value = GLFW_CURSOR_DISABLED;
                break;
            }
            case Mode::Cursor: {
                Value = GLFW_CURSOR_DISABLED;
                break;
            }
            default: {
                break;
            }
        }
        glfwSetInputMode(Globals::AppWindow->GetRawWindow(), GLFW_CURSOR, Value);
    }

    bool IsKeyDown(Key InKey) {
        return glfwGetKey(Globals::AppWindow->GetRawWindow(), (i32)InKey) == GLFW_PRESS;
    }

    f64 GetMouseX() {
        return LastMouseX;
    }

    f64 getMouseY() {
        return LastMouseY;
    }

}

void InputListener::OnKeyPressed(Input::Key InKey) {

}

void InputListener::OnKeyReleased(Input::Key InKey) {

}

void InputListener::OnMouseMoved(f64 OffsetX, f64 OffsetY) {

}