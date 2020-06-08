#include <debug_drawer_2d.h>

namespace neko::physics {

void DebugDrawer2d::Init()
{
    lineRenderer_.Init();
    RendererLocator::get().RegisterSyncBuffersFunction(&lineRenderer_);
}

void DebugDrawer2d::Update(seconds dt)
{
    DrawLine({1, 0}, {0, 0});

    lineRenderer_.Update(dt);
}

void DebugDrawer2d::Destroy()
{

}

void DebugDrawer2d::DrawLine(physics::Vec2 p1, physics::Vec2 p2) {
    lineRenderer_.DrawLine(Line(WorldToScreen(p1), WorldToScreen(p2)));
}

Vec3f DebugDrawer2d::WorldToScreen(physics::Vec2 pos)
{
    const auto size = window_->GetSize();

    return Vec3f((pos.x / size.x) * pixelPerUnit_, (pos.y / size.y) * pixelPerUnit_, 0);
}
} // namespace neko::physics
