#include <physics_engine.h>
#include "gl/graphics.h"
#include "gl/gles3_window.h"

#include <stats.h>
#include <entity_viewer.h>
#include <transforms_viewer.h>

int main(int argc, char** argv)
{
	neko::sdl::Gles3Window window;
	neko::gl::Gles3Renderer renderer;
	neko::PhysicsEngine engine;

	neko::EntityManager entityManager = neko::EntityManager();
	neko::EntityHierarchy entityHierarchy = neko::EntityHierarchy(entityManager);

	// Components manager
	neko::Transform2dManager transform2DManager = neko::Transform2dManager(entityManager);

	//List of every tool
	neko::tool::StatsTool statsTool = neko::tool::StatsTool();
	neko::tool::EntityViewer entityViewer = neko::tool::EntityViewer(entityManager, entityHierarchy);

	// Components viewers
	neko::tool::Transform2dViewer transform2DViewer = neko::tool::Transform2dViewer(entityManager, transform2DManager);

	entityViewer.RegisterDrawComponentImGui(transform2DViewer);

	//Assign every tools
	engine.RegisterOnDrawUi(statsTool);
	engine.RegisterOnDrawUi(entityViewer);

	//Start engine
	engine.SetWindowAndRenderer(&window, &renderer);
	engine.Init();
	engine.EngineLoop();
	return 0;
}
