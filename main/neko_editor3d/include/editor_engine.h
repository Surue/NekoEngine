#pragma once

#include <sdl_engine/sdl_engine.h>

namespace neko::editor
{
class PhysicsEngine : public sdl::SdlEngine
{
public:
	explicit PhysicsEngine(Configuration* config = nullptr);
};
}