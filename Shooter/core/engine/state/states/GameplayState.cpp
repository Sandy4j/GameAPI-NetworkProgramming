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
}

void GameplayState::iEnter()
{
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
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
