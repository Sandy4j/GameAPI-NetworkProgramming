#include <iostream>
#include <functional>

#include "Entity.h"
#include "Transform.h"
#include "SpriteSystem.h"
#include "Personal.h"

#include "Level.h"

#include "PlayerController.h"

#include "GameManager.h"
#include "InputManager.h"

#include "GameplayState.h"

GameplayState::GameplayState()
{
	level = new Level();
	player_controller = new PlayerController();

	const char* cursorPath = nullptr;
	int width, height, channels;
	GLFWimage image;

	cursorPath = "assets/ui/crosshair.png";

	unsigned char* pixels = stbi_load(cursorPath, &width, &height, &channels, 4);
	image.width = width;
	image.height = height;
	image.pixels = pixels;

	cursor = glfwCreateCursor(&image, 0, 0);
}

void GameplayState::iEnter()
{
	//glfwSetCursor(GameManager::GetInstance().GetWindow(), cursor);

	if (GameManager::GetInstance().GetGameState().GetEnumState(ETrasition::ePrevious) != EGameState::eMainMenu && 
		GameManager::GetInstance().GetGameState().GetEnumState(ETrasition::ePrevious) != EGameState::eGameOver) return;

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

	GameManager::GetInstance().SetLevel(level);

	level->LoadLevel("gameplay_level.json");

	level->GetEntity()->GetComponent<TextBlock>(1)->label = "username: " + GameManager::GetInstance().GetUsername();
	level->GetEntity()->GetComponent<TextBlock>(2)->label = "score: " + std::to_string(GameManager::GetInstance().GetScore());

	player_controller->Enter();
}

void GameplayState::iUpdateLogic()
{
	level->UpdatePersonalLogic();
	player_controller->UpdatePlayerController();
}

void GameplayState::iUpdateRenderObject()
{
	level->UpdateRenderObject();
}

void GameplayState::iUpdateRenderUI()
{
	level->UpdateRenderUI();
}

void GameplayState::iExit()
{
	
}
