#include <world.h>

#include <debug_drawer_2d.h>

namespace neko::physics
{

void World::Init()
{

}

void World::Update(seconds dt)
{
    std::cout << "World\n";
    for (Body2d& body : bodies_)
    {

        Vec2 bodyPosition = body.GetPosition();

        Vec2 vel = body.GetLinearVelocity();

        vel = vel + Vec2(9.81f * dt.count(), 0);

        body.SetLinearVelocity(vel);

        DebugDrawer2dLocator::get().DrawLine(Vec2{0, 0}, bodyPosition);

//        bodyPosition = bodyPosition + vel;

//        body.SetPosition(bodyPosition);
    }
}

void World::Destroy()
{

}
} // namespace neko::physics