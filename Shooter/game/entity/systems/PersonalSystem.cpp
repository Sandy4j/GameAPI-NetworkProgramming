#include <iostream>

#include "Entity.h"
#include "Personal.h"
#include "Level.h"

#include "GameManager.h"

#include "PersonalSystem.h"

void PersonalSystem::PersonalStart()
{
	entity = GameManager::GetInstance().GetLevel()->GetEntity();

	auto& sprite_map = entity->GetComponentMap<Personal>();

	if (sprite_map.empty()) return;

	for (auto& sprite : sprite_map)
	{
		void* raw = sprite.second;
		Personal* ptr = static_cast<Personal*>(raw);
		ptr->IPersonalStart();
	}
}

void PersonalSystem::PersonalUpdate()
{
	auto& sprite_map = entity->GetComponentMap<Personal>();

	if (sprite_map.empty()) return;

	for (auto& sprite : sprite_map)
	{
		void* raw = sprite.second;
		Personal* ptr = static_cast<Personal*>(raw);
		ptr->IPersonalUpdate();
	}
}
