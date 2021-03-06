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

#include <string>
#include <cmath>

namespace neko::physics
{

// Prototypes
struct Vec3;

/**
 * \brief Class used to represent a 2D vector.
 */
struct Vec2
{
public:

    union
    {
        struct
        {
            float x;
            float y;
        };
        float coord[2]{};
    };

    Vec2();

    Vec2(float x, float y);

    Vec2 operator+(const Vec2 rhs) const
    {
        return {x + rhs.x, y + rhs.y};
    }

    void operator+=(const Vec2 rhs)
    {
        x += rhs.x;
        y += rhs.y;
    }

    Vec2 operator-(const Vec2 rhs) const
    {
        //TODO Complete this function.
        return {};
    }

    void operator-=(const Vec2 rhs)
    {
        //TODO Complete this function.
    }

    Vec2 operator*(const float scalar) const
    {
        //TODO Complete this function.
        return {x * scalar, y * scalar};
    }

    void operator*=(const float scalar)
    {
        //TODO Complete this function.
    }

    Vec2 operator/(const float scalar) const
    {
        //TODO Complete this function.
        return {};
    }

    void operator/=(const float scalar)
    {
        //TODO Complete this function.
    }

    const float& operator[](size_t component) const
    {
        return coord[component];
    }

    float& operator[](size_t component)
    {
        return coord[component];
    }

    /**
     * \brief Calculate the magnitude of the vector.
     * \return the magnitude
     */
    float Magnitude() const
    {
        return sqrtf(x*x + y*y);
    }

    /**
     * \brief Calculate the square magnitude of the vector.
     * \details This operation is faster than the function Magnitude().
     * \return the square magnitude
     */
    float SqrMagnitude() const
    {
        return x*x + y*y;
    }

    /**
     * \brief Return a normalized vector without changing the original one.
     * \return a normalized vector.
     */
    Vec2 Normalized() const
    {
        //TODO Complete this function.
        return {};
    }

    /**
     * \brief Normalize the original vector
     */
    void Normalize()
    {
        //TODO Complete this function.
    }

    float Dot(const Vec2 other) const
    {
        //TODO Complete this function.
        return 0;
    }

    static float Dot(const Vec2 v1, const Vec2 v2)
    {
        //TODO Complete this function.
        return 0;
    }

    float AngleBetween(const Vec2 other) const
    {
        //TODO Complete this function.
        return 0;
    }


    static float AngleBetween(const Vec2 v1, const Vec2 v2)
    {
        //TODO Complete this function.
        return 0;
    }

    Vec3 Cross(const Vec2 other) const;

    static Vec3 Cross(const Vec2 v1, const Vec2 v2);

    std::string ToString()
    {
        //TODO Complete this function.
        return "()";
    }
};

struct Vec3
{
    float x, y, z;

    Vec3() : x(0), y(0), z(0) {}
};
} // namespace neko::physics
