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
    DebugDrawer2dLocator::get().DrawAABB({0, 0}, {1, 1});
    DebugDrawer2dLocator::get().DrawCircle({0, 0}, 5);

    BoxCollider2d collider2D;

    if(collider2D.GetShapeType() == ShapeType::BOX){
        std::cout << "BOX\n";
    }

    Collider2d* col = &collider2D;
    if(col->GetShapeType() == ShapeType::BOX){
        std::cout << "BOX\n";
    }

    for (RigidBody& body : bodies_)
    {
        std::cout << "nb collider" << body.GetColliders().size() << "\n";

        const auto& colliders = body.GetColliders();

        for(int i = 0; i < colliders.size(); i++){
            switch(colliders[i].GetShapes().shapeType){
                case ShapeType::BOX:
                    std::cout << "Box(" << std::get<BoxShape>(colliders[i].GetShapes().shape).GetExtent().x << " , " << std::get<BoxShape>(colliders[i].GetShapes().shape).GetExtent().y << "\n";
                    break;
            }
        }

        Vec2 bodyPosition = body.GetPosition();

        Vec2 vel = body.GetLinearVelocity();

        vel = vel + Vec2(0, 9.81f * dt.count());

        body.SetLinearVelocity(vel);

        DebugDrawer2dLocator::get().DrawLine(Vec2{0, 0}, bodyPosition);

        bodyPosition = bodyPosition + vel;

        body.SetPosition(bodyPosition);
    }
}

void World::Destroy()
{

}
} // namespace neko::physics