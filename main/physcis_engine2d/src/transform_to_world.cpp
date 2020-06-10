#include "transform_to_world.h"

#include <engine/body_2d.h>
#include "rigidbody.h"

namespace neko
{

TransformToWorld::TransformToWorld(
        physics::World& world,
        EntityManager& entityManager,
        Transform2dManager& transform2DManager,
        Body2dManager& body2DManager) :
        world_(world),
        entityManager_(entityManager),
        transform2DManager_(transform2DManager),
        body2DManager_(body2DManager)
{}

void TransformToWorld::Init()
{

}

void TransformToWorld::Update(seconds dt)
{
    const EntityMask entityMask = EntityMask((uint32_t) ComponentType::BODY2D | (uint32_t) ComponentType::TRANSFORM2D);

    const std::vector<Entity> entities = entityManager_.FilterEntities(entityMask);

    std::vector<physics::RigidBody> bodies(entities.size());

    for (int i = 0; i < entities.size(); i++)
    {
        const auto body = body2DManager_.GetComponent(entities[i]);
        physics::RigidBody rigidBody;

        //Update position
        const auto pos = transform2DManager_.GetPosition(entities[i]);
        rigidBody.SetPosition(physics::Vec2(pos.x, pos.y));

        //Update angle
        const auto angle = transform2DManager_.GetRotation(entities[i]);
        rigidBody.SetAngle(angle);

        rigidBody.SetBodyType(body.bodyType);
        rigidBody.SetLinearVelocity(physics::Vec2(body.linearVelocity.x, body.linearVelocity.y));
        rigidBody.SetAngularVelocity(body.angularVelocity);
        rigidBody.SetForce(physics::Vec2(body.force.x, body.force.y));
        rigidBody.SetMass(body.mass);
        rigidBody.SetInvMass(body.invMass);
        rigidBody.SetTorque(body.torque);
        rigidBody.SetGravityScale(body.gravityScale);

        bodies[i] = rigidBody;
    }

    world_.SetBodies(bodies);
}

void TransformToWorld::Destroy()
{

}
} //namespace neko
