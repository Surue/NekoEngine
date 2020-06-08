#include <physics_engine.h>

namespace neko
{
PhysicsEngine::PhysicsEngine(Configuration* config) :
        SdlEngine(config),
        entityManager_(),
        entityHierarchy_(entityManager_),
        transform2DManager_(entityManager_),
        body2DManager_(entityManager_),
        boxCollider2DManager_(entityManager_),
        circleCollider2DManager_(entityManager_),
        polygonCollider2DManager_(entityManager_),
        statsTool_(),
        entityViewer_(entityManager_, entityHierarchy_),
        transform2DViewer_(entityManager_, transform2DManager_),
        body2DViewer_(entityManager_, body2DManager_),
        boxCollider2DViewer_(entityManager_, boxCollider2DManager_),
        circleCollider2DViewer_(entityManager_, circleCollider2DManager_),
        polygonCollider2DViewer_(entityManager_, polygonCollider2DManager_),
        transformToWorld_(world_, entityManager_, transform2DManager_, body2DManager_),
        worldToTransform_(world_, entityManager_, transform2DManager_, body2DManager_){

    //Register systems
    RegisterSystem(transformToWorld_);
    RegisterSystem(world_);
    RegisterSystem(worldToTransform_);

    //Register component viewers
    entityViewer_.RegisterDrawComponentImGui(transform2DViewer_);
    entityViewer_.RegisterDrawComponentImGui(body2DViewer_);
    entityViewer_.RegisterDrawComponentImGui(boxCollider2DViewer_);
    entityViewer_.RegisterDrawComponentImGui(circleCollider2DViewer_);
    entityViewer_.RegisterDrawComponentImGui(polygonCollider2DViewer_);

    //Assign every tools
    RegisterOnDrawUi(statsTool_);
    RegisterOnDrawUi(entityViewer_);
}
} //namespace neko
