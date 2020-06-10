#include "../include/body_2d_viewer.h"

#include <imgui.h>

neko::tool::Body2dViewer::Body2dViewer(neko::EntityManager& entityManager, neko::Body2dManager& body2dManager) :
    entityManager_(entityManager),
    body2dManager_(body2dManager){}

void neko::tool::Body2dViewer::DrawImGui(neko::Entity entity) {
    if(entity == INVALID_ENTITY)
        return;

    if(ImGui::CollapsingHeader("Body2d"))
    {
        Body2d newBody = body2dManager_.GetComponent(entity);

        //Gravity scale
        ImGui::DragFloat("Gravity scale", &newBody.gravityScale);

        //Mass
        if (ImGui::DragFloat("Mass", &newBody.mass))
        {
            newBody.invMass = 1.0f / newBody.mass;
        }

        //Body type
        auto bodyType = newBody.bodyType;
        const char* bodyTypeNames[] = {"Static", "Dynamic", "Kinematic"};
        int itemCurrent = static_cast<int>(bodyType);

        if (ImGui::BeginCombo("Body Type", bodyTypeNames[static_cast<int>(bodyType)])) {
            for (int i = 0; i < IM_ARRAYSIZE(bodyTypeNames); i++) {
                const bool isSelected = itemCurrent == i;

                if (ImGui::Selectable(bodyTypeNames[i], isSelected)) { itemCurrent = i; }
                if (isSelected) { ImGui::SetItemDefaultFocus(); }
            }
            newBody.bodyType= static_cast<BodyType>(itemCurrent);
            ImGui::EndCombo();
        }

        body2dManager_.SetComponent(entity, newBody);

        //Infos
        const ImVec2 padding{10, 10};
        const ImVec2 p0 = ImGui::GetCursorScreenPos();
        ImGui::SetCursorScreenPos(ImVec2(p0.x + padding.x, p0.y + padding.y));
        ImGui::BeginGroup();
        ImGui::TextColored({0.6f, 0.6f, 0.6f, 1.0f}, "Infos:");
        //Linear velocity
        ImGui::TextColored(
                {0.5f, 0.5f, 0.5f, 1.0f},
                "Forces");
        ImGui::TextColored(
                {0.5f, 0.5f, 0.5f, 1.0f},
                "   Linear velocity : (%.2f, %.2f)",
                newBody.linearVelocity.x,
                newBody.linearVelocity.y);

        //Angular Velocity
        ImGui::TextColored(
                {0.5f, 0.5f, 0.5f, 1.0f},
                "   Angular velocity : (%.2f)",
                newBody.angularVelocity);

        //Force
        ImGui::TextColored(
                {0.5f, 0.5f, 0.5f, 1.0f},
                "   Force : (%.2f, %.2f)",
                newBody.force.x,
                newBody.force.y);

        //Torque
        ImGui::TextColored(
                {0.5f, 0.5f, 0.5f, 1.0f},
                "   Torque : (%.2f)",
                newBody.torque);

        ImGui::TextColored(
                {0.5f, 0.5f, 0.5f, 1.0f},
                "Mass");
        //Inverse mass
        ImGui::TextColored(
                {0.5f, 0.5f, 0.5f, 1.0f},
                "   Inv Mass : (%.2f)",
                newBody.invMass);

        ImGui::EndGroup();
        ImVec2 p1 = ImVec2(
                ImGui::GetItemRectMax().x + padding.x,
                ImGui::GetItemRectMax().y + padding.y);
        ImGui::Dummy(ImVec2(0.0f, padding.y));
        ImGui::GetWindowDrawList()->AddRect(p0, p1, IM_COL32(120, 120, 120, 255), 10.0f);
    }
}
