#include <98_balistic/balistic_program.h>

#include <debug_drawer_2d.h>

namespace neko{

void BalisticProgram::Update(seconds dt)
{
    //Draw tower

    physics::DebugDrawer2dLocator::get().DrawAABB(physics::Vec2(-2, 0), physics::Vec2(2, 5));

    float velocity = 10.0f; // 10[m/s]
    float angle = 0.79f; // 45°
//    float angle = 1.05f; // 60°
//    float angle = 0.52f; // 30°
//    float angle = 0; // 0°
//    float angle = 1.48f; //80°

    float x0 = 0;
    float y0 = 2.5f;
    float acc = -9.81f; //g = 9.81[m/s^2]

    //Draw parabol
    physics::Vec2 lastPos = physics::Vec2(x0, y0);
    for(float x = x0; x < 20; x += 0.1f){
        float t = x / (cos(angle) * velocity);
        float y = 0.5f * acc * t * t + sin(angle) * velocity * t + y0;

        if(y < 0){
            break;
        }

        physics::Vec2 newPos = physics::Vec2(x, y);

        physics::DebugDrawer2dLocator::get().DrawLine(lastPos, newPos);

        lastPos = newPos;
    }
}

void BalisticProgram::LoadSimulation(EntityManager& entityManager, Transform2dManager& transform2DManager,
                                     Body2dManager& body2DManager, BoxCollider2dManager& boxCollider2DManager,
                                     CircleCollider2dManager& circleCollider2DManager,
                                     PolygonCollider2dManager& polygonCollider2DManager)
{

}
} //namespace neko
