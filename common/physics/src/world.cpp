#include "../include/world.h"

namespace neko::physics {

void World::Init() {

}

void World::Update(seconds dt) {
    std::cout << "World\n";
    for (Body2d& body : bodies_) {

        Vec2 bodyPosition = body.GetPosition();

        bodyPosition = bodyPosition + Vec2(1, 0);

        body.SetPosition(bodyPosition);
    }
}

void World::Destroy() {

}
} // namespace neko::physics