#include <02_quadtree/quadtree_program.h>

#include <imgui.h>

#include <debug_drawer_2d.h>

namespace neko{
QuadTreeProgram::QuadTreeProgram(
        Transform2dManager& transform2DManager,
        Body2dManager& body2DManager) :
        transform2DManager_(transform2DManager),
        body2DManager_(body2DManager){}

void QuadTreeProgram::Init()
{

}

void QuadTreeProgram::LoadSimulation(
        EntityManager& entityManager,
        Transform2dManager& transform2DManager,
        Body2dManager& body2DManager,
        BoxCollider2dManager& boxCollider2DManager,
        CircleCollider2dManager& circleCollider2DManager,
        PolygonCollider2dManager& polygonCollider2DManager)
{
    entities_.resize(nbEntityToSpawn);

    for(int i = 0; i < nbEntityToSpawn; i++){
        //Create an entity in the center of the scree
        auto entity = entityManager.CreateEntity();

        entities_[i] = entity;

        transform2DManager.AddComponent(entity);
        body2DManager.AddComponent(entity);

        //Set position at the center of the screen
        transform2DManager.SetPosition(entity, Vec2f(RandomRange(-spawnArea.x, spawnArea.x), RandomRange(-spawnArea.y, spawnArea.y)));

        //Set the body type to kinematic without gravity
        auto body = body2DManager.GetComponent(entity);
        body.bodyType = BodyType::KINEMATIC;
        body.gravityScale = 0;

        //Set Random velocity
        body.linearVelocity = Vec2f(RandomRange(-1, 1), RandomRange(-1, 1));

        body2DManager.SetComponent(entity, body);
    }
}

void QuadTreeProgram::Update(seconds dt)
{
    for(const Entity entity : entities_){
        auto pos = transform2DManager_.GetPosition(entity);
        auto body = body2DManager_.GetComponent(entity);
        auto vel = body.linearVelocity;

        if(pos.x > spawnArea.x){
            vel.x = -vel.x;
            pos.x = spawnArea.x;
        }
        if(pos.x < -spawnArea.x){
            vel.x = -vel.x;
            pos.x = -spawnArea.x;
        }

        if(pos.y > spawnArea.y){
            vel.y = -vel.y;
            pos.y = spawnArea.y;
        }
        if(pos.y < -spawnArea.y){
            vel.y = -vel.y;
            pos.y = -spawnArea.y;
        }

        body.linearVelocity = vel;
        body2DManager_.SetComponent(entity, body);
        transform2DManager_.SetPosition(entity, pos);

        physics::DebugDrawer2dLocator::get().DrawCircle(physics::Vec2(pos.x, pos.y), 0.2f);
    }

    //Draw area
    physics::DebugDrawer2dLocator::get().DrawAABB(physics::Vec2(-spawnArea.x, -spawnArea.y), physics::Vec2(spawnArea.x, spawnArea.y), Color3(1, 1, 0));
}

void QuadTreeProgram::Destroy()
{

}

void QuadTreeProgram::DrawImGui() {
    //Set spawnArea
    ImGui::DragFloat2("Area", &spawnArea[0]);
}

} //namespace neko