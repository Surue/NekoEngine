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

        // Radius
        auto radius = newCollider.GetRadius();
        if (ImGui::InputFloat("radius", &radius))
        {
            newCollider.SetRadius(radius);
        }

        circleCollider2DManager_.SetComponent(entity, newCollider);
    }
}
} // namespace neko::tool
