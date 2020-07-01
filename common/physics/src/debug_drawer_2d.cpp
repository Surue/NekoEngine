#include <debug_drawer_2d.h>

#include <matrix.h>

namespace neko::physics {

void DebugDrawer2d::Init()
{
    lineRenderer_.Init();
    RendererLocator::get().RegisterSyncBuffersFunction(&lineRenderer_);
}

void DebugDrawer2d::Update(seconds dt)
{
    lineRenderer_.Update(dt);
}

void DebugDrawer2d::Destroy()
{

}

void DebugDrawer2d::DrawLine(physics::Vec2 p1, physics::Vec2 p2, const Color3& color) {
    lineRenderer_.DrawLine(Line(WorldToScreen(p1), WorldToScreen(p2), color));
}

Vec3f DebugDrawer2d::WorldToScreen(physics::Vec2 pos)
{
    const auto size = window_->GetSize();

    return Vec3f((pos.x / size.x) * pixelPerUnit_, (pos.y / size.y) * pixelPerUnit_, 0);
}

void DebugDrawer2d::DrawVector(physics::Vec2 origin, physics::Vec2 direction, float length, const Color3& color)
{
    Vec3f endPosition = WorldToScreen(origin + direction * length);

    lineRenderer_.DrawLine(Line(WorldToScreen(origin), endPosition, color));
}

void DebugDrawer2d::DrawAABB(physics::Vec2 bottomLeft, physics::Vec2 topRight, const Color3& color)
{
    //Draw line from bottom left to bottom right.
    lineRenderer_.DrawLine(Line(
            WorldToScreen(bottomLeft),
            WorldToScreen(Vec2(topRight.x, bottomLeft.y)),
            color
            ));

    //Draw line from bottom left to top Left.
    lineRenderer_.DrawLine(Line(
            WorldToScreen(bottomLeft),
            WorldToScreen(Vec2(bottomLeft.x, topRight.y)),
            color
    ));

    //Draw line from bottom right to top right.
    lineRenderer_.DrawLine(Line(
            WorldToScreen(Vec2(topRight.x, bottomLeft.y)),
            WorldToScreen(topRight),
            color
    ));

    //Draw line from top left to top right.
    lineRenderer_.DrawLine(Line(
            WorldToScreen(Vec2(bottomLeft.x, topRight.y)),
            WorldToScreen(topRight),
            color
    ));
}

void DebugDrawer2d::DrawCircle(Vec2 center, float radius, const Color3& color)
{

    float x = radius * cosf(0);
    float y = radius * sinf(0);
    Vec2 lastPos = {x + center.x, y + center.y};

    for (int i = 1; i <= nbSegmentCircle_; i++)   {
        float theta = 2.0f * neko::PI * float(i) / float(nbSegmentCircle_);

        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        Vec2 newPos = {x + center.x, y + center.y};
        lineRenderer_.DrawLine(Line(WorldToScreen(lastPos), WorldToScreen(newPos), color));
        lastPos = newPos;
    }
}

void DebugDrawer2d::DrawBox(Vec2 center, Vec2 extent, float angle, const Color3& color)
{
    Mat22 rotationMatrix = Mat22::GetRotationMatrix(angle);

    Vec2 posA, posB, posC, posD;
    posA = center + rotationMatrix * Vec2(-extent.x, -extent.y);
    posB = center + rotationMatrix * Vec2(extent.x, -extent.y);
    posC = center + rotationMatrix * Vec2(extent.x, extent.y);
    posD = center + rotationMatrix * Vec2(-extent.x, extent.y);

    lineRenderer_.DrawLine(Line(WorldToScreen(posA), WorldToScreen(posB), color));
    lineRenderer_.DrawLine(Line(WorldToScreen(posB), WorldToScreen(posC), color));
    lineRenderer_.DrawLine(Line(WorldToScreen(posC), WorldToScreen(posD), color));
    lineRenderer_.DrawLine(Line(WorldToScreen(posD), WorldToScreen(posA), color));
}

void DebugDrawer2d::DrawPolygon(Vec2 center, std::vector<Vec2> vertices, float angle, const Color3& color)
{
    Mat22 rotationMatrix = Mat22::GetRotationMatrix(angle);

    const int size = vertices.size();
    for(int i = 0; i <= size; i++){
        lineRenderer_.DrawLine(Line(
                WorldToScreen(rotationMatrix * vertices[i % size] + center) ,
                WorldToScreen(rotationMatrix * vertices[(i + 1) % size] + center),
                color));
    }
}
} // namespace neko::physics
