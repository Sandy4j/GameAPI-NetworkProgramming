#include <iostream>
#include <functional>

#include "Entity.h"
#include "Transform.h"
#include "SpriteSystem.h"

#include "Level.h"

#include "PlayerController.h"

#include "GameManager.h"
#include "InputManager.h"

#include "GameplayState.h"

GameplayState::GameplayState()
{
	level = new Level();
	player_controller = new PlayerController(*level->GetEntity());
}

void GameplayState::iEnter()
{
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

	level->LoadLevel("gameplay_level.json");

	level->GetEntity()->GetComponent<TextBlock>(1)->label = "username: " + GameManager::GetInstance().GetUsername();
	level->GetEntity()->GetComponent<TextBlock>(2)->label = "score: " + std::to_string(GameManager::GetInstance().GetScore());
}

void GameplayState::iUpdateLogic()
{
	
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
