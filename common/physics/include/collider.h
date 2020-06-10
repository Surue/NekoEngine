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
#include "shape.h"

namespace neko::physics
{
class Collider
{
public:
    bool IsTrigger() const
    {
        return isTrigger_;
    }

    void SetIsTrigger(bool isTrigger)
    {
        isTrigger_ = isTrigger;
    }

    float GetRestitution() const
    {
        return restitution_;
    }

    void SetRestitution(float restitution)
    {
        restitution_ = restitution;
    }

    float GetFriction() const
    {
        return friction_;
    }

    void SetFriction(float friction)
    {
        friction_ = friction;
    }

    Vec2 GetOffset() const
    {
        return offset_;
    }

    void SetOffset(const Vec2 offset)
    {
        offset_ = offset;
    }

    Vec2 GetCentroid() const
    {
        return centroid_;
    }

    void SetCentroid(const Vec2 centroid)
    {
        centroid_ = centroid;
    }

    const ShapeData& GetShapes() const
    {
        return shapes_;
    }

    void SetShapes(const ShapeData& shapes)
    {
        shapes_ = shapes;
    }

public:
private:
    bool isTrigger_;
    float restitution_;
    float friction_;

    Vec2 offset_;
    Vec2 centroid_;

    ShapeData shapes_;
};
} //namespace neko::physics
