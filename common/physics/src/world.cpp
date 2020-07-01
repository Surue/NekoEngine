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
        //TODO ICUBUEWUIVFBZUEHIUCVUZWEUIFO BCIWGREBFOUIV CBWRISUFZIC
        auto pos = body.GetPosition();

        //x(t) = t * vo + x0
        pos = pos + body.GetLinearVelocity();

        body.SetPosition(pos);

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
                    break;
            }
        }
    }
}

void World::Destroy()
{

}
} // namespace neko::physics