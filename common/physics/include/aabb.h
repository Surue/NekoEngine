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

namespace neko::physics {
/**
 * \brief Bounding volume around collider used in broad phase of the physics engine.
 */
struct AABB {

    Vec2 bottomLeft;
    Vec2 topRight;

    AABB(Vec2 bottomLeft, Vec2 topRight) : bottomLeft(bottomLeft), topRight(topRight) {};

    /**
     * \brief Return the center of the aabb
     */
    Vec2 GetCenter() const {
        //TODO Complete this function
        return {};
    }

    /**
     * \brief Compute the extent of the aabb
     */
    Vec2 GetExtent() const {
        //TODO Complete this function
        return {};
    }

    /**
     * \brief Test if 2 aabbs are overlapping.
     * \param other aabb which is test against the current aabb.
     * \return true if both aabb are overlapping.
     */
    bool Overlap(const AABB& other) const{
        //TODO complete this function
        return false;
    }
};
} // namespace neko::physics

