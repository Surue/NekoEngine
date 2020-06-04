#include <entity_viewer.h>

#include <imgui.h>
#include <engine/log.h>
#include <engine/component.h>
#include <cmath>

namespace neko::tool {
EntityViewer::EntityViewer(EntityManager& entityManager, EntityHierarchy& entityHierarchy) :
        entityHierarchy_(entityHierarchy),
        entityManager_(entityManager) { }

void EntityViewer::DrawImGui()
{
    //Hierarchy
    ImGui::Begin("Hierarchy");

    if (ImGui::BeginDragDropTarget())
    {
        ImGuiDragDropFlags target_flags = 0;
        //target_flags |= ImGuiDragDropFlags_AcceptBeforeDelivery;    // Don't wait until the delivery (release mouse button on a target) to do something
        target_flags |= ImGuiDragDropFlags_AcceptNoDrawDefaultRect; // Don't display the yellow rectangle
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DND_DEMO_NAME", target_flags))
        {
            const neko::Entity moveFrom = *static_cast<const neko::Entity*>(payload->Data);
            const neko::Entity moveTo = neko::INVALID_ENTITY;
            entityManager_.SetEntityParent(moveFrom, moveTo);
        }
        ImGui::EndDragDropTarget();
    }

    if (ImGui::Button("Add Entity"))
    {
        const auto entity = entityManager_.CreateEntity();
    }

    for(Entity entity = 0; entity < entityManager_.GetEntitiesSize(); entity++)
    {
        if(entityManager_.EntityExists(entity) and entityManager_.GetEntityParent(entity) == INVALID_ENTITY)
        {
            DrawEntityHierarchy(entity, true, false);
        }
    }
    ImGui::End();

    //Inspector
    if(selectedEntity_ == INVALID_ENTITY) { return; }

    ImGui::Begin("Inspector");

    for(auto it = componentViewers_.begin(); it != componentViewers_.end(); it++){
        if(entityManager_.HasComponent(selectedEntity_, (EntityMask)it->second->GetComponentType())){
            std::cout << "Entity[" << selectedEntity_ << "] has component " << (uint32_t)it->second->GetComponentType() << "\n";
            it->second->DrawImGui(selectedEntity_);
        }
    }

    ImGui::Dummy(ImVec2(0.0f, 20.0f));

    if (ImGui::Button("Add Component")) {
        ImGui::OpenPopup("component_popup");
    }

    if (ImGui::BeginPopup("component_popup"))
    {
        //Transform 2D
        if(!entityManager_.HasComponent(selectedEntity_, EntityMask(ComponentType::TRANSFORM2D))){
            if (ImGui::MenuItem("Transform 2d")) {
                entityManager_.AddComponentType(selectedEntity_, EntityMask(ComponentType::TRANSFORM2D));
            }
        }

        //Body 2D
        if(!entityManager_.HasComponent(selectedEntity_, EntityMask(ComponentType::BODY2D))){
            if (ImGui::MenuItem("Body 2d")) {
                entityManager_.AddComponentType(selectedEntity_, EntityMask(ComponentType::BODY2D));
            }
        }

        //Box collider 2D
        if(!entityManager_.HasComponent(selectedEntity_, EntityMask(ComponentType::BOX_COLLIDER2D))){
            if (ImGui::MenuItem("Box collider 2d")) {
                entityManager_.AddComponentType(selectedEntity_, EntityMask(ComponentType::BOX_COLLIDER2D));
            }
        }

        //Circle collider 2D
        if(!entityManager_.HasComponent(selectedEntity_, EntityMask(ComponentType::CIRCLE_COLLIDER2D))){
            if (ImGui::MenuItem("Circle collider 2d")) {
                entityManager_.AddComponentType(selectedEntity_, EntityMask(ComponentType::CIRCLE_COLLIDER2D));
            }
        }

        //Polygon collider 2D
        if(!entityManager_.HasComponent(selectedEntity_, EntityMask(ComponentType::POLYGON_COLLIDER2D))){
            if (ImGui::MenuItem("Polygon collider 2d")) {
                entityManager_.AddComponentType(selectedEntity_, EntityMask(ComponentType::POLYGON_COLLIDER2D));
            }
        }
        ImGui::EndPopup();
    }

    ImGui::End();
}

void EntityViewer::DrawEntityHierarchy(neko::Entity entity, bool draw, bool destroy)
{
    const std::string entityName = "Entity " + std::to_string(entity + 1);
    bool nodeOpen = draw;
    bool destroyEntity = destroy;
    bool createEntity = false;

    const bool leaf = !entityHierarchy_.HasChildren(entity);

    if (draw)
    {
        ImGuiTreeNodeFlags nodeFlags = ImGuiTreeNodeFlags_DefaultOpen;
        if (!leaf)
        {
            nodeFlags |= ImGuiTreeNodeFlags_OpenOnArrow;
        }
        else
        {
            nodeFlags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
        }
        if (entity == selectedEntity_)
        {
            nodeFlags |= ImGuiTreeNodeFlags_Selected;
        }
        ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x * 0.7f);
        nodeOpen = ImGui::TreeNodeEx((void*)(intptr_t)entity, nodeFlags, "%s",
                                     entityName.c_str());
        ImGui::PopItemWidth();
        if (ImGui::IsItemClicked())
            selectedEntity_ = entity;
        const std::string entityPopupName = "Entity Popup " + std::to_string(entity);
        if (ImGui::IsItemClicked(1))
        {
            logDebug("Left Clicked on Entity: " + std::to_string(entity));

            ImGui::OpenPopup(entityPopupName.c_str());
        }

        if (ImGui::BeginPopup(entityPopupName.c_str()))
        {
            const std::string entityMenuName = "Entity Menu " + std::to_string(entity);
            enum class EntityMenuComboItem
            {
                ADD_EMPTY_ENTITY,
                DELETE_ENTITY,
                LENGTH
            };
            const char* entityMenuComboItemName[int(EntityMenuComboItem::LENGTH)] = {
                    "Add Empty Entity",
                    "Delete Entity"
            };

            const auto entityComboName = entityMenuName + " Combo";
            for (int i = 0; i < int(EntityMenuComboItem::LENGTH); i++)
            {
                const auto key = entityComboName + " " + entityMenuComboItemName[i];
                ImGui::PushID(key.c_str());
                if (ImGui::Selectable(entityMenuComboItemName[i]))
                {
                    const auto item = EntityMenuComboItem(i);
                    switch (item)
                    {
                        case EntityMenuComboItem::ADD_EMPTY_ENTITY:
                        {
                            createEntity = true;
                            break;
                        }
                        case EntityMenuComboItem::DELETE_ENTITY:
                        {
                            destroyEntity = true;
                            break;
                        }
                        default:
                            break;
                    }
                    ImGui::CloseCurrentPopup();
                }
                ImGui::PopID();
            }

            ImGui::EndPopup();
        }
        ImGuiDragDropFlags srcFlags = 0;
        srcFlags |= ImGuiDragDropFlags_SourceNoDisableHover;     // Keep the source displayed as hovered
        srcFlags |= ImGuiDragDropFlags_SourceNoHoldToOpenOthers; // Because our dragging is local, we disable the feature of opening foreign treenodes/tabs while dragging

        if (ImGui::BeginDragDropSource(srcFlags))
        {
            if (!(srcFlags & ImGuiDragDropFlags_SourceNoPreviewTooltip))
            {
                ImGui::Text("Moving Entity \"%s\"", entityName.c_str());
            }
            ImGui::SetDragDropPayload("DND_DEMO_NAME", &entity, sizeof(neko::Entity));
            ImGui::EndDragDropSource();
        }
        if (ImGui::BeginDragDropTarget())
        {
            ImGuiDragDropFlags targetFlags = 0;
            //target_flags |= ImGuiDragDropFlags_AcceptBeforeDelivery;    // Don't wait until the delivery (release mouse button on a target) to do something
            targetFlags |= ImGuiDragDropFlags_AcceptNoDrawDefaultRect; // Don't display the yellow rectangle
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DND_DEMO_NAME", targetFlags))
            {
                const neko::Entity moveFrom = *(const neko::Entity*) payload->Data;
                const neko::Entity moveTo = entity;
                entityManager_.SetEntityParent(moveFrom, moveTo);
            }
            ImGui::EndDragDropTarget();
        }
    }

    if (!leaf)
    {
        const auto& children = entityHierarchy_.GetChildren(entity);
        for (auto entityChild : children)
        {
            if (entityManager_.EntityExists(entityChild))
            {
                DrawEntityHierarchy(entityChild, nodeOpen, destroyEntity);
            }
        }
    }
    if (createEntity)
    {
        const auto newEntity = entityManager_.CreateEntity();
        entityManager_.SetEntityParent(newEntity, entity);
    }
    if (destroyEntity)
    {
        entityManager_.DestroyEntity(entity);
    }
    if (nodeOpen and !leaf)
    {
        ImGui::TreePop();
    }
}

void EntityViewer::RegisterDrawComponentImGui(DrawComponentImGuiInterface& drawComponentImGuiInterface)
{
    componentViewers_[drawComponentImGuiInterface.GetComponentType()] = &drawComponentImGuiInterface;
}

} // namespace neko::tool