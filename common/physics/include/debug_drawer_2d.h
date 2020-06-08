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
class DebugDrawer2dInterface{
public:
    virtual void DrawLine(physics::Vec2 p1, physics::Vec2 p2) = 0;
};

class DebugDrawer2d : public DebugDrawer2dInterface, public SystemInterface{
public:
    void Init() override;
    void Update(seconds dt) override;
    void Destroy() override;

    void DrawLine(physics::Vec2 p1, physics::Vec2 p2) override;

    void SetWindow(Window* window){ window_ = window;}

private:

    const int pixelPerUnit_ = 50;

    Vec3f WorldToScreen(physics::Vec2 pos);

    gl::LineRenderer lineRenderer_;

    Window* window_;
};

class NullDebugDrawer2d : public DebugDrawer2dInterface{
public:
    void DrawLine(physics::Vec2 p1, physics::Vec2 p2) override{}
};

using DebugDrawer2dLocator = Locator<DebugDrawer2dInterface, NullDebugDrawer2d>;
} //namespace neko::physics
