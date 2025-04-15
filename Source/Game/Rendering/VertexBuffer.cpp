/**
 * @file VertexBuffer.cpp 
 * @author Marco Silva (msilva2203)
 */

#include "VertexBuffer.h"

#include "glad/glad.h"

VertexBuffer::VertexBuffer() {
    glGenBuffers(1, &Id);
    AttributeCount = 0;
    AttributeOffset = 0;
    BufferStride = 0;
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &Id);
}

void VertexBuffer::Bind() {
    glBindBuffer(GL_ARRAY_BUFFER, Id);
}

void VertexBuffer::Unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::BufferData(f32* Data, u32 Size, u32 Stride) {
    Bind();
    glBufferData(GL_ARRAY_BUFFER, Size, Data, GL_DYNAMIC_DRAW);
    Unbind();

    BufferStride = Stride;
}

void VertexBuffer::AddAttribute(u32 Size) {
    Bind();
    glVertexAttribPointer(AttributeCount, Size, GL_FLOAT, GL_FALSE, BufferStride, (void*)(AttributeOffset));
    glEnableVertexAttribArray(AttributeCount);
    Unbind();

    AttributeCount++;
    AttributeOffset += Size * sizeof(f32);
}