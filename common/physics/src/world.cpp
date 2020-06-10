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
    for (RigidBody& body : bodies_)
    {
        //TODO Complete this loop
    }
}

void World::Destroy()
{

}
} // namespace neko::physics