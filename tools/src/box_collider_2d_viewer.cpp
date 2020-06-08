
#include <polygon_collider_2d_viewer.h>

#include "box_collider_2d_viewer.h"

namespace neko::tool {

BoxCollider2dViewer::BoxCollider2dViewer(EntityManager& entityManager, physics::BoxCollider2dManager& boxCollider2DManager) :
        entityManager_(entityManager),
        boxCollider2DManager_(boxCollider2DManager){ }

void BoxCollider2dViewer::DrawImGui(Entity entity)
{
    if(entity == INVALID_ENTITY)
        return;

    if(ImGui::CollapsingHeader("Box Collider 2d"))
    {
        physics::BoxCollider2d newCollider = boxCollider2DManager_.GetComponent(entity);

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

        // Extent
        auto extent = newCollider.GetExtent();
        if (ImGui::DragFloat2("Extent", &extent[0]))
        {
            newCollider.SetExtent(extent);
        }

        boxCollider2DManager_.SetComponent(entity, newCollider);

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
}
