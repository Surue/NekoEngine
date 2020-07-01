#include <06_torque/torque_program.h>

#include <matrix.h>

namespace neko {
TorqueProgram::TorqueProgram(Transform2dManager& transform2DManager) : transform2DManager_(transform2DManager) {}

void TorqueProgram::LoadSimulation(EntityManager& entityManager, Transform2dManager& transform2DManager,
                                   Body2dManager& body2DManager, BoxCollider2dManager& boxCollider2DManager,
                                   CircleCollider2dManager& circleCollider2DManager,
                                   PolygonCollider2dManager& polygonCollider2DManager)
{
    bodies_.resize(nbPentagon_);

    for(int i = 0; i < nbPentagon_; i++){
        //Create an entity
        auto entity = entityManager.CreateEntity();

        //Add transform, body and circleCollider
        transform2DManager.AddComponent(entity);
        body2DManager.AddComponent(entity);
        polygonCollider2DManager.AddComponent(entity);

        //Set position
        transform2DManager.SetPosition(entity, Vec2f(RandomRange(-50.0f, 50.0f), RandomRange(-50.0f, 50.0f)));

        //Set the body type to dynamic
        auto body = body2DManager.GetComponent(entity);
        body.bodyType = BodyType::DYNAMIC;
        body.gravityScale = 0.0f;
        body2DManager.SetComponent(entity, body);

        //Set circle collider
        auto collider = polygonCollider2DManager.GetComponent(entity);
        collider.restitution = 0.0f;
        collider.friction = 0.0f;
        collider.vertices = GeneratePentagon(RandomRange(1.0f, 5.0f));
        collider.centroid = Vec2f(0.0f,0.0f);
        collider.isTrigger = false;
        polygonCollider2DManager.SetComponent(entity, collider);

        bodies_[i] = entity;
    }

    for(int i = 0; i < nbPlatform_; i++){
        //Create an entity
        auto entity = entityManager.CreateEntity();

        //Add transform, body and circleCollider
        transform2DManager.AddComponent(entity);
        body2DManager.AddComponent(entity);
        boxCollider2DManager.AddComponent(entity);

        //Set position
        transform2DManager.SetPosition(entity, Vec2f(RandomRange(-50.0f, 50.0f), RandomRange(-50.0f, 50.0f)));
        transform2DManager.SetRotation(entity, RandomRange(-0.5f, 0.5f));

        //Set the body type to dynamic
        auto body = body2DManager.GetComponent(entity);
        body.bodyType = BodyType::STATIC;
        body.gravityScale = 0.0f;
        body2DManager.SetComponent(entity, body);

        //Set circle collider
        auto collider = boxCollider2DManager.GetComponent(entity);
        collider.restitution = 0.0f;
        collider.friction = 0.0f;
        collider.extent = Vec2f(20.0f, 2.0f);
        collider.centroid = Vec2f(0.0f,0.0f);
        collider.isTrigger = false;
        boxCollider2DManager.SetComponent(entity, collider);
    }
}

std::vector<Vec2f> TorqueProgram::GeneratePentagon(float radius)
{
    float factor = (2.0f * PI / nbPentagonPoint_);

    std::vector<Vec2f> points = std::vector<Vec2f>(nbPentagonPoint_);

    for(int i = 0; i < nbPentagonPoint_; i++){
        auto physicsVec = physics::Mat22::GetRotationMatrix(factor * i) * physics::Vec2(0, radius);
        points[i] = Vec2f(physicsVec.x, physicsVec.y);
    }
    return points;
}

void TorqueProgram::Update(seconds dt) {
    for(int i = 0; i < bodies_.size(); i++){
        if(transform2DManager_.GetPosition(bodies_[i]).y < -60.0f){
            transform2DManager_.SetPosition(bodies_[i], Vec2f(RandomRange(-50.0f, 50.0f), 60.0f));
        }
    }
}
} //namespace neko