#include "read_from_physics_engine.h"

#include "rigidbody.h"

namespace neko{

ReadFromPhysicsEngine::ReadFromPhysicsEngine(physics::World& world, EntityManager& entityManager,
                                             Transform2dManager& transform2DManager, Body2dManager& body2DManager,
                                             BoxCollider2dManager& boxCollider2DManager,
                                             CircleCollider2dManager& circleCollider2DManager,
                                             PolygonCollider2dManager& polygonCollider2DManager) :
        world_(world),
        entityManager_(entityManager),
        transform2DManager_(transform2DManager),
        body2DManager_(body2DManager),
        boxCollider2DManager_(boxCollider2DManager),
        circleCollider2DManager_(circleCollider2DManager),
        polygonCollider2DManager_(polygonCollider2DManager){

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

        // Update Box Colliders
        if(entityManager_.HasComponent(entities[i], EntityMask(ComponentType::BOX_COLLIDER2D))){
            physics::Collider boxCollider;
            for(int i = 0; i < rigidBody.GetColliders().size(); i++){
                if(rigidBody.GetColliders()[i].GetShape().shapeType == ShapeType::BOX){
                    boxCollider = rigidBody.GetColliders()[i];
                    break;
                }
            }

            auto otherCollider = boxCollider2DManager_.GetComponent(entities[i]);

            otherCollider.centroid = Vec2f(boxCollider.GetCentroid().x, boxCollider.GetCentroid().y);
            otherCollider.offset = Vec2f(boxCollider.GetOffset().x, boxCollider.GetOffset().y);
            otherCollider.isTrigger = boxCollider.IsTrigger();
            otherCollider.friction = boxCollider.GetFriction();
            otherCollider.restitution = boxCollider.GetRestitution();

            const auto shape = std::get<physics::BoxShape>(boxCollider.GetShape().shape);
            otherCollider.extent = Vec2f(shape.GetExtent().x, shape.GetExtent().y);

            boxCollider2DManager_.SetComponent(entities[i], otherCollider);
        }

        //Update circle collider
        if(entityManager_.HasComponent(entities[i], EntityMask(ComponentType::CIRCLE_COLLIDER2D))){
            physics::Collider circleCollider;
            for(int i = 0; i < rigidBody.GetColliders().size(); i++){
                if(rigidBody.GetColliders()[i].GetShape().shapeType == ShapeType::CIRCLE){
                    circleCollider = rigidBody.GetColliders()[i];
                    break;
                }
            }

            auto otherCollider = circleCollider2DManager_.GetComponent(entities[i]);

            otherCollider.centroid = Vec2f(circleCollider.GetCentroid().x, circleCollider.GetCentroid().y);
            otherCollider.offset = Vec2f(circleCollider.GetOffset().x, circleCollider.GetOffset().y);
            otherCollider.isTrigger = circleCollider.IsTrigger();
            otherCollider.friction = circleCollider.GetFriction();
            otherCollider.restitution = circleCollider.GetRestitution();

            const auto shape = std::get<physics::CircleShape>(circleCollider.GetShape().shape);
            otherCollider.radius = shape.GetRadius();

            circleCollider2DManager_.SetComponent(entities[i], otherCollider);
        }

        if(entityManager_.HasComponent(entities[i], EntityMask(ComponentType::POLYGON_COLLIDER2D))){
            physics::Collider circleCollider;
            for(int i = 0; i < rigidBody.GetColliders().size(); i++){
                if(rigidBody.GetColliders()[i].GetShape().shapeType == ShapeType::POLYGON){
                    circleCollider = rigidBody.GetColliders()[i];
                    break;
                }
            }

            auto otherCollider = polygonCollider2DManager_.GetComponent(entities[i]);

            otherCollider.centroid = Vec2f(circleCollider.GetCentroid().x, circleCollider.GetCentroid().y);
            otherCollider.offset = Vec2f(circleCollider.GetOffset().x, circleCollider.GetOffset().y);
            otherCollider.isTrigger = circleCollider.IsTrigger();
            otherCollider.friction = circleCollider.GetFriction();
            otherCollider.restitution = circleCollider.GetRestitution();

            const auto shape = std::get<physics::PolygonShape>(circleCollider.GetShape().shape);
            std::vector<Vec2f> vertices(shape.GetVertices().size());
            for(int i = 0; i < vertices.size(); i++){
                vertices[i] = {shape.GetVertices()[i].x, shape.GetVertices()[i].y};
            }
            otherCollider.vertices = vertices;

            polygonCollider2DManager_.SetComponent(entities[i], otherCollider);
        }
    }
}

void ReadFromPhysicsEngine::Destroy() {

}
} //namespace neko