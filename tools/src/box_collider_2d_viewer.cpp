
#include <polygon_collider_2d_viewer.h>

#include "box_collider_2d_viewer.h"

namespace neko::tool {

BoxCollider2dViewer::BoxCollider2dViewer(EntityManager& entityManager, BoxCollider2dManager& boxCollider2DManager) :
        entityManager_(entityManager),
        boxCollider2DManager_(boxCollider2DManager){ }

void BoxCollider2dViewer::DrawImGui(Entity entity)
{
    if(entity == INVALID_ENTITY)
        return;

    if(ImGui::CollapsingHeader("Box Collider 2d"))
    {
        BoxCollider2d newCollider = boxCollider2DManager_.GetComponent(entity);

        // Restitution
        ImGui::DragFloat("Restitution", &newCollider.restitution);

        // Friction
        ImGui::DragFloat("Friction", &newCollider.friction);

        // IsTrigger
        ImGui::Checkbox("Is Trigger", &newCollider.isTrigger);

        // Offset
        ImGui::DragFloat2("Offset", &newCollider.offset[0]);

        // Extent
        ImGui::DragFloat2("Extent", &newCollider.extent[0]);

        boxCollider2DManager_.SetComponent(entity, newCollider);
    }
}
}
