#include <physics_engine.h>

namespace neko
{
PhysicsEngine::PhysicsEngine(Configuration* config) : SdlEngine(config)
{
    RegisterSystem(world_);
}
} //namespace neko
