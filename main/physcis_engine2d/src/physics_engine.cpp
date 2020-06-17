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
        transformToWorld_(world_, entityManager_, transform2DManager_, body2DManager_, boxCollider2DManager_, circleCollider2DManager_, polygonCollider2DManager_),
        worldToTransform_(world_, entityManager_, transform2DManager_, body2DManager_, boxCollider2DManager_, circleCollider2DManager_, polygonCollider2DManager_),
        simulationBrowser_(entityManager_, transform2DManager_, body2DManager_, boxCollider2DManager_, circleCollider2DManager_, polygonCollider2DManager_)
{
    //Register systems
    RegisterSystem(transformToWorld_);
    RegisterSystem(world_);
    RegisterSystem(worldToTransform_);
    RegisterSystem(debugDrawer2D_);
    RegisterSystem(simulationBrowser_);

    //Register component viewers
    entityViewer_.RegisterDrawComponentImGui(transform2DViewer_);
    entityViewer_.RegisterDrawComponentImGui(body2DViewer_);
    entityViewer_.RegisterDrawComponentImGui(boxCollider2DViewer_);
    entityViewer_.RegisterDrawComponentImGui(circleCollider2DViewer_);
    entityViewer_.RegisterDrawComponentImGui(polygonCollider2DViewer_);

    //Assign every tools
    RegisterOnDrawUi(statsTool_);
    RegisterOnDrawUi(entityViewer_);
    RegisterOnDrawUi(simulationBrowser_);

    //Locator
    physics::DebugDrawer2dLocator::provide(&debugDrawer2D_);

    //Register all simulation
    simulationBrowser_.RegisterSimulation("Rigidbody with gravity", std::make_unique<RigidBodyGravityProgramProgram>());
    simulationBrowser_.RegisterSimulation("Grapher", std::make_unique<GrapherProgram>());
    simulationBrowser_.RegisterSimulation("Balistic", std::make_unique<BalisticProgram>());
}

void PhysicsEngine::Init()
{
    SdlEngine::Init();
}

void PhysicsEngine::SetWindowAndRenderer(Window* window, Renderer* renderer)
{
    BasicEngine::SetWindowAndRenderer(window, renderer);

    debugDrawer2D_.SetWindow(window);
}
} //namespace neko
