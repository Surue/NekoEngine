#include "write_to_physics_engine.h"

#include <engine/body_2d.h>
#include "rigidbody.h"

namespace neko
{

WriteToPhysicsEngine::WriteToPhysicsEngine(
        physics::World& world,
        EntityManager& entityManager,
        Transform2dManager& transform2DManager,
        Body2dManager& body2DManager,
        BoxCollider2dManager& boxCollider2DManager,
        CircleCollider2dManager& circleCollider2DManager,
        PolygonCollider2dManager& polygonCollider2DManager) :
        world_(world),
        entityManager_(entityManager),
        transform2DManager_(transform2DManager),
        body2DManager_(body2DManager),
        boxCollider2DManager_(boxCollider2DManager),
        circleCollider2DManager_(circleCollider2DManager),
        polygonCollider2DManager_(polygonCollider2DManager)
{}

void WriteToPhysicsEngine::Init()
{

}

void WriteToPhysicsEngine::Update(seconds dt)
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

        //Box Colliders
        std::vector<physics::Collider> colliders;
        if(entityManager_.HasComponent(entities[i], EntityMask(ComponentType::BOX_COLLIDER2D))){
            physics::Collider boxCollider;

            const auto otherCollider = boxCollider2DManager_.GetComponent(entities[i]);

            boxCollider.SetCentroid(physics::Vec2(otherCollider.centroid.x, otherCollider.centroid.y));
            boxCollider.SetOffset(physics::Vec2(otherCollider.offset.x, otherCollider.offset.y));
            boxCollider.SetIsTrigger(otherCollider.isTrigger);
            boxCollider.SetFriction(otherCollider.friction);
            boxCollider.SetRestitution(otherCollider.restitution);

            physics::ShapeData shapeData{physics::Vec2(
                    otherCollider.extent.x,
                    otherCollider.extent.y)};
            boxCollider.SetShapes(shapeData);

            colliders.push_back(boxCollider);
        }

        if(entityManager_.HasComponent(entities[i], EntityMask(ComponentType::CIRCLE_COLLIDER2D))){
            physics::Collider circleCollider;

            const auto otherCollider = circleCollider2DManager_.GetComponent(entities[i]);

            circleCollider.SetCentroid(physics::Vec2(otherCollider.centroid.x, otherCollider.centroid.y));
            circleCollider.SetOffset(physics::Vec2(otherCollider.offset.x, otherCollider.offset.y));
            circleCollider.SetIsTrigger(otherCollider.isTrigger);
            circleCollider.SetFriction(otherCollider.friction);
            circleCollider.SetRestitution(otherCollider.restitution);

            physics::ShapeData shapeData{otherCollider.radius};
            circleCollider.SetShapes(shapeData);

            colliders.push_back(circleCollider);
        }

        if(entityManager_.HasComponent(entities[i], EntityMask(ComponentType::POLYGON_COLLIDER2D))){
            physics::Collider polygonCollider;

            const auto otherCollider = polygonCollider2DManager_.GetComponent(entities[i]);

            polygonCollider.SetCentroid(physics::Vec2(otherCollider.centroid.x, otherCollider.centroid.y));
            polygonCollider.SetOffset(physics::Vec2(otherCollider.offset.x, otherCollider.offset.y));
            polygonCollider.SetIsTrigger(otherCollider.isTrigger);
            polygonCollider.SetFriction(otherCollider.friction);
            polygonCollider.SetRestitution(otherCollider.restitution);

            std::vector<physics::Vec2> vertices(otherCollider.vertices.size());
            for(int i = 0; i < otherCollider.vertices.size(); i++){
                vertices[i] = physics::Vec2(otherCollider.vertices[i].x, otherCollider.vertices[i].y);
            }

            physics::ShapeData shapeData{vertices};
            polygonCollider.SetShapes(shapeData);

            colliders.push_back(polygonCollider);
        }

        rigidBody.SetColliders(colliders);

        bodies[i] = rigidBody;
    }

    world_.SetBodies(bodies);
}

void WriteToPhysicsEngine::Destroy()
{

}
} //namespace neko
