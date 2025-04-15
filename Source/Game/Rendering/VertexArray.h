/**
 * @file VertexArray.h
 * @author Marco Silva (msilva2203)
 */

#pragma once

#include "Utility.h"

class VertexArray
{
public:

    VertexArray();
    virtual ~VertexArray();

    void Bind();
    void Unbind();

private:

    u32 Id;

};