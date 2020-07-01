#include <05_friction/friction_program.h>

#include <imgui.h>

namespace neko {
FrictionProgram::FrictionProgram(
        Transform2dManager& transform2DManager,
        BoxCollider2dManager& boxCollider2DManager) :
        transform2DManager_(transform2DManager),
        boxCollider2DManager_(boxCollider2DManager){}

void FrictionProgram::LoadSimulation(
        EntityManager& entityManager,
        Transform2dManager& transform2DManager,
        Body2dManager& body2DManager,
        BoxCollider2dManager& boxCollider2DManager,
        CircleCollider2dManager& circleCollider2DManager,
        PolygonCollider2dManager& polygonCollider2DManager)
{
    platformsEntities_.resize(nbBody_);
    quadEntities_.resize(nbBody_);

    for(int i = 0; i < nbBody_; i++){
        //Create an entity
        auto entity = entityManager.CreateEntity();

        //Add transform, body and circleCollider
        transform2DManager.AddComponent(entity);
        body2DManager.AddComponent(entity);
        boxCollider2DManager.AddComponent(entity);

        //Set position at the center of the screen
        if(nbBody_ % 2 == 0)
        {
            transform2DManager.SetPosition(entity, Vec2f((i - nbBody_ / 2.0f) * horizontalSpaceBetweenBall_ + horizontalSpaceBetweenBall_ * 0.5f, 40.0f));
        }else{
            transform2DManager.SetPosition(entity, Vec2f((i - nbBody_ / 2.0f) * horizontalSpaceBetweenBall_, 40.0f));
        }

        //Set the body type to dynamic
        auto body = body2DManager.GetComponent(entity);
        body.bodyType = BodyType::DYNAMIC;
        body.gravityScale = 1;
        body2DManager.SetComponent(entity, body);

        //Set circle collider
        auto collider = boxCollider2DManager.GetComponent(entity);
        collider.restitution = 0;
        collider.friction = ((i) / (nbBody_ - 1.0f));
        collider.extent = Vec2f(1, 1);
        collider.centroid = Vec2f(0,0);
        collider.isTrigger = false;
        boxCollider2DManager.SetComponent(entity, collider);

        quadEntities_[i] = entity;

        //add ground to slide on
        auto boxEntity = entityManager.CreateEntity();

        transform2DManager.AddComponent(boxEntity);
        body2DManager.AddComponent(boxEntity);
        boxCollider2DManager.AddComponent(boxEntity);

        //Set position at the center of the screen
        if(nbBody_ % 2 == 0)
        {
            transform2DManager.SetPosition(boxEntity, Vec2f((i - nbBody_ / 2.0f) * horizontalSpaceBetweenBall_ + horizontalSpaceBetweenBall_ * 0.5f + platformWidth_ * 0.5f, -20.0f));
        }else{
            transform2DManager.SetPosition(boxEntity, Vec2f((i - nbBody_ / 2.0f) * horizontalSpaceBetweenBall_ + platformWidth_ * 0.5f, -20.0f));
        }
        transform2DManager.SetRotation(boxEntity, angleInRadOfPlatforms_);

        auto boxBody = body2DManager.GetComponent(boxEntity);
        boxBody.bodyType = BodyType::STATIC;
        boxBody.gravityScale = 0;
        body2DManager.SetComponent(boxEntity, boxBody);

        auto boxCollider = boxCollider2DManager.GetComponent(boxEntity);
        boxCollider.extent = Vec2f(platformWidth_, platformHeight_);
        boxCollider.restitution = 0;
        boxCollider.friction = 0;
        boxCollider.isTrigger = false;
        boxCollider2DManager.SetComponent(boxEntity, boxCollider);

        platformsEntities_[i] = boxEntity;
    }
}

void FrictionProgram::DrawImGui() {
    float angelInDeg = angleInRadOfPlatforms_ * (180.0f / PI);
    ImGui::DragFloat("Angle", &angelInDeg);
    angleInRadOfPlatforms_ = angelInDeg * (PI / 180.0f);

    ImGui::DragFloat("Platforms friction", &platformFriction_, 0.01, 0.0f, 10.0f);

    if(ImGui::Button("Reset simulation")){
        mustReset_ = true;
    }
}

void FrictionProgram::Update(seconds dt) {
    for(const Entity e : platformsEntities_){
        transform2DManager_.SetRotation(e, angleInRadOfPlatforms_);

        auto boxCollider = boxCollider2DManager_.GetComponent(e);
        boxCollider.friction = platformFriction_;
        boxCollider2DManager_.SetComponent(e, boxCollider);
    }

    if(mustReset_){
        mustReset_ = false;

        for(int i = 0; i < nbBody_; i++){
            if(nbBody_ % 2 == 0)
            {
                transform2DManager_.SetPosition(quadEntities_[i], Vec2f((i - nbBody_ / 2.0f) * horizontalSpaceBetweenBall_ + horizontalSpaceBetweenBall_ * 0.5f, 40.0f));
            }else{
                transform2DManager_.SetPosition(quadEntities_[i], Vec2f((i - nbBody_ / 2.0f) * horizontalSpaceBetweenBall_, 40.0f));
            }
        }
    }
}
} //namespace neko

