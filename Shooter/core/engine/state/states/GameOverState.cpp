#include <iostream>
#include <GLFW/glfw3.h>

#include "GameManager.h"
#include "InputManager.h"

#include "Level.h"
#include "Entity.h"
#include "TextBlock.h"

#include "GameOverState.h"

GameOverState::GameOverState()
{
	level = new Level();
}

void GameOverState::iEnter()
{
	ImGuiIO& io = ImGui::GetIO();
	io.ClearInputKeys();

	std::cout << "ENTER GAMEOVER" << std::endl;
	glfwSetCursor(GameManager::GetInstance().GetWindow(), nullptr);
	level->LoadLevel("gameover_level.json");

	level->GetEntity()->GetComponent<TextBlock>(1)->label = GameManager::GetInstance().GetResultGame();
}

void GameOverState::iUpdateLogic()
{
	int id = level->GetButtonID();

	if (id == 2)
		GameManager::GetInstance().GetGameState().ChangeState(EGameState::eGameplayPlayerOne);

	if (id == 3)
		GameManager::GetInstance().GetGameState().ChangeState(EGameState::eMainMenu);
}

void GameOverState::iUpdateRenderObject()
{
	level->UpdateRenderObject();
}

void GameOverState::iUpdateRenderUI()
{
	level->UpdateRenderUI();
}

void GameOverState::iExit()
{
	
}
