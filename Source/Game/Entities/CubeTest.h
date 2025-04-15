/**
 * @file CubeTest.h 
 * @author Marco Silva (msilva2203)
 */

#pragma once

#include "Utility.h"
#include "Framework/Entity.h"

#include "Rendering/Renderer.h"

class CubeTest : public Entity
{
    using Super = Entity;
public:

    CubeTest();
    virtual ~CubeTest();

    virtual void Setup() override;
    virtual void Update(f32 DeltaTime) override;
    virtual void Draw() override;

private:

    VertexArray* VAO;
    VertexBuffer* VBO;
    ElementsBuffer* EBO;
    Shader* CubeShader;
    Texture* CubeTexture;

};