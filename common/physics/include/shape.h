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

#include <vector>

#include <engine/collider_2d.h>
#include "vector.h"
#include "aabb.h"

namespace neko::physics
{
class Shape
{
public:
    virtual AABB ComputeAABB(Vec2 position, float angle) const = 0;
};

class CircleShape : public Shape
{
public:
    AABB ComputeAABB(Vec2 position, float angle) const override
    {
        //TODO Complete this function
        return {};
    }

    float GetRadius() const
    {
        return radius_;
    }

    void SetRadius(float radius)
    {
        radius_ = radius;
    }

private:
    float radius_;
};

class BoxShape : public Shape
{
public:
    AABB ComputeAABB(Vec2 position, float angle) const override
    {
        //TODO Complete this function
        return {};
    }

    Vec2 GetExtent() const
    {
        return extent_;
    }

    void SetExtent(const Vec2 extent)
    {
        extent_ = extent;
    }

private:
    Vec2 extent_;
};

class PolygonShape : public Shape
{
public:
    AABB ComputeAABB(Vec2 position, float angle) const override
    {
        //TODO Complete this function
        return {};
    }

    const std::vector<Vec2>& GetVertices() const
    {
        return vertices_;
    }

    void SetVertices(const std::vector<Vec2>& vertices)
    {
        vertices_ = vertices;
    }

private:
    std::vector<Vec2> vertices_;
};

class ShapeData{
public:
    ShapeType shapeType;

    union {
        CircleShape;
        BoxShape;
        PolygonShape;
    } shape;
};
} //namespace neko::physics
