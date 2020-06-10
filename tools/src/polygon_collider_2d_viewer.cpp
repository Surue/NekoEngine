#include <polygon_collider_2d_viewer.h>

namespace neko::tool{
PolygonCollider2dViewer::PolygonCollider2dViewer(EntityManager& entityManager, PolygonCollider2dManager& polygonCollider2DManager) :
    entityManager_(entityManager),
    polygonCollider2DManager_(polygonCollider2DManager) {}

void PolygonCollider2dViewer::DrawImGui(Entity entity)
{
    if(entity == INVALID_ENTITY)
        return;

    if(ImGui::CollapsingHeader("Polygon Collider 2d"))
    {
        PolygonCollider2d newCollider = polygonCollider2DManager_.GetComponent(entity);

        // Restitution
        ImGui::DragFloat("Restitution", &newCollider.restitution);

        // Friction
        ImGui::DragFloat("Friction", &newCollider.friction);

        // IsTrigger
        ImGui::Checkbox("Is Trigger", &newCollider.isTrigger);

        // Offset
        ImGui::DragFloat2("Offset", &newCollider.offset[0]);

        // Points
        ImGui::Text("Vertices");
        const auto vertices = newCollider.vertices;
        std::vector<Vec2f> newVertices;
        newVertices.reserve(vertices.size());
        for (int i = 0; i < vertices.size(); i++){
            Vec2f newPos = vertices[i];
            if (ImGui::DragFloat2(("##point" + std::to_string(i)).c_str(), &newPos[0]), 0.1f);

            ImGui::SameLine();
            if(!ImGui::Button(("x##deletePoint" + std::to_string(i)).c_str())){
                newVertices.emplace_back(newPos);
            }
        }
        if(ImGui::Button("Add new point")){
            newVertices.emplace_back(Vec2f{});
        }

        newCollider.vertices = newVertices;

        polygonCollider2DManager_.SetComponent(entity, newCollider);

//        //Infos
//        const ImVec2 padding{10, 10};
//        const ImVec2 p0 = ImGui::GetCursorScreenPos();
//        ImGui::SetCursorScreenPos(ImVec2(p0.x + padding.x, p0.y + padding.y));
//        ImGui::BeginGroup();
//        ImGui::TextColored({0.6f, 0.6f, 0.6f, 1.0f}, "Infos:");
//        //Centroid
//        ImGui::TextColored(
//                {0.5f, 0.5f, 0.5f, 1.0f},
//                "Centroid : (%.2f, %.2f)",
//                newCollider.GetCentroid().x,
//                newCollider.GetCentroid().y);
//
//        ImGui::EndGroup();
//        ImVec2 p1 = ImVec2(
//                ImGui::GetItemRectMax().x + padding.x,
//                ImGui::GetItemRectMax().y + padding.y);
//        ImGui::Dummy(ImVec2(0.0f, padding.y));
//        ImGui::GetWindowDrawList()->AddRect(p0, p1, IM_COL32(120, 120, 120, 255), 10.0f);
    }
}
} //namespace neko::tool