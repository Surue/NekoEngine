#include <physics_engine.h>

namespace neko
{
PhysicsEngine::PhysicsEngine(Configuration* config) :
        SdlEngine(config),
        entityManager(),
        entityHierarchy(entityManager),
        transform2DManager(entityManager),
        body2DManager(entityManager),
        boxCollider2DManager(entityManager),
        circleCollider2DManager(entityManager),
        polygonCollider2DManager(entityManager),
        statsTool(),
        entityViewer(entityManager, entityHierarchy),
        transform2DViewer(entityManager, transform2DManager),
        body2DViewer(entityManager, body2DManager),
        boxCollider2dViewer(entityManager, boxCollider2DManager),
        circleCollider2dViewer(entityManager, circleCollider2DManager),
        polygonCollider2dViewer(entityManager, polygonCollider2DManager) {

    //Register systems
    RegisterSystem(world_);

    //Register component viewers
    entityViewer.RegisterDrawComponentImGui(transform2DViewer);
    entityViewer.RegisterDrawComponentImGui(body2DViewer);
    entityViewer.RegisterDrawComponentImGui(boxCollider2dViewer);
    entityViewer.RegisterDrawComponentImGui(circleCollider2dViewer);
    entityViewer.RegisterDrawComponentImGui(polygonCollider2dViewer);

    //Assign every tools
    RegisterOnDrawUi(statsTool);
    RegisterOnDrawUi(entityViewer);
}
} //namespace neko
