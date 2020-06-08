#include "transform_to_world.h"

#include "body_2d.h"

namespace neko {

TransformToWorld::TransformToWorld(
        physics::World& world,
        EntityManager& entityManager,
        Transform2dManager& transform2DManager,
        physics::Body2dManager& body2DManager) :
        world_(world),
        entityManager_(entityManager),
        transform2DManager_(transform2DManager),
        body2DManager_(body2DManager) {}

void TransformToWorld::Init() {

}

void TransformToWorld::Update(seconds dt) {
    std::cout << "Transform To World\n";

    EntityMask entityMask = EntityMask((uint32_t)ComponentType::BODY2D | (uint32_t)ComponentType::TRANSFORM2D);

    std::vector<Entity> entities = entityManager_.FilterEntities(entityMask);

    std::vector<physics::Body2d> bodies;
    bodies.resize(entities.size());

    for(int i = 0; i < entities.size(); i++){
        auto body = body2DManager_.GetComponent(entities[i]);

        //Update position
        auto pos = transform2DManager_.GetPosition(entities[i]);
        body.SetPosition(physics::Vec2(pos.x, pos.y));

        //Update angle
        auto angle = transform2DManager_.GetRotation(entities[i]);
        body.SetAngle(angle);

        body2DManager_.SetComponent(entities[i], body);

        bodies[i] = body;
    }

    world_.SetBodies(bodies);
}

void TransformToWorld::Destroy() {

}
} //namespace neko
