#include "circle_collider_2d_viewer.h"

namespace neko::tool
{
CircleCollider2dViewer::CircleCollider2dViewer(EntityManager& entityManager, physics::CircleCollider2dManager& circleCollider2DManager) :
        entityManager_(entityManager),
        circleCollider2DManager_(circleCollider2DManager) {}

void CircleCollider2dViewer::DrawImGui(Entity entity)
{
    if(entity == INVALID_ENTITY)
        return;

    if(ImGui::CollapsingHeader("Circle Collider 2d"))
    {
        physics::CircleCollider2d newCollider = circleCollider2DManager_.GetComponent(entity);

        // Restitution
        auto restitution = newCollider.GetRestitution();
        if (ImGui::DragFloat("Restitution", &restitution))
        {
            newCollider.SetRestitution(restitution);
        }

        // Friction
        auto friction = newCollider.GetFriction();
        if (ImGui::DragFloat("Friction", &friction))
        {
            newCollider.SetFriction(friction);
        }

        // IsTrigger
        auto isTrigger = newCollider.IsTrigger();
        if (ImGui::Checkbox("Is Trigger", &isTrigger))
        {
            newCollider.SetIsTrigger(isTrigger);
        }

        // Offset
        auto offset = newCollider.GetOffset();
        if (ImGui::DragFloat2("Offset", &offset[0]))
        {
            newCollider.SetOffset(offset);
        }

        // Radius
        auto radius = newCollider.GetRadius();
        if (ImGui::DragFloat("radius", &radius))
        {
            newCollider.SetRadius(radius);
        }

        circleCollider2DManager_.SetComponent(entity, newCollider);

        //Infos
        const ImVec2 padding{10, 10};
        const ImVec2 p0 = ImGui::GetCursorScreenPos();
        ImGui::SetCursorScreenPos(ImVec2(p0.x + padding.x, p0.y + padding.y));
        ImGui::BeginGroup();
        ImGui::TextColored({0.6f, 0.6f, 0.6f, 1.0f}, "Infos:");
        //Centroid
        ImGui::TextColored(
                {0.5f, 0.5f, 0.5f, 1.0f},
                "Centroid : (%.2f, %.2f)",
                newCollider.GetCentroid().x,
                newCollider.GetCentroid().y);

        ImGui::EndGroup();
        ImVec2 p1 = ImVec2(
                ImGui::GetItemRectMax().x + padding.x,
                ImGui::GetItemRectMax().y + padding.y);
        ImGui::Dummy(ImVec2(0.0f, padding.y));
        ImGui::GetWindowDrawList()->AddRect(p0, p1, IM_COL32(120, 120, 120, 255), 10.0f);
    }
}
} // namespace neko::tool
