#include <entity_viewer.h>

#include <imgui.h>
#include <engine/log.h>
#include <engine/component.h>
#include <cmath>

namespace neko::tool {
EntityViewer::EntityViewer(EntityManager& entityManager, EntityHierarchy& entityHierarchy) :
        entityHierarchy_(entityHierarchy),
        entityManager_(entityManager)
{
}

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
    std::cout << "nb = " << log2(static_cast<double>(ComponentType::OTHER_TYPE)) << "\n";
    std::cout << "Entity mask = " << entityManager_.GetMask(selectedEntity_) << "\n";
    for(uint32_t i = 1; i < log2(static_cast<double>(ComponentType::OTHER_TYPE)); i++){
        if(entityManager_.HasComponent(selectedEntity_, 1u << i)){
            std::cout << "Has component " << i << "\n";
        }
    }

    if(ImGui::Button("Add Component")){
        entityManager_.AddComponentType(selectedEntity_, EntityMask(ComponentType::POSITION2D));
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

}