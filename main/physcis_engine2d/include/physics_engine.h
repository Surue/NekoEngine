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

#include <sdl_engine/sdl_engine.h>
#include "world.h"
#include <stats.h>
#include <entity_viewer.h>
#include <body_2d_viewer.h>
#include <transforms_viewer.h>
#include <box_collider_2d_viewer.h>
#include <circle_collider_2d_viewer.h>
#include <polygon_collider_2d_viewer.h>

namespace neko {
class PhysicsEngine final : public sdl::SdlEngine {
public:
	explicit PhysicsEngine(Configuration* config = nullptr);

	~PhysicsEngine() = default;

private:
	physics::World world_;

	// Entity
    EntityManager entityManager;
    EntityHierarchy entityHierarchy;

    // Components manager
    Transform2dManager transform2DManager;
    physics::Body2dManager body2DManager;
    physics::BoxCollider2dManager boxCollider2DManager;
    physics::CircleCollider2dManager circleCollider2DManager;
    physics::PolygonCollider2dManager polygonCollider2DManager;

    //List of every tool
    tool::StatsTool statsTool;
    tool::EntityViewer entityViewer ;

    // Components viewers
    tool::Transform2dViewer transform2DViewer;
    tool::Body2dViewer body2DViewer;
    tool::BoxCollider2dViewer boxCollider2dViewer;
    tool::CircleCollider2dViewer circleCollider2dViewer;
    tool::PolygonCollider2dViewer polygonCollider2dViewer;
};
} // namespace neko