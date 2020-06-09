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

void DebugDrawer2d::DrawVector(physics::Vec2 origin, physics::Vec2 direction, float length)
{
    Vec3f endPosition = WorldToScreen(origin + direction * length);

    lineRenderer_.DrawLine(Line(WorldToScreen(origin), endPosition));
}

void DebugDrawer2d::DrawAABB(physics::Vec2 bottomLeft, physics::Vec2 topRight)
{
    lineRenderer_.DrawLine(Line(
            WorldToScreen(bottomLeft),
            WorldToScreen(bottomLeft + Vec2(topRight.x, bottomLeft.y))
            ));

    lineRenderer_.DrawLine(Line(
            WorldToScreen(bottomLeft),
            WorldToScreen(bottomLeft + Vec2(bottomLeft.x, topRight.y))
    ));

    lineRenderer_.DrawLine(Line(
            WorldToScreen(bottomLeft + Vec2(topRight.x, bottomLeft.y)),
            WorldToScreen(topRight)
    ));

    lineRenderer_.DrawLine(Line(
            WorldToScreen(bottomLeft + Vec2(bottomLeft.x, topRight.y)),
            WorldToScreen(topRight)
    ));
}

void DebugDrawer2d::DrawCircle(Vec2 center, float radius)
{

    float x = radius * cosf(0);
    float y = radius * sinf(0);
    Vec2 lastPos = {x + center.x, y + center.y};

    for (int i = 1; i <= nbSegmentCircle_; i++)   {
        float theta = 2.0f * neko::PI * float(i) / float(nbSegmentCircle_);

        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        Vec2 newPos = {x + center.x, y + center.y};
        lineRenderer_.DrawLine(Line(WorldToScreen(lastPos), WorldToScreen(newPos)));
        lastPos = newPos;
    }
}
} // namespace neko::physics
