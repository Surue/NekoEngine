#pragma once

#include <engine/entity.h>
#include <engine/transform.h>

namespace neko::tool
{
class Transform2dViewer : public TemplateDrawComponentImGuiInterface<ComponentType::TRANSFORM2D>
{
public:
    explicit Transform2dViewer(EntityManager& entityManager, Transform2dManager& transform2dManager);
    ~Transform2dViewer() = default;

    void DrawImGui(Entity entity) override;
protected:
    EntityManager& entityManager_;
    Transform2dManager& transform2dManager_;
};

class Transform3dViewer : public TemplateDrawComponentImGuiInterface<ComponentType::TRANSFORM3D>
{
public:
    explicit Transform3dViewer(EntityManager& entityManager, Transform3dManager& transform3dManager);

    void DrawImGui(Entity entity) override;
protected:
    EntityManager& entityManager_;
    Transform3dManager& transform3dManager_;
};
} // namespace neko::tool