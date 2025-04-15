/**
 * @file Input.h
 * @author Marco Silva (msilva2203)
 */

#pragma once

#include "Utility.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Input {

    enum class Key {
        W              = GLFW_KEY_W,
        A              = GLFW_KEY_A,
        S              = GLFW_KEY_S,
        D              = GLFW_KEY_D,
        LSHIFT         = GLFW_KEY_LEFT_SHIFT,
        LCTRL          = GLFW_KEY_LEFT_CONTROL,
        SPACE          = GLFW_KEY_SPACE,
        ESC            = GLFW_KEY_ESCAPE
    };

    enum class Mode {
        Game           = GLFW_CURSOR_DISABLED,
        Cursor         = GLFW_CURSOR_NORMAL
    };

    void Init();
    void SetMode(Mode NewValue);

    bool IsKeyDown(Key InKey);
    f64 GetMouseX();
    f64 GetMouseY();

};

class InputListener {
public:

    InputListener() = default;
    virtual ~InputListener() = default;

    virtual void OnKeyPressed(Input::Key InKey);
    virtual void OnKeyReleased(Input::Key InKey);
    virtual void OnMouseMoved(f64 OffsetX, f64 OffsetY);

};