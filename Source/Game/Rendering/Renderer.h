/**
 * @file Renderer.h
 * @author Marco Silva (msilva2203)
 */

#pragma once

#include "Utility.h"

#include "VertexBuffer.h"
#include "ElementsBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

class Renderer
{
public:

    static void Init();
    static void DrawElements(VertexArray* VAO, ElementsBuffer* EBO, Shader* ElementShader);

private:

};