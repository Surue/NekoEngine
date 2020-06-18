#include <01_rigidbody_gravity/rigidbody_gravity_program.h>

namespace neko
{

void RigidBodyGravityProgram::LoadSimulation(
        EntityManager& entityManager,
        Transform2dManager& transform2DManager,
        Body2dManager& body2DManager,
        BoxCollider2dManager& boxCollider2DManager,
        CircleCollider2dManager& circleCollider2DManager,
        PolygonCollider2dManager& polygonCollider2DManager)
{
    //Create an entity in the center of the scree
    auto entity = entityManager.CreateEntity();

    transform2DManager.AddComponent(entity);
    body2DManager.AddComponent(entity);

    //Set position at the center of the screen
    transform2DManager.SetPosition(entity, Vec2f(0, 0));

    //Set the body type to dynamic
    auto body = body2DManager.GetComponent(entity);
    body.bodyType = BodyType::DYNAMIC;
    body.gravityScale = 1;
    body2DManager.SetComponent(entity, body);
}

void RigidBodyGravityProgram::Init()
{

}

void RigidBodyGravityProgram::Update(seconds dt)
{

}

void RigidBodyGravityProgram::Destroy()
{

}
} //namespace neko