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

#include <engine/window.h>
#include <utilities/service_locator.h>
#include <vector.h>
#include <gl/line.h>

namespace neko::physics
{
class DebugDrawer2dInterface
{
public:
    /**
     * \brief Draw a line between p1 and p2
     * @param p1
     * @param p2
     */
    virtual void DrawLine(Vec2 p1, Vec2 p2, const Color3& color = Color3(1, 1, 1)) = 0;

    /**
     * \brief Draw a vector from an origin with a certain direction and length
     * \param origin
     * \param direction
     * \param length
     */
    virtual void DrawVector(Vec2 origin, Vec2 direction, float length, const Color3& color = Color3(1, 1, 1)) = 0;

    /**
     * \brief Draw an AABB
     * \param bottomLeft
     * \param topRight
     */
    virtual void DrawAABB(Vec2 bottomLeft, Vec2 topRight, const Color3& color = Color3(0, 1 ,0)) = 0;

    /**
     * \brief Draw a circle a the center with the given radius
     * \param center
     * \param radius
     */
    virtual void DrawCircle(Vec2 center, float radius, const Color3& color = Color3(1, 1, 1)) = 0;

    /**
     * \brief Draw a box with a given rotation
     * \param center
     * \param extent
     * \param angle
     * \param color
     */
    virtual void DrawBox(Vec2 center, Vec2 extent, float angle, const Color3& color = Color3(1, 1, 1)) = 0;

    /**
     * \brief Draw a polygon
     * \param center
     * \param vertices
     * \param color
     */
    virtual void DrawPolygon(Vec2 center, std::vector<Vec2> vertices, const Color3& color = Color3(1, 1, 1)) = 0;
};

class DebugDrawer2d : public DebugDrawer2dInterface, public SystemInterface
{
public:
    void Init() override;

    void Update(seconds dt) override;

    void Destroy() override;

    void DrawLine(Vec2 p1, Vec2 p2, const Color3& color) override;

    void DrawVector(Vec2 origin, Vec2 direction, float length, const Color3& color) override;

    void DrawAABB(Vec2 bottomLeft, Vec2 topRight, const Color3& color) override;

    void DrawCircle(Vec2 center, float radius, const Color3& color) override;

    void DrawBox(Vec2 center, Vec2 extent, float angle, const Color3& color) override;

    void DrawPolygon(Vec2 center, std::vector<Vec2> vertices, const Color3& color) override;

    void SetWindow(Window* window) { window_ = window; }

private:
    const int pixelPerUnit_ = 20;
    const int nbSegmentCircle_ = 20;

    Vec3f WorldToScreen(physics::Vec2 pos);

    gl::LineRenderer lineRenderer_;

    Window* window_;
};

class NullDebugDrawer2d : public DebugDrawer2dInterface
{
public:
    void DrawLine(Vec2 p1, Vec2 p2, const Color3& color) override {}

    void DrawVector(Vec2 origin, Vec2 direction, float length, const Color3& color) override {}

    void DrawAABB(Vec2 bottomLeft, Vec2 topRight, const Color3& color) override {}

    void DrawCircle(Vec2 center, float radius, const Color3& color) override {}

    void DrawBox(Vec2 center, Vec2 extent, float angle, const Color3& color) override {}

    void DrawPolygon(Vec2 center, std::vector<Vec2> vertices, const Color3& color) override {}
};

using DebugDrawer2dLocator = Locator<DebugDrawer2dInterface, NullDebugDrawer2d>;
} //namespace neko::physics
