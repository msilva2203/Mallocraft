/**
 * @file CubeTest.cpp 
 * @author Marco Silva (msilva2203)
 */

#include "CubeTest.h"

#include "GLFW/glfw3.h"

CubeTest::CubeTest() {

}

CubeTest::~CubeTest() {
    delete VAO;
    delete VBO;
    delete EBO;
    delete CubeTexture;
}

void CubeTest::Setup() {
    Super::Setup();

    //f32 Vertices[] = {
    //    -0.5f, -0.5f,  0.0f,        1.0f,  0.0f,  0.0f,        0.0f,  0.0f,
    //     0.5f, -0.5f,  0.0f,        0.0f,  1.0f,  0.0f,        1.0f,  0.0f,
    //     0.5f,  0.5f,  0.0f,        0.0f,  0.0f,  1.0f,        1.0f,  1.0f,
    //    -0.5f,  0.5f,  0.0f,        0.5f,  0.0f,  0.5f,        0.0f,  1.0f
    //};

    f32 Vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    //i32 Elements[] = {
    //    0, 1, 2,
    //    2, 3, 0
    //};

    i32 Elements[] = {
        0, 1, 2,
        2, 3, 0
    };

    VAO = new VertexArray();
    VAO->Bind();

    VBO = new VertexBuffer();
    VBO->Bind();
    VBO->BufferData(Vertices, sizeof(Vertices), 5 * sizeof(f32));

    EBO = new ElementsBuffer();
    EBO->Bind();
    EBO->BufferElements(Elements, sizeof(Vertices));

    VBO->AddAttribute(3);
    //VBO->AddAttribute(3);
    VBO->AddAttribute(2);

    VBO->Unbind();
    VAO->Unbind();
    EBO->Unbind();

    CubeShader = Shader::Manager::GetShader("Content/Shaders/Cube.glsl");

    CubeTexture = new Texture();
    CubeTexture->Load("Content/Textures/Dirt.jpg");
}

void CubeTest::Update(f32 DeltaTime) {
    Super::Update(DeltaTime);
    
}

void CubeTest::Draw() {
    Super::Draw();

    glm::mat4 Transform = glm::mat4(1.0f);
    Transform = glm::translate(Transform, GetPosition());
    Transform = glm::rotate(Transform, (f32)Utility::GetTime(), glm::vec3(1.0f, 0.0f, 0.0f));
    Transform = glm::rotate(Transform, (f32)Utility::GetTime() * 0.25f, glm::vec3(0.0f, 0.0f, 1.0f));

    CubeShader->Bind();
    CubeTexture->Bind();
    VAO->Bind();
    CubeShader->SetFloatMatrix4("uModel", Transform);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    VAO->Unbind();
    CubeTexture->Unbind();
    CubeShader->Unbind();

    //Renderer::DrawElements(VAO, EBO, CubeShader);
}