#include <99_grapher/grapher_program.h>

#include <debug_drawer_2d.h>

namespace neko{

void GrapherProgram::LoadSimulation(
        EntityManager& entityManager,
        Transform2dManager& transform2DManager,
        Body2dManager& body2DManager,
        BoxCollider2dManager& boxCollider2DManager,
        CircleCollider2dManager& circleCollider2DManager,
        PolygonCollider2dManager& polygonCollider2DManager)
{

}

void GrapherProgram::Init()
{

}

void GrapherProgram::Update(seconds dt)
{
    physics::DebugDrawer2dLocator::get().DrawLine({-100, 0}, {100, 0});
    physics::DebugDrawer2dLocator::get().DrawLine({0, -100}, {0, 100});

    physics::Vec2 lastPos = {-100, 0};

    for(float x = -100; x < 100; x += 0.1f){
        float y = FunctionX(x);
        physics::DebugDrawer2dLocator::get().DrawLine(lastPos, {x, y});

        lastPos = {x, y};


    }
}

void GrapherProgram::Destroy()
{

}

float GrapherProgram::FunctionX(float x)
{
    return sin(x) * 2;
}
} //namespace neko

