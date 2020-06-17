#include <world.h>

#include <matrix.h>
#include <debug_drawer_2d.h>
#include <engine/box_collider_2d.h>

namespace neko::physics
{

void World::Init()
{

}

void World::Update(seconds dt)
{
    static float time = 0;

    time += dt.count();

    Vec2 center = Vec2(3, 3);
    Vec2 extent = Vec2(5, 2);

    DebugDrawer2dLocator::get().DrawBox(center, extent, time);

    Mat22 rotationMatrix = Mat22::GetRotationMatrix(time);

    Vec2 posA, posB, posC, posD;
    posA = center + rotationMatrix * Vec2(-extent.x, -extent.y);
    posB = center + rotationMatrix * Vec2(extent.x, -extent.y);
    posC = center + rotationMatrix * Vec2(extent.x, extent.y);
    posD = center + rotationMatrix * Vec2(-extent.x, extent.y);

    //ABBB
    float minX = posA.x, maxX = posA.x, minY = posA.y, maxY = posA.y;

    //Test pos B
    if(posB.x < minX) minX = posB.x;
    if(posB.x > maxX) maxX = posB.x;
    if(posB.y < minY) minY = posB.y;
    if(posB.y > maxY) maxY = posB.y;

    //Test pos C
    if(posC.x < minX) minX = posC.x;
    if(posC.x > maxX) maxX = posC.x;
    if(posC.y < minY) minY = posC.y;
    if(posC.y > maxY) maxY = posC.y;

    //Test pos C
    if(posD.x < minX) minX = posD.x;
    if(posD.x > maxX) maxX = posD.x;
    if(posD.y < minY) minY = posD.y;
    if(posD.y > maxY) maxY = posD.y;

    DebugDrawer2dLocator::get().DrawAABB(Vec2(minX, minY), Vec2(maxX, maxY));
}

void World::Destroy()
{

}
} // namespace neko::physics