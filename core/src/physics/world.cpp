#include <physics/world.h>

namespace neko::physics {

void World::Init()
{
    std::cout << "Init world\n";
}

void World::Update(seconds dt)
{
    std::cout << dt.count() << "\n";
}

void World::Destroy()
{
    std::cout << "Destroy\n";
}
} // namespace neko::physics