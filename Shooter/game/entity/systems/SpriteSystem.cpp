#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>
#include <algorithm>

#include "RenderManager.h"

#include "Entity.h"

#include "SpriteSystem.h"

void SpriteSystem::SpriteBegin()
{
	auto& sprite_map = entity->GetComponentMap<Sprite>();
	for (auto& sprite : sprite_map)
	{
		void* raw = sprite.second;
		Sprite* ptr = static_cast<Sprite*>(raw);
		ptr->shader_program = shader_program;
		ptr->Init();
	}

	ReorderRender();
}

void SpriteSystem::SpriteUpdate()
{
	glm::mat4 view = RenderManager::GetInstance().GetViewMatrix();
	glm::mat4 projection = RenderManager::GetInstance().GetProjectionMatrix();

	shader_program->SetMatrix4Uniform("cameraMatrix", projection * view);

	RenderQueue();
}

void SpriteSystem::ReorderRender()
{
	sprites.clear();

	auto& sprite = entity->GetComponentMap<Sprite>();
	for (auto& var : sprite)
	{
		void* raw = var.second;
		Sprite* ptr = static_cast<Sprite*>(raw);
		sprites.push_back(ptr);
	}

	std::sort(sprites.begin(), sprites.end(), [](Sprite* a, Sprite* b)
		{
			return a->layer < b->layer;
		}
	);
}

void SpriteSystem::RenderQueue()
{
	for (auto& ptr : sprites)
	{
		ptr->transform->Update();
		ptr->Update();
	}
}
