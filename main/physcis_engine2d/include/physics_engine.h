#pragma once

#include <sdl_engine/sdl_engine.h>

namespace neko
{
class PhysicsEngine final : public sdl::SdlEngine
{
public:
	explicit PhysicsEngine(Configuration* config = nullptr);
};
} // namespace neko