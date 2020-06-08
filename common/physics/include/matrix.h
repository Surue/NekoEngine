/*
 MIT License

 Copyright (c) 2020 SAE Institute Switzerland AG

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */
#pragma once

#include "vector.h"

namespace neko::physics
{
struct Mat22
{
    Mat22() {}

    Mat22(const Vec2 v1, const Vec2 v2) : v1(v1), v2(v2) {}

    Mat22 operator+(const Mat22& rhs) const
    {
        //TODO Complete this function,
        return {};
    };

    Mat22 operator+=(const Mat22& rhs)
    {
        //TODO Complete this function,
        return {};
    }

    Mat22 operator-(const Mat22& rhs) const
    {
        //TODO Complete this function,
        return {};
    }

    Mat22 operator-=(const Mat22& rhs)
    {
        //TODO Complete this function,
        return {};
    }

    Mat22 operator*(const Mat22& rhs) const
    {
        //TODO Complete this function,
        return {};
    }

    Mat22 operator*=(const Mat22& rhs)
    {
        //TODO Complete this function,
        return {};
    }

    Vec2 operator*(const Vec2& rhs) const
    {
        //TODO Complete this function,
        return {};
    }

    Vec2 operator*=(const Vec2& rhs)
    {
        //TODO Complete this function,
        return {};
    }


    static Mat22 Identity()
    {
        //TODO Complete this function,
        return {};
    }

    static Mat22 GetRotationMatrix(float angleInRad)
    {
        //TODO Complete this function,
        return {};
    }

    std::string ToString()
    {
        //TODO Complete this function,
        return "";
    }

    Vec2 v1, v2;
};
} // namespace neko::physics
