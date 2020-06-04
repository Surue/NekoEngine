
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
        if (ImGui::InputFloat("Restitution", &restitution))
        {
            newCollider.SetRestitution(restitution);
        }

        // Friction
        auto friction = newCollider.GetFriction();
        if (ImGui::InputFloat("Friction", &friction))
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
        if (ImGui::InputFloat2("Offset", &offset[0]))
        {
            newCollider.SetOffset(offset);
        }
        // Centroid
        auto centroid = newCollider.GetCentroid();
        if (ImGui::InputFloat2("Centroid", &centroid[0]))
        {
            newCollider.SetCentroid(centroid);
        }

        // Extent
        auto extent = newCollider.GetExtent();
        if (ImGui::InputFloat2("Extent", &extent[0]))
        {
            newCollider.SetExtent(extent);
        }

        boxCollider2DManager_.SetComponent(entity, newCollider);
    }
}
}
