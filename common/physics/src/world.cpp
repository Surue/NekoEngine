#include <world.h>

#include <debug_drawer_2d.h>
#include <engine/box_collider_2d.h>

namespace neko::physics
{

void World::Init()
{

}

void World::Update(seconds dt)
{
    for(RigidBody& body : bodies_){
        auto pos = body.GetPosition();

        body.SetLinearVelocity(body.GetLinearVelocity() + Vec2(0, dt.count() * gravity_.y * body.GetGravityScale()));

        pos = pos + body.GetLinearVelocity() * dt.count();

        body.SetPosition(pos);
        
        //TODO Check collision

        //TODO Update object velocities with gravity

        //TODO Move objects regarding their velocities

        //Draw all collider
        //TODO Move it somewhere else or at least clean this code
        for(const auto& collider : body.GetColliders()){
            const auto& colliderShape = collider.GetShape();
            switch(colliderShape.shapeType){
                case ShapeType::BOX:
                {
                    const auto& boxShape = std::get<BoxShape>(colliderShape.shape);
                    DebugDrawer2dLocator::get().DrawBox(pos + collider.GetOffset(), boxShape.GetExtent(),
                                                        body.GetAngle());
                }
                    break;
                case ShapeType::CIRCLE:
                {
                    const auto& circleShape = std::get<CircleShape>(colliderShape.shape);
                    DebugDrawer2dLocator::get().DrawCircle(pos + collider.GetOffset(), circleShape.GetRadius());
                }
                    break;
                case ShapeType::POLYGON:
                {
                    const auto& polyShape = std::get<PolygonShape>(colliderShape.shape);
                    DebugDrawer2dLocator::get().DrawPolygon(pos + collider.GetOffset(), polyShape.GetVertices(), body.GetAngle());
                }
                    break;
            }
        }
    }
}

void World::Destroy()
{

}
} // namespace neko::physics