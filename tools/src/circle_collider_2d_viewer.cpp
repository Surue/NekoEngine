#include "circle_collider_2d_viewer.h"

namespace neko::tool
{
CircleCollider2dViewer::CircleCollider2dViewer(EntityManager& entityManager, CircleCollider2dManager& circleCollider2DManager) :
        entityManager_(entityManager),
        circleCollider2DManager_(circleCollider2DManager) {}

void CircleCollider2dViewer::DrawImGui(Entity entity)
{
    if(entity == INVALID_ENTITY)
        return;

    if(ImGui::CollapsingHeader("Circle Collider 2d"))
    {
        CircleCollider2d newCollider = circleCollider2DManager_.GetComponent(entity);

        // Restitution
        ImGui::DragFloat("Restitution", &newCollider.restitution);

        // Friction
        ImGui::DragFloat("Friction", &newCollider.friction);

        // IsTrigger
        ImGui::Checkbox("Is Trigger", &newCollider.isTrigger);

        // Offset
        ImGui::DragFloat2("Offset", &newCollider.offset[0]);

        // Radius
        ImGui::DragFloat("radius", &newCollider.radius);

        circleCollider2DManager_.SetComponent(entity, newCollider);
    }
}
} // namespace neko::tool
