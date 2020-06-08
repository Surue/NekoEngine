#include "world_to_transform.h"

namespace neko{

WorldToTransform::WorldToTransform(physics::World& world, EntityManager& entityManager,
                                   Transform2dManager& transform2DManager, physics::Body2dManager& body2DManager) :
        world_(world),
        entityManager_(entityManager),
        transform2DManager_(transform2DManager),
        body2DManager_(body2DManager){

}

void WorldToTransform::Init() {

}

void WorldToTransform::Update(seconds dt) {
    std::cout << "world to transform\n";
    const std::vector<physics::Body2d>& bodies = world_.RetriveBodies();

    const EntityMask entityMask = EntityMask((uint32_t)ComponentType::BODY2D | (uint32_t)ComponentType::TRANSFORM2D);

    std::vector<Entity> entities = entityManager_.FilterEntities(entityMask);

    for(int i = 0; i < entities.size(); i++){
        const auto body = bodies[i];

        //Update body component
        body2DManager_.SetComponent(entities[i], body);

        //Update position
        const auto pos = body.GetPosition();
        transform2DManager_.SetPosition(entities[i], Vec2f(pos.x, pos.y));

        //Update angle
        const auto angle = body.GetAngle();
        transform2DManager_.SetRotation(entities[i], angle);
    }
}

void WorldToTransform::Destroy() {

}
} //namespace neko