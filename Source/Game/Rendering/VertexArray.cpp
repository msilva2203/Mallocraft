/**
 * @file VertexArray.cpp 
 * @author Marco Silva (msilva2203)
 */

#include "VertexArray.h"

#include "glad/glad.h"

VertexArray::VertexArray() {
    glGenVertexArrays(1, &Id);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &Id);
}

void VertexArray::Bind() {
    glBindVertexArray(Id);
}

void VertexArray::Unbind() {
    glBindVertexArray(0);
}