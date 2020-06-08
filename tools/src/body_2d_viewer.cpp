#include "../include/body_2d_viewer.h"

#include <imgui.h>

neko::tool::Body2dViewer::Body2dViewer(neko::EntityManager& entityManager, neko::physics::Body2dManager& body2dManager) :
    entityManager_(entityManager),
    body2dManager_(body2dManager){}

void neko::tool::Body2dViewer::DrawImGui(neko::Entity entity) {
    if(entity == INVALID_ENTITY)
        return;

    if(ImGui::CollapsingHeader("Body2d"))
    {
        physics::Body newBody = body2dManager_.GetComponent(entity);

        //Gravity scale
        auto gravityScale = newBody.GetGravityScale();
        if (ImGui::DragFloat("Gravity scale", &gravityScale))
        {
            newBody.SetGravityScale(gravityScale);
        }

        //Mass
        auto mass = newBody.GetMass();
        if (ImGui::DragFloat("Mass", &mass))
        {
            newBody.SetMass(mass);
            newBody.SetInvMass(1.0f / mass);
        }

        //Body type
        auto bodyType = newBody.GetBodyType();
        const char* bodyTypeNames[] = {"Static", "Dynamic", "Kinematic"};
        int itemCurrent = static_cast<int>(bodyType);

        if (ImGui::BeginCombo("Body Type", bodyTypeNames[static_cast<int>(bodyType)])) {
            for (int i = 0; i < IM_ARRAYSIZE(bodyTypeNames); i++) {
                const bool isSelected = itemCurrent == i;

                if (ImGui::Selectable(bodyTypeNames[i], isSelected)) { itemCurrent = i; }
                if (isSelected) { ImGui::SetItemDefaultFocus(); }
            }
            newBody.SetBodyType(static_cast<physics::BodyType>(itemCurrent));
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
                newBody.GetLinearVelocity().x,
                newBody.GetLinearVelocity().y);

        //Angular Velocity
        ImGui::TextColored(
                {0.5f, 0.5f, 0.5f, 1.0f},
                "   Angular velocity : (%.2f)",
                newBody.GetAngularVelocity());

        //Force
        ImGui::TextColored(
                {0.5f, 0.5f, 0.5f, 1.0f},
                "   Force : (%.2f, %.2f)",
                newBody.GetForce().x,
                newBody.GetForce().y);

        //Torque
        ImGui::TextColored(
                {0.5f, 0.5f, 0.5f, 1.0f},
                "   Torque : (%.2f)",
                newBody.GetTorque());

        ImGui::TextColored(
                {0.5f, 0.5f, 0.5f, 1.0f},
                "Transform");

        //Position
        ImGui::TextColored(
                {0.5f, 0.5f, 0.5f, 1.0f},
                "   Position : (%.2f, %.2f)",
                newBody.GetPosition().x,
                newBody.GetPosition().y);

        //Angle
        ImGui::TextColored(
                {0.5f, 0.5f, 0.5f, 1.0f},
                "   Angle : (%.2f)",
                newBody.GetAngle());

        ImGui::TextColored(
                {0.5f, 0.5f, 0.5f, 1.0f},
                "Mass");
        //Inverse mass
        ImGui::TextColored(
                {0.5f, 0.5f, 0.5f, 1.0f},
                "   Inv Mass : (%.2f)",
                newBody.GetInvMass());

        ImGui::EndGroup();
        ImVec2 p1 = ImVec2(
                ImGui::GetItemRectMax().x + padding.x,
                ImGui::GetItemRectMax().y + padding.y);
        ImGui::Dummy(ImVec2(0.0f, padding.y));
        ImGui::GetWindowDrawList()->AddRect(p0, p1, IM_COL32(120, 120, 120, 255), 10.0f);
    }
}
