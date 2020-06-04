#include "../include/body_viewer.h"

#include <imgui.h>

neko::tool::BodyViewer::BodyViewer(neko::EntityManager& entityManager, neko::physics::Body2dManager& body2dManager) :
    entityManager_(entityManager),
    body2dManager_(body2dManager){}

void neko::tool::BodyViewer::DrawImGui(neko::Entity entity) {
    if(entity == INVALID_ENTITY)
        return;

    if(ImGui::CollapsingHeader("Body2d"))
    {
        physics::Body newBody = body2dManager_.GetComponent(entity);

        //Position
        auto position = newBody.GetPosition();
        if (ImGui::InputFloat2("Position", &position[0]))
        {
            newBody.SetPosition(position);
        }

        //Angle
        auto angle = newBody.GetAngle();
        if (ImGui::InputFloat("Angle", &angle))
        {
            newBody.SetAngle(angle);
        }

        //Gravity scale
        auto gravityScale = newBody.GetGravityScale();
        if (ImGui::InputFloat("Gravity scale", &gravityScale))
        {
            newBody.SetGravityScale(gravityScale);
        }

        //Linear velocity
        auto linearVelocity = newBody.GetLinearVelocity();
        if (ImGui::InputFloat2("Linear velocity", &linearVelocity[0]))
        {
            newBody.SetLinearVelocity(linearVelocity);
        }

        //Angular velocity
        auto angularVelocity = newBody.GetAngularVelocity();
        if (ImGui::InputFloat("Angular velocity", &angularVelocity))
        {
            newBody.SetAngularVelocity(angularVelocity);
        }

        //Force
        auto force = newBody.GetForce();
        if (ImGui::InputFloat2("Force", &force[0]))
        {
            newBody.SetForce(force);
        }

        //Torque
        auto torque = newBody.GetTorque();
        if (ImGui::InputFloat("Torque", &torque))
        {
            newBody.SetTorque(torque);
        }

        //Mass
        auto mass = newBody.GetMass();
        if (ImGui::InputFloat("Mass", &mass))
        {
            newBody.SetMass(mass);
            newBody.SetInvMass(1.0f / mass);
        }

        //Inverse Mass
        auto invMass = newBody.GetInvMass();
        if (ImGui::InputFloat("Inverse mass", &invMass))
        {
            newBody.SetInvMass(invMass);
            newBody.SetMass(1.0f / invMass);
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
    }
}
