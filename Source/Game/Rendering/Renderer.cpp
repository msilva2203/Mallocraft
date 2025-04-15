/**
 * @file Renderer.cpp 
 * @author Marco Silva (msilva2203)
 */

#include "Renderer.h"

#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

void Renderer::Init() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(EXIT_FAILURE);
    }
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

void Renderer::DrawElements(VertexArray* VAO, ElementsBuffer* EBO, Shader* ElementShader) {
    if (!VAO) return;
    if (!EBO) return;
    if (ElementShader) {
        ElementShader->Bind();
    }
    VAO->Bind();
    glDrawElements(GL_TRIANGLES, EBO->GetCount(), GL_UNSIGNED_INT, 0);
}