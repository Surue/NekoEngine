#include <physics_engine.h>
#include "gl/graphics.h"
#include "gl/gles3_window.h"

#include <stats.h>

int main(int argc, char** argv)
{
	neko::sdl::Gles3Window window;
	neko::gl::Gles3Renderer renderer;
	neko::PhysicsEngine engine;

	neko::tool::StatsTool statsTool = neko::tool::StatsTool();

	engine.RegisterOnDrawUi(statsTool);

	engine.SetWindowAndRenderer(&window, &renderer);
	engine.Init();
	engine.EngineLoop();
	return 0;
}
