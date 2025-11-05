//#include <GLFW/glfw3.h>
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

	const char* cursorPath = nullptr;
	int width, height, channels;
	GLFWimage image;

	cursorPath = "assets/ui/crosshair-default.png";

	unsigned char* pixels = stbi_load(cursorPath, &width, &height, &channels, 4);
	image.width = width;
	image.height = height;
	image.pixels = pixels;

	cursor_default = glfwCreateCursor(&image, width / 2, height / 2);

	stbi_image_free(pixels);

	cursorPath = "assets/ui/crosshair-reload.png";

	pixels = stbi_load(cursorPath, &width, &height, &channels, 4);
	image.width = width;
	image.height = height;
	image.pixels = pixels;

	cursor_reload = glfwCreateCursor(&image, width / 2, height / 2);
}

void GunSystem::Enter()
{
	glfwSetCursor(GameManager::GetInstance().GetWindow(), cursor_default);
	//entity = GameManager::GetInstance().GetLevel()->GetEntity();
	level = GameManager::GetInstance().GetLevel();

	level->GetEntity()->GetComponent<TextBlock>(3)->label = std::to_string(current_ammo) + "/5";
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
		glfwSetCursor(GameManager::GetInstance().GetWindow(), cursor_reload);
	}

	if (reload_time > 0) return;

	current_ammo = max_ammo;
	level->GetEntity()->GetComponent<TextBlock>(3)->label = std::to_string(current_ammo) + "/5";
	b_is_reload = false;
	glfwSetCursor(GameManager::GetInstance().GetWindow(), cursor_default);
}

bool GunSystem::IsCanFire()
{
	return current_ammo > 0 && !b_is_reload;
}

void GunSystem::Fire()
{
	if (!IsCanFire()) return;

	current_ammo--;
	level->GetEntity()->GetComponent<TextBlock>(3)->label = std::to_string(current_ammo) + "/5";
	int temp = ray_line->ShootRayLine();

	if (!IsCanFire())
	{
		level->GetEntity()->GetComponent<TextBlock>(3)->label = "reload..";
		b_is_reload = true;
		reload_time = 5;
		glfwSetCursor(GameManager::GetInstance().GetWindow(), cursor_reload);
	}

	if (temp == 0) return;
	std::cout << temp << std::endl;

	Entity* entity = level->GetEntity();

	entity->GetComponent<Sprite>(temp)->layer = -1;
	level->GetSpriteSystem()->ReorderRender();

	int get_score = std::stoi(entity->GetComponent<Transform>(temp)->tag);
	int score = GameManager::GetInstance().GetScore() + get_score;
	GameManager::GetInstance().SetScore(score);
	level->GetEntity()->GetComponent<TextBlock>(2)->label = "score: " + std::to_string(score);

	int kill_count = GameManager::GetInstance().GetKillCount();
	kill_count++;
	GameManager::GetInstance().SetKillCount(kill_count);
	level->GetEntity()->GetComponent<TextBlock>(6)->label = "kill: " + std::to_string(kill_count);
}
