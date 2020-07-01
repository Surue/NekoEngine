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

#include <physics_simulation_program.h>

namespace neko
{
class FrictionProgram : public PhysicsSimulationProgramInterface
{
public:
    FrictionProgram(Transform2dManager& transform2DManager, BoxCollider2dManager& boxCollider2DManager);

    virtual void LoadSimulation(
            EntityManager& entityManager,
            Transform2dManager& transform2DManager,
            Body2dManager& body2DManager,
            BoxCollider2dManager& boxCollider2DManager,
            CircleCollider2dManager& circleCollider2DManager,
            PolygonCollider2dManager& polygonCollider2DManager) override;

    void DrawImGui() override;;

    void Init() override {}

    void Update(seconds dt) override;

    void Destroy() override{}

private:
    const int nbBody_ = 4;
    const float horizontalSpaceBetweenBall_ = 20;
    const float platformHeight_ = 2;
    const float platformWidth_ = 10;

    float platformFriction_ = 0;
    float angleInRadOfPlatforms_ = 0.5f;
    bool mustReset_ = false;

    std::vector<Entity> platformsEntities_;
    std::vector<Entity> quadEntities_;

    Transform2dManager& transform2DManager_;
    BoxCollider2dManager& boxCollider2DManager_;
};
} // namespace neko