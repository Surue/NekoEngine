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
#include <engine/component.h>

namespace neko::physics
{

enum class BodyType : uint8_t
{
    STATIC = 0,
    DYNAMIC,
    KINEMATIC
};

class Body2d
{
public:
    Vec2 GetPosition() const { return position_; }

    void SetPosition(const Vec2 position) { position_ = position; }

    float GetAngle() const { return angle_; }

    void SetAngle(float angle) { angle_ = angle; }

    float GetGravityScale() const { return gravityScale_; }

    void SetGravityScale(float gravityScale) { gravityScale_ = gravityScale; }

    const Vec2 GetLinearVelocity() const { return linearVelocity; }

    void SetLinearVelocity(const Vec2& linearVelocity) { Body2d::linearVelocity = linearVelocity; }

    float GetAngularVelocity() const { return angularVelocity; }

    void SetAngularVelocity(float angularVelocity) { Body2d::angularVelocity = angularVelocity; }

    const Vec2 GetForce() const { return force_; }

    void SetForce(const Vec2& force) { force_ = force; }

    float GetTorque() const { return torque_; }

    void SetTorque(float torque) { torque_ = torque; }

    float GetMass() const { return mass_; }

    void SetMass(float mass) { mass_ = mass; }

    float GetInvMass() const { return invMass_; }

    void SetInvMass(float invMass) { invMass_ = invMass; }

    BodyType GetBodyType() const { return bodyType_; }

    void SetBodyType(BodyType bodyType) { bodyType_ = bodyType; }

private:
    Vec2 position_;
    float angle_;

    float gravityScale_;

    Vec2 linearVelocity;
    float angularVelocity;

    Vec2 force_;

    float torque_;

    float mass_;
    float invMass_;

    BodyType bodyType_;
};

class Body2dManager : public ComponentManager<Body2d, ComponentType::BODY2D>
{
public:

private:
    using ComponentManager::ComponentManager;
};
} // namespace neko::physics

