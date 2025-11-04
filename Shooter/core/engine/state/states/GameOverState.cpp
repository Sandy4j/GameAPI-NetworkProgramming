#include <iostream>
#include <GLFW/glfw3.h>

#include "GameManager.h"
#include "InputManager.h"
#include "../../Integration/GameAPIManager.h"

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

	GameManager::GetInstance().SetLevel(level);

	std::cout << "ENTER GAMEOVER" << std::endl;
	glfwSetCursor(GameManager::GetInstance().GetWindow(), nullptr);
	level->LoadLevel("gameover_level.json");

	std::cout << "[GameOver] Submitting game score to API..." << std::endl;
	bool submitSuccess = GameAPIManager::GetInstance().SubmitCurrentGameScore();

	if (submitSuccess)
	{
		std::cout << "[GameOver] Score submitted successfully." << std::endl;
	}
	else
	{
		std::string error = GameAPIManager::GetInstance().GetLastError();
		std::cerr << "[GameOver] Failed to submit score: " << error << std::endl;
	}
}

void GameOverState::iUpdateLogic()
{
	int id = level->GetButtonID();

	if (id == 2)
		GameManager::GetInstance().GetGameState().ChangeState(EGameState::eGameplay);

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
