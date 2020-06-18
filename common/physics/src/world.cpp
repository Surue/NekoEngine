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

        pos = pos + body.GetLinearVelocity();

        body.SetPosition(pos);
    }
}

void World::Destroy()
{

}
} // namespace neko::physics