#include <physics_engine.h>
#include "gl/graphics.h"
#include "gl/gles3_window.h"

int main(int argc, char** argv)
{
	neko::sdl::Gles3Window window;
	neko::gl::Gles3Renderer renderer;
	neko::PhysicsEngine engine;

	engine.SetWindowAndRenderer(&window, &renderer);
	engine.Init();
	engine.EngineLoop();
	return 0;
}
