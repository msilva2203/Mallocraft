/**
 * @file Utility.h 
 * @author Marco Silva (msilva2203)
 */

#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

using i08 = char;
using i16 = short;
using i32 = int;
using i64 = long long;

using u08 = unsigned char;
using u16 = unsigned short;
using u32 = unsigned int;
using u64 = unsigned long long;

using f32 = float;
using f64 = double;

class Utility
{
public:

    Utility() = delete;

    static f64 GetTime();

};