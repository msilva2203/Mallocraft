/**
 * @file ElementsBuffer.cpp 
 * @author Marco Silva (msilva2203)
 */

#include "ElementsBuffer.h"

#include <iostream>

#include "glad/glad.h"

ElementsBuffer::ElementsBuffer() {
    glGenBuffers(1, &Id);
}

ElementsBuffer::~ElementsBuffer() {
    glDeleteBuffers(1, &Id);
}

void ElementsBuffer::Bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Id);
}

void ElementsBuffer::Unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Id);
}

void ElementsBuffer::BufferElements(i32* Elements, u32 Size) {
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Size, Elements, GL_STATIC_DRAW);
    Count = Size / sizeof(i32);
}

u32 ElementsBuffer::GetCount() const {
    return Count;
}