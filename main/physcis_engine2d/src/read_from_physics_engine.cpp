#include "read_from_physics_engine.h"

#include "rigidbody.h"

namespace neko{

ReadFromPhysicsEngine::ReadFromPhysicsEngine(physics::World& world, EntityManager& entityManager,
                                             Transform2dManager& transform2DManager, Body2dManager& body2DManager) :
        world_(world),
        entityManager_(entityManager),
        transform2DManager_(transform2DManager),
        body2DManager_(body2DManager){

}

void ReadFromPhysicsEngine::Init() {

}

void ReadFromPhysicsEngine::Update(seconds dt) {
    const std::vector<physics::RigidBody>& bodies = world_.RetrieveBodies();

    const EntityMask entityMask = EntityMask((uint32_t)ComponentType::BODY2D | (uint32_t)ComponentType::TRANSFORM2D);

    std::vector<Entity> entities = entityManager_.FilterEntities(entityMask);

    for(int i = 0; i < entities.size(); i++){
        const auto rigidBody = bodies[i];

        auto body = body2DManager_.GetComponent(entities[i]);
        body.bodyType = rigidBody.GetBodyType();
        body.linearVelocity = Vec2f(rigidBody.GetLinearVelocity().x, rigidBody.GetLinearVelocity().y);
        body.angularVelocity = rigidBody.GetAngularVelocity();
        body.force = Vec2f(rigidBody.GetForce().x, rigidBody.GetForce().y);
        body.mass = rigidBody.GetMass();
        body.invMass = rigidBody.GetInvMass();
        body.torque = rigidBody.GetTorque();
        body.gravityScale = rigidBody.GetGravityScale();

        //Update body component
        body2DManager_.SetComponent(entities[i], body);

        //Update position
        const auto pos = rigidBody.GetPosition();
        transform2DManager_.SetPosition(entities[i], Vec2f(pos.x, pos.y));

        //Update angle
        const auto angle = rigidBody.GetAngle();
        transform2DManager_.SetRotation(entities[i], angle);
    }
}

void ReadFromPhysicsEngine::Destroy() {

}
} //namespace neko