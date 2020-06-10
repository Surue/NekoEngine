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

#include <rigidbody.h>
#include <quad_tree.h>
#include <contact.h>

#include <engine/system.h>

namespace neko::physics
{
class World : public SystemInterface
{
public:
    void Init() override;

    void Update(seconds dt) override;

    void Destroy() override;

    /**
     * \brief Set bodies for the current frame.
     * \param bodies
     */
    void SetBodies(std::vector<RigidBody>& bodies) { bodies_ = bodies; }

    /**
     * \brief Get the bodies after the physics update.
     * \return updated bodies
     */
    std::vector<RigidBody>& RetrieveBodies() { return bodies_; }

    float GetFixedDeltaTime() const { return fixedDeltaTime_; }

    void SetFixedDeltaTime(float dt) { fixedDeltaTime_ = dt; }

    Vec2 GetGravity() const { return gravity_; }

    void SetGravity(Vec2 gravity) { gravity_ = gravity; }

private:
    float fixedDeltaTime_;
    Vec2 gravity_;

    std::vector<RigidBody> bodies_;

    ContactManager contactManager_;

    QuadTree quadTree_;
};
} // namespace neko::physics
