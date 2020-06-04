#include <polygon_collider_2d_viewer.h>

namespace neko::tool{
PolygonCollider2dViewer::PolygonCollider2dViewer(EntityManager& entityManager, physics::PolygonCollider2dManager& polygonCollider2DManager) :
    entityManager_(entityManager),
    polygonCollider2DManager_(polygonCollider2DManager) {}

void PolygonCollider2dViewer::DrawImGui(Entity entity)
{
    if(entity == INVALID_ENTITY)
        return;

    if(ImGui::CollapsingHeader("Polygon Collider 2d"))
    {
        physics::PolygonCollider2d newCollider = polygonCollider2DManager_.GetComponent(entity);

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

        // Points

        ImGui::Text("Vertices");
        const auto vertices = newCollider.GetVertices();
        std::vector<physics::Vec2> newVertices;
        newVertices.reserve(vertices.size());
        for (int i = 0; i < vertices.size(); i++){
            physics::Vec2 newPos = vertices[i];
            if (ImGui::InputFloat2(("##point" + std::to_string(i)).c_str(), &newPos[0]));

            ImGui::SameLine();
            if(!ImGui::Button(("x##deletePoint" + std::to_string(i)).c_str())){
                newVertices.emplace_back(newPos);
            }
        }
        if(ImGui::Button("Add new point")){
            newVertices.emplace_back(physics::Vec2{});
        }

        newCollider.SetVertices(newVertices);

        polygonCollider2DManager_.SetComponent(entity, newCollider);
    }
}
} //namespace neko::tool