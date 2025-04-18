/**
 * @file Blocks.h
 * @author Marco Silva (msilva2203)
 */

#pragma once

#include "Utility.h"

enum class Direction {
    Front = 0,
    Back,
    Top,
    Bottom,
    Left,
    Right
};

namespace Blocks {

    enum class Type {
        Air = 0,
        Dirt,
        Stone,
        Water
    };

    i32 GetTextureIndex(Type Block, Direction InDirection);

    class Block {
    public:

        Block();
        virtual ~Block();

    private:

    };

}