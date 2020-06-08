#include <physics_engine.h>
#include "gl/graphics.h"
#include "gl/gles3_window.h"

#include <stats.h>
#include <entity_viewer.h>
#include <transforms_viewer.h>
#include <body_2d_viewer.h>
#include <box_collider_2d_viewer.h>
#include <circle_collider_2d_viewer.h>
#include <polygon_collider_2d_viewer.h>

int main(int argc, char** argv)
{
	neko::sdl::Gles3Window window;
	neko::gl::Gles3Renderer renderer;
	neko::PhysicsEngine engine;

	//Start engine
	engine.SetWindowAndRenderer(&window, &renderer);
	engine.Init();
	engine.EngineLoop();
	return 0;
}
