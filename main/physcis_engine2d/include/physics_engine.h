#pragma once

#include <sdl_engine/sdl_engine.h>
#include <physics/world.h>

namespace neko
{
class PhysicsEngine final : public sdl::SdlEngine
{
public:
	explicit PhysicsEngine(Configuration* config = nullptr);

	physics::World world_;
};
} // namespace neko