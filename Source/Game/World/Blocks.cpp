/**
 * @file Blocks.cpp
 * @author Marco Silva (msilva2203)
 */

#include "Blocks.h"

namespace Blocks {

    i32 GetTextureIndex(Type Block, Direction InDirection) {
        switch (Block) {
            case Type::Air:
            return 4 * 4 - 1;
            case Type::Dirt: {
                switch (InDirection) {
                    case Direction::Top:
                    return 0;
                    case Direction::Bottom:
                    return 2;
                    default:
                    return 1;
                }
            }
            case Type::Stone:
            return 3;
            case Type::Water:
            return 4;
        }
        return 4 * 4 - 1;
    }
}