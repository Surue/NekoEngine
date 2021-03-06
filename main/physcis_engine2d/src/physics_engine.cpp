#include <physics_engine.h>
#include <01_rigidbody_gravity/rigidbody_gravity_program.h>
#include <02_quadtree/quadtree_program.h>
#include <03_simple_collision/simple_collision_program.h>
#include <04_restitution/restitution_program.h>
#include <05_friction/friction_program.h>
#include <06_torque/torque_program.h>
#include <97_planet/planet_program.h>
#include <98_balistic/balistic_program.h>
#include <99_grapher/grapher_program.h>

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
    simulationBrowser_.RegisterSimulation("01 Rigidbody with gravity", std::make_unique<RigidBodyGravityProgram>());
    simulationBrowser_.RegisterSimulation("02 Quadtree", std::make_unique<QuadTreeProgram>(transform2DManager_, body2DManager_, world_.GetQuadTree()));
    simulationBrowser_.RegisterSimulation("03 Simple Collision", std::make_unique<SimpleCollisionProgram>());
    simulationBrowser_.RegisterSimulation("04 Restitution", std::make_unique<RestitutionProgram>());
    simulationBrowser_.RegisterSimulation("05 Friction", std::make_unique<FrictionProgram>(transform2DManager_, boxCollider2DManager_));
    simulationBrowser_.RegisterSimulation("06 Torque", std::make_unique<TorqueProgram>(transform2DManager_));
    simulationBrowser_.RegisterSimulation("97 Planet", std::make_unique<PlanetProgram>());
    simulationBrowser_.RegisterSimulation("Balistic", std::make_unique<BalisticProgram>());
    simulationBrowser_.RegisterSimulation("Grapher", std::make_unique<GrapherProgram>());
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
