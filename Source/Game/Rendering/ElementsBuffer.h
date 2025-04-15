/**
 * @file IndexBuffer.h
 * @author Marco Silva (msilva2203)
 */

#pragma once

#include "Utility.h"

class ElementsBuffer
{
public:

    ElementsBuffer();
    ~ElementsBuffer();

    void Bind();
    void Unbind();

    void BufferElements(i32* Elements, u32 Size);
    u32 GetCount() const;

private:

    u32 Id;
    u32 Count;

};