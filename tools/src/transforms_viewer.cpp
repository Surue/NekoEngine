#include <transforms_viewer.h>

namespace neko::tool {

Transform2dViewer::Transform2dViewer(EntityManager& entityManager, Transform2dManager& transform2dManager) :
    entityManager_(entityManager),
    transform2dManager_(transform2dManager)
{

}

void Transform2dViewer::DrawImGui(Entity entity)
{
    if(entity == INVALID_ENTITY)
        return;

    if(ImGui::CollapsingHeader("Transform2d"))
    {
        //Position
        if (entityManager_.HasComponent(entity, static_cast<EntityMask>(ComponentType::POSITION2D)))
        {
            auto position = transform2dManager_.GetPosition(entity);
            if (ImGui::InputFloat2("Position", &position[0]))
            {
                transform2dManager_.SetPosition(entity, position);
            }
        }

        //Scale
        if (entityManager_.HasComponent(entity, static_cast<EntityMask>(ComponentType::SCALE2D)))
        {
            auto scale = transform2dManager_.GetScale(entity);
            if (ImGui::InputFloat2("Scale", &scale[0]))
            {
                transform2dManager_.SetScale(entity, scale);
            }
        }

        //Rotation
        if (entityManager_.HasComponent(entity, static_cast<EntityMask>(ComponentType::ROTATION2D)))
        {
            auto eulerAngle = transform2dManager_.GetRotation(entity);
            if (ImGui::InputFloat("Euler Angle", &eulerAngle))
            {
                transform2dManager_.SetRotation(entity, eulerAngle);
            }
        }
    }
}

Transform3dViewer::Transform3dViewer(EntityManager& entityManager, Transform3dManager& transform3dManager) :
    entityManager_(entityManager),
    transform3dManager_(transform3dManager)
{ }

void Transform3dViewer::DrawImGui(Entity entity)
{
    if(entity == INVALID_ENTITY)
        return;
    if(entityManager_.HasComponent(entity, static_cast<EntityMask>(ComponentType::TRANSFORM3D)))
    {
        auto position = transform3dManager_.GetPosition(entity);
        if (ImGui::InputFloat3("Position", &position[0]))
        {
            transform3dManager_.SetPosition(entity, position);
        }
        auto scale = transform3dManager_.GetScale(entity);
        if(ImGui::InputFloat3("Scale", &scale[0]))
        {
            transform3dManager_.SetScale(entity, scale);
        }
        const auto eulerAngles = transform3dManager_.GetAngles(entity);
        float angles[3] = { eulerAngles.x.value(), eulerAngles.y.value(), eulerAngles.z.value() };
        if(ImGui::InputFloat3("Euler Angles", &angles[0]))
        {
            const EulerAngles newEulerAngles = EulerAngles(degree_t(angles[0]), degree_t(angles[1]), degree_t(angles[2]));
            transform3dManager_.SetRotation(entity, newEulerAngles);
        }
    }
}
} // namespace neko::tool