/*
 MIT License

 Copyright (c) 2017 SAE Institute Switzerland AG

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

#include <engine/transform.h>
#include "engine/globals.h"
#include "mathematics/transform.h"
#include "imgui.h"
#include "graphics/graphics.h"

#ifdef EASY_PROFILE_USE
#include "easy/profiler.h"
#endif
namespace neko
{

Index Scale2dManager::AddComponent(Entity entity)
{
	ResizeIfNecessary(components_, entity, Vec2f::one);
	return ComponentManager::AddComponent(entity);
}

Index Scale3dManager::AddComponent(Entity entity)
{
	ResizeIfNecessary(components_, entity, Vec3f::one);
	return ComponentManager::AddComponent(entity);
}

Transform3dManager::Transform3dManager(EntityManager& entityManager) :
	DoubleBufferComponentManager(entityManager),
	position3DManager_(entityManager),
	scale3DManager_(entityManager),
	rotation3DManager_(entityManager),
	dirtyManager_(entityManager)
{
	entityManager_.RegisterOnChangeParent(this);
	dirtyManager_.RegisterComponentManager(this);
}

void Transform3dManager::Init()
{
	RendererLocator::get().RegisterSyncBuffersFunction(this);
}

void Transform3dManager::UpdateTransform(Entity entity)
{
    Mat4f transform = Mat4f::Identity;
	transform = Transform3d::Rotate(transform, rotation3DManager_.GetComponent(entity));
	transform = Transform3d::Scale(transform, scale3DManager_.GetComponent(entity));
    transform = Transform3d::Translate(transform, position3DManager_.GetComponent(entity));

	const auto parent = entityManager_.GetEntityParent(entity);
	if (parent != INVALID_ENTITY)
	{
		transform =  GetComponent(parent) * transform;
	}
	
    SetComponent(entity, transform);
}

void Transform3dManager::SetPosition(Entity entity, Vec3f position)
{
	position3DManager_.SetComponent(entity, position);
	dirtyManager_.SetDirty(entity);
}

void Transform3dManager::SetScale(Entity entity, Vec3f scale)
{
	scale3DManager_.SetComponent(entity, scale);
	dirtyManager_.SetDirty(entity);
}

void Transform3dManager::SetRotation(Entity entity, EulerAngles angles)
{
	rotation3DManager_.SetComponent(entity, angles);
	dirtyManager_.SetDirty(entity);
}

Vec3f Transform3dManager::GetPosition(Entity entity) const
{
	return position3DManager_.GetComponent(entity);
}

Vec3f Transform3dManager::GetScale(Entity entity) const
{
	return scale3DManager_.GetComponent(entity);
}

EulerAngles Transform3dManager::GetAngles(Entity entity) const
{
	return rotation3DManager_.GetComponent(entity);
}

void Transform3dManager::OnChangeParent(Entity entity, Entity newParent, Entity oldParent)
{
	dirtyManager_.SetDirty(entity);
}

void Transform3dManager::UpdateDirtyComponent(Entity entity)
{
	UpdateTransform(entity);
}

void Transform3dManager::Update()
{
#ifdef EASY_PROFILE_USE
	EASY_BLOCK("Update Transform");
#endif
	dirtyManager_.UpdateDirtyEntities();
}

Index Transform3dManager::AddComponent(Entity entity)
{
	position3DManager_.AddComponent(entity);
	scale3DManager_.AddComponent(entity);
	rotation3DManager_.AddComponent(entity);
	return DoubleBufferComponentManager::AddComponent(entity);
}

Transform2dManager::Transform2dManager(EntityManager& entityManager) :
    DoubleBufferComponentManager(entityManager),
    position2DManager_(entityManager),
    scale2DManager_(entityManager),
    rotation2DManager_(entityManager),
    dirtyManager_(entityManager)
{
    entityManager_.RegisterOnChangeParent(this);
    dirtyManager_.RegisterComponentManager(this);
}

void Transform2dManager::Init()
{
    RendererLocator::get().RegisterSyncBuffersFunction(this);
}

Vec2f Transform2dManager::GetPosition(Entity entity) const
{
    return position2DManager_.GetComponent(entity);
}

void Transform2dManager::SetPosition(Entity entity, Vec2f position)
{
    position2DManager_.SetComponent(entity, position);
}

Vec2f Transform2dManager::GetScale(Entity entity) const
{
    return scale2DManager_.GetComponent(entity);
}

void Transform2dManager::SetScale(Entity entity, Vec2f scale)
{
    scale2DManager_.SetComponent(entity, scale);
}

float Transform2dManager::GetRotation(Entity entity)
{
    return rotation2DManager_.GetComponent(entity);
}

void Transform2dManager::SetRotation(Entity entity, float angle)
{
    rotation2DManager_.SetComponent(entity, angle);
}

void Transform2dManager::OnChangeParent(Entity entity, Entity newParent, Entity oldParent)
{
    dirtyManager_.SetDirty(entity);
}

void Transform2dManager::UpdateTransform(Entity entity)
{
    Mat3f transform = Mat3f::Identity;
    transform = Transform2d::Rotate(transform, rotation2DManager_.GetComponent(entity));
    transform = Transform2d::Scale(transform, scale2DManager_.GetComponent(entity));
    transform = Transform2d::Translate(transform, position2DManager_.GetComponent(entity));

    const auto parent = entityManager_.GetEntityParent(entity);
    if (parent != INVALID_ENTITY)
    {
        transform =  GetComponent(parent) * transform;
    }

    SetComponent(entity, transform);
}

void Transform2dManager::Update()
{
    dirtyManager_.UpdateDirtyEntities();
}

Index Transform2dManager::AddComponent(Entity entity)
{
    position2DManager_.AddComponent(entity);
    scale2DManager_.AddComponent(entity);
    rotation2DManager_.AddComponent(entity);
    return DoubleBufferComponentManager::AddComponent(entity);
}

void Transform2dManager::UpdateDirtyComponent(Entity entity)
{
    UpdateTransform(entity);
}
}
