#include <01_rigidbody_gravity/rigidbody_gravity_program.h>

namespace neko
{

void RigidBodyGravityProgramProgram::LoadSimulation(EntityManager& entityManager, Transform2dManager& transform2DManager,
                                                    Body2dManager& body2DManager,
                                                    BoxCollider2dManager& boxCollider2DManager,
                                                    CircleCollider2dManager& circleCollider2DManager,
                                                    PolygonCollider2dManager& polygonCollider2DManager)
{
    auto entity = entityManager.CreateEntity();

    transform2DManager.AddComponent(entity);
    body2DManager.AddComponent(entity);
}
} //namespace neko