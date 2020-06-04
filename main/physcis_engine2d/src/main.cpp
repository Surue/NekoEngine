#include <physics_engine.h>
#include "gl/graphics.h"
#include "gl/gles3_window.h"

#include <stats.h>
#include <entity_viewer.h>
#include <transforms_viewer.h>
#include <body_viewer.h>
#include <box_collider_2d_viewer.h>
#include <circle_collider_2d_viewer.h>
#include <polygon_collider_2d_viewer.h>

int main(int argc, char** argv)
{
	neko::sdl::Gles3Window window;
	neko::gl::Gles3Renderer renderer;
	neko::PhysicsEngine engine;

	neko::EntityManager entityManager = neko::EntityManager();
	neko::EntityHierarchy entityHierarchy = neko::EntityHierarchy(entityManager);

	// Components manager
	neko::Transform2dManager transform2DManager = neko::Transform2dManager(entityManager);
	neko::physics::Body2dManager body2DManager = neko::physics::Body2dManager(entityManager);
	neko::physics::BoxCollider2dManager boxCollider2DManager = neko::physics::BoxCollider2dManager(entityManager);
	neko::physics::CircleCollider2dManager circleCollider2DManager = neko::physics::CircleCollider2dManager(entityManager);
	neko::physics::PolygonCollider2dManager polygonCollider2DManager = neko::physics::PolygonCollider2dManager(entityManager);

	//List of every tool
	neko::tool::StatsTool statsTool = neko::tool::StatsTool();
	neko::tool::EntityViewer entityViewer = neko::tool::EntityViewer(entityManager, entityHierarchy);

	// Components viewers
	neko::tool::Transform2dViewer transform2DViewer = neko::tool::Transform2dViewer(entityManager, transform2DManager);
	neko::tool::BodyViewer body2DViewer = neko::tool::BodyViewer(entityManager, body2DManager);
    neko::tool::BoxCollider2dViewer boxCollider2dViewer = neko::tool::BoxCollider2dViewer(entityManager, boxCollider2DManager);
    neko::tool::CircleCollider2dViewer circleCollider2dViewer = neko::tool::CircleCollider2dViewer(entityManager, circleCollider2DManager);
    neko::tool::PolygonCollider2dViewer polygonCollider2dViewer = neko::tool::PolygonCollider2dViewer(entityManager, polygonCollider2DManager);

	entityViewer.RegisterDrawComponentImGui(transform2DViewer);
	entityViewer.RegisterDrawComponentImGui(body2DViewer);
	entityViewer.RegisterDrawComponentImGui(boxCollider2dViewer);
	entityViewer.RegisterDrawComponentImGui(circleCollider2dViewer);
	entityViewer.RegisterDrawComponentImGui(polygonCollider2dViewer);

	//Assign every tools
	engine.RegisterOnDrawUi(statsTool);
	engine.RegisterOnDrawUi(entityViewer);

	//Start engine
	engine.SetWindowAndRenderer(&window, &renderer);
	engine.Init();
	engine.EngineLoop();
	return 0;
}
