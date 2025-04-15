/**
 * @file VertexBuffer.h
 * @author Marco Silva (msilva2203)
 */

#pragma once

#include "Utility.h"

class VertexBuffer
{
public:

    VertexBuffer();
    virtual ~VertexBuffer();

    void Bind();
    void Unbind();
    void BufferData(f32* Data, u32 Size, u32 Stride);
    void AddAttribute(u32 Size);

private:

    u32 Id;
    u32 AttributeCount;
    u32 AttributeOffset;
    u32 BufferStride;

};