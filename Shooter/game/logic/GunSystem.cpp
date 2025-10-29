#include <iostream>
#include <string>

#include "Entity.h"
#include "Sprite.h"
#include "TextBlock.h"
#include "RayLine.h"

#include "GameManager.h"
#include "InputManager.h"
#include "TimeManager.h"

#include "Level.h"
#include "SpriteSystem.h"

#include "GunSystem.h"

GunSystem::GunSystem()
{
	ray_line = new RayLine();

	InputManager* input = &InputManager::GetInstance();
	input->BindMouseFunction(std::bind(&GunSystem::Fire, this), GLFW_MOUSE_BUTTON_1, EInputEventType::ePress, EGameState::eGameplay);
	input->BindKeyFunction(std::bind(&GunSystem::Reload, this), GLFW_KEY_R, EInputEventType::ePress, EGameState::eGameplay);

	max_ammo = 5;
	current_ammo = max_ammo;
	b_is_reload = false;
}

void GunSystem::Enter()
{
	//entity = GameManager::GetInstance().GetLevel()->GetEntity();
	level = GameManager::GetInstance().GetLevel();

	level->GetEntity()->GetComponent<TextBlock>(3)->label = "ammo: " + std::to_string(current_ammo);
}

void GunSystem::UpdateGunSystem()
{
	#pragma region ReloadTime

	if (!b_is_reload) return;

	reload_time -= TimeManager::GetInstance().GetDeltaTime();

	if (reload_time <= 0 && b_is_reload) Reload();
	#pragma endregion
}

void GunSystem::Reload()
{
	if (current_ammo != max_ammo && !b_is_reload)
	{
		level->GetEntity()->GetComponent<TextBlock>(3)->label = "reload..";
		b_is_reload = true;
		reload_time = 5;
	}

	if (reload_time > 0) return;

	current_ammo = max_ammo;
	level->GetEntity()->GetComponent<TextBlock>(3)->label = "ammo: " + std::to_string(current_ammo);
	b_is_reload = false;
}

bool GunSystem::IsCanFire()
{
	return current_ammo > 0 && !b_is_reload;
}

void GunSystem::Fire()
{
	if (!IsCanFire()) return;

	current_ammo--;
	level->GetEntity()->GetComponent<TextBlock>(3)->label = "ammo: " + std::to_string(current_ammo);
	int temp = ray_line->ShootRayLine();

	if (temp == 0) return;
	std::cout << temp << std::endl;

	level->GetEntity()->GetComponent<BoundingBox>(temp)->b_is_trigger = true;
	level->GetEntity()->GetComponent<Sprite>(temp)->layer = -1;
	level->GetSpriteSystem()->ReorderRender();

	int score = GameManager::GetInstance().GetScore() + 1;
	GameManager::GetInstance().SetScore(score);
	level->GetEntity()->GetComponent<TextBlock>(2)->label = "score: " + std::to_string(score);
}
