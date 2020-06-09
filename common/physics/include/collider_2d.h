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

#include "aabb.h"

namespace neko::physics
{

enum class ShapeType : uint8_t {
    BOX = 0,
    CIRCLE,
    POLYGON
};

class Collider2d
{
public:
    /**
     * \brief Create a default trigger
     */
    Collider2d();

    /**
     * \brief
     * \warning The centroid must be manually calculated.
     * \param isTrigger
     * \param restitution
     * \param friction
     * \param offset
     */
    Collider2d(bool isTrigger, float restitution, float friction, Vec2 offset);

    virtual ~Collider2d() = default;

    /**
     * \brief Compute the aabb for the given position and angle
     * \param position
     * \param angle
     * \return the aabb
     */
    virtual AABB ComputeAABB(Vec2 position, float angle) const = 0;

    bool IsTrigger() const { return isTrigger_; }

    void SetIsTrigger(bool isTrigger) { isTrigger_ = isTrigger; }

    float GetRestitution() const { return restitution_; }

    void SetRestitution(float restitution) { restitution_ = restitution; }

    float GetFriction() const { return friction_; }

    void SetFriction(float friction) { friction_ = friction; }

    Vec2 GetOffset() const { return offset_; }

    void SetOffset(const Vec2 offset) { offset_ = offset; }

    Vec2 GetCentroid() const { return centroid_; }

    void SetCentroid(const Vec2 centroid) { centroid_ = centroid; }

    virtual ShapeType GetShapeType() const = 0;

protected:
    bool isTrigger_;
    float restitution_;
    float friction_;

    Vec2 offset_;
    Vec2 centroid_;
};

template<ShapeType shapeType>
class Collider2dTemplate : public Collider2d{
public:
    virtual ShapeType GetShapeType() const {
        return shapeType;
    }
};
} // namespace neko::physics
