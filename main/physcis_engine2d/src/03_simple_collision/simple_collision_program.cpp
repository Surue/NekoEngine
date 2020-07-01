#include <03_simple_collision/simple_collision_program.h>

namespace neko{

void neko::SimpleCollisionProgram::LoadSimulation(EntityManager& entityManager, Transform2dManager& transform2DManager,
                                                  Body2dManager& body2DManager,
                                                  BoxCollider2dManager& boxCollider2DManager,
                                                  CircleCollider2dManager& circleCollider2DManager,
                                                  PolygonCollider2dManager& polygonCollider2DManager)
{
    //Create falling sphere
    auto circleEntity = entityManager.CreateEntity();

    transform2DManager.AddComponent(circleEntity);
    body2DManager.AddComponent(circleEntity);
    circleCollider2DManager.AddComponent(circleEntity);

    transform2DManager.SetPosition(circleEntity, Vec2f(0, 50));

    auto circleBody = body2DManager.GetComponent(circleEntity);
    circleBody.bodyType = BodyType::DYNAMIC;
    circleBody.gravityScale = 1;
    body2DManager.SetComponent(circleEntity, circleBody);

    auto circleCollider = circleCollider2DManager.GetComponent(circleEntity);
    circleCollider.radius = 1;
    circleCollider.restitution = 0;
    circleCollider.friction = 0;
    circleCollider.isTrigger = false;
    circleCollider2DManager.SetComponent(circleEntity, circleCollider);

    //Static box
    auto boxEntity = entityManager.CreateEntity();

    transform2DManager.AddComponent(boxEntity);
    body2DManager.AddComponent(boxEntity);
    boxCollider2DManager.AddComponent(boxEntity);

    transform2DManager.SetPosition(boxEntity, Vec2f(0, -20));

    auto boxBody = body2DManager.GetComponent(boxEntity);
    boxBody.bodyType = BodyType::STATIC;
    boxBody.gravityScale = 0;
    body2DManager.SetComponent(boxEntity, boxBody);

    auto boxCollider = boxCollider2DManager.GetComponent(boxEntity);
    boxCollider.extent = Vec2f(100, 10);
    boxCollider.restitution = 0;
    boxCollider.friction = 0;
    boxCollider.isTrigger = false;
    boxCollider2DManager.SetComponent(boxEntity, boxCollider);

}
} //namespace neko
