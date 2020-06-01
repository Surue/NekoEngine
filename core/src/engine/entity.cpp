/*
 MIT License

 Copyright (c) 2019 SAE Institute Switzerland AG

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */
#include <engine/entity.h>
#include "engine/globals.h"
#include <algorithm>
#include <utilities/vector_utility.h>
#include <engine/component.h>
#include <sstream>
#include <engine/log.h>

#include "imgui.h"

namespace neko
{

EntityManager::EntityManager()
{
    entityMaskArray_.resize(INIT_ENTITY_NMB);
	entityHashArray_.resize(INIT_ENTITY_NMB);
    parentEntities_.resize(INIT_ENTITY_NMB, INVALID_ENTITY);
}

EntityMask EntityManager::GetMask(Entity entity)
{
    return entityMaskArray_[entity];
}

Entity EntityManager::CreateEntity(Entity entity)
{
    if(entity == INVALID_ENTITY)
    {
        const auto entityMaskIt = std::find_if(entityMaskArray_.begin(), entityMaskArray_.end(),
                                               [](EntityMask entityMask)
                                               {
                                                   return entityMask == INVALID_ENTITY_MASK;
                                               });
        if (entityMaskIt == entityMaskArray_.end())
        {
            const auto newEntity = entityMaskArray_.size();
            ResizeIfNecessary(entityMaskArray_, newEntity, INVALID_ENTITY_MASK);
            ResizeIfNecessary(parentEntities_, entity, INVALID_ENTITY);
			ResizeIfNecessary(entityHashArray_, newEntity, INVALID_ENTITY_HASH);
        	AddComponentType(Entity(newEntity), static_cast<EntityMask>(ComponentType::EMPTY));
            return Entity(newEntity);
        }
        else
        {
            const auto newEntity = entityMaskIt - entityMaskArray_.begin();
            AddComponentType(Entity(newEntity), static_cast<EntityMask>(ComponentType::EMPTY));
            return Entity(newEntity);
        }
    }
    else
    {
        ResizeIfNecessary(entityMaskArray_, entity, INVALID_ENTITY_MASK);
        ResizeIfNecessary(parentEntities_, entity, INVALID_ENTITY);
		ResizeIfNecessary(entityHashArray_, entity, INVALID_ENTITY_HASH);
    	if(!EntityExists(entity))
        {
            AddComponentType(entity, static_cast<EntityMask>(ComponentType::EMPTY));
            return entity;
        }
        return CreateEntity(INVALID_ENTITY);
    }
}

void EntityManager::DestroyEntity(Entity entity)
{
    entityMaskArray_[entity] = INVALID_ENTITY_MASK;
	entityHashArray_[entity] = INVALID_ENTITY_HASH;

	onDestroyEntity.Execute(entity);
}

bool EntityManager::HasComponent(Entity entity, EntityMask componentType) const
{
	if (entity >= entityMaskArray_.size())
    {
	    std::ostringstream oss;
	    oss << "[Error] Accessing entity: "<<entity<<" while entity mask array is of size: "<<entityMaskArray_.size();
	    logDebug(oss.str());
	    return false;
    }
    return (entityMaskArray_[entity] & EntityMask(componentType)) == EntityMask(componentType);
}

void EntityManager::AddComponentType(Entity entity, EntityMask componentType)
{
    entityMaskArray_[entity] |= EntityMask(componentType);
}

void EntityManager::RemoveComponentType(Entity entity, EntityMask componentType)
{
    entityMaskArray_[entity] &= ~EntityMask(componentType);
}

void EntityManager::SetEntityName(Entity entity, const std::string& entityName)
{
	const auto entityHash = HashEntityName(entityName);
	entityHashArray_[entity] = entityHash;
}

Entity EntityManager::FindEntityByName(const std::string& entityName)
{
	const auto entityHash = HashEntityName(entityName);
	return FindEntityByHash(entityHash);
}

EntityHash EntityManager::HashEntityName(const std::string& entityName)
{
	xxh::hash_state_t<64> hash_stream(0);
	hash_stream.update(entityName);
	const EntityHash entityHash = hash_stream.digest();
	return entityHash;
}

DirtyManager::DirtyManager(EntityManager& entityManager) : entityManager_(entityManager)
{
}

void DirtyManager::SetDirty(Entity entity)
{
    if (std::find(dirtyEntities_.cbegin(), dirtyEntities_.cend(), entity) == dirtyEntities_.cend())
    {
    	dirtyEntities_.push_back(entity);
    }
}

void DirtyManager::UpdateDirtyEntities()
{
    //Fill the dirty entities with all the children in O(n)
    for (Entity entity = 0; entity < entityManager_.GetEntitiesSize(); entity++)
    {
    	if(!entityManager_.EntityExists(entity))
            continue;
        auto parent = entityManager_.GetEntityParent(entity);
        while (parent != INVALID_ENTITY)
        {
            if (std::find(dirtyEntities_.cbegin(), dirtyEntities_.cend(), parent) != dirtyEntities_.end())
            {
                SetDirty(entity);
                break;
            }
            parent = entityManager_.GetEntityParent(parent);
        }
    }
    for (auto entity : dirtyEntities_)
    {
        updateDirtyEntity.Execute(entity);
    }
    dirtyEntities_.clear();
}

EntityHierarchy::EntityHierarchy(EntityManager& entityManager) : entityManager_(entityManager)
{
    entityManager_.RegisterOnChangeParent(this);
}

void EntityHierarchy::OnChangeParent(Entity entity, Entity newParent, Entity oldParent)
{
	//Remove entity from previous parent
    if(oldParent != INVALID_ENTITY)
    {
        auto it = entityHierarchyMap_.find(oldParent);
    	if(it != entityHierarchyMap_.end())
    	{
            auto& hierarchy = it->second;
            const auto entityIt = std::find(hierarchy.begin(), hierarchy.end(), entity);
    		if(entityIt != hierarchy.end())
    		{
                hierarchy.erase(entityIt);
    		}
    	}
    }
	//Add entity to new parent
	if(newParent != INVALID_ENTITY)
	{
        auto it = entityHierarchyMap_.find(newParent);
		if(it != entityHierarchyMap_.end())
		{
            auto& hierarchy = it->second;
            hierarchy.push_back(entity);
		}
        else
        {
            entityHierarchyMap_[newParent] = { entity };
        }
	}
}

const std::vector<Entity>& EntityHierarchy::GetChildren(Entity entity)
{
    return entityHierarchyMap_[entity];
}

bool EntityHierarchy::HasChildren(Entity entity)
{
	const auto it = entityHierarchyMap_.find(entity);
	if(it != entityHierarchyMap_.end())
	{
        return !(it->second.empty());
	}
    return false;
}

size_t EntityManager::GetEntitiesNmb(EntityMask filterComponents)
{
    return std::count_if(entityMaskArray_.begin(), entityMaskArray_.end(),[&filterComponents](EntityMask entityMask){
        return entityMask != INVALID_ENTITY_MASK && (entityMask & EntityMask(filterComponents)) == EntityMask(filterComponents);
    });
}

size_t EntityManager::GetEntitiesSize() const
{
	return entityMaskArray_.size();
}

std::vector<Entity> EntityManager::FilterEntities(EntityMask filterComponents) const
{
	std::vector<Entity> entities;
	entities.reserve(entityMaskArray_.size());
	for(Entity i = 0; i < entityMaskArray_.size();i++)
	{
		if(HasComponent(i, filterComponents))
		{
			entities.push_back(i);
		}
	}
	return entities;
}

bool EntityManager::EntityExists(Entity entity)
{
    return entityMaskArray_[entity] != INVALID_ENTITY_MASK;
}

Entity EntityManager::GetLastEntity()
{
    const auto it = std::find_if(
            entityMaskArray_.rbegin(),
            entityMaskArray_.rend(),
                    [](EntityMask entityMask){
       return entityMask != INVALID_ENTITY_MASK;
    });

    return Entity(std::distance(entityMaskArray_.begin(), it.base()) - 1);
}

bool EntityManager::IsPrefab(Entity entity) const
{
    return HasComponent(entity, static_cast<EntityMask>(ComponentType::PREFAB));
}

EntityHash EntityManager::GetEntityNameHash(Entity entity)
{
    return entityHashArray_[entity];
}

Entity EntityManager::FindEntityByHash(EntityHash entityHash)
{
	const auto index = std::find(entityHashArray_.begin(), entityHashArray_.end(), entityHash);
	if (index != entityHashArray_.end())
	{
		return index - entityHashArray_.begin();
	}
	return INVALID_ENTITY;
}

void EntityManager::SetEntityNameHash(Entity entity, EntityHash entityHash)
{
    entityHashArray_[entity] = entityHash;
}

void EntityManager::RegisterOnChangeParent(OnChangeParentInterface* onChangeInterface)
{
    onChangeParent.RegisterCallback([onChangeInterface](Entity entity, Entity newParent, Entity oldParent)
    {
        onChangeInterface->OnChangeParent(entity, newParent, oldParent);
    });
}

Entity EntityManager::GetEntityParent(Entity entity)
{
    return parentEntities_[entity];
}

bool EntityManager::SetEntityParent(Entity child, Entity parent)
{
	const auto oldParent = GetEntityParent(child);
    auto p = GetEntityParent(parent);
    while (p != INVALID_ENTITY)
    {
	    if(p == child)
	    {
            logDebug("[Warning] Child entity: " + std::to_string(child) + " cannot have parent entity: " + std::to_string(parent));
            return false;
	    }
        p = GetEntityParent(p);
    }
    parentEntities_[child] = parent;
    onChangeParent.Execute(child, parent, oldParent);
    return true;
}
}
