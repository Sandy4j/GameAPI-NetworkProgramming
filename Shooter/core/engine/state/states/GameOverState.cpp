#include <iostream>
#include <string>
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
	level = new Level("gameover_level.json");
}

void GameOverState::iEnter()
{
	ImGuiIO& io = ImGui::GetIO();
	io.ClearInputKeys();

	GameManager::GetInstance().SetLevel(level);

	glfwSetCursor(GameManager::GetInstance().GetWindow(), nullptr);
	level->LoadLevel("gameover_level.json");

	std::cout << "[GameOver] Submitting game score to API..." << std::endl;
	bool submitSuccess = GameAPIManager::GetInstance().SubmitCurrentGameScore();

	if (submitSuccess)
	{
		std::cout << "[GameOver] Score submitted successfully." << std::endl;
		std::string username = GameManager::GetInstance().GetUsername();
		if (!username.empty())
		{
			GameAPIManager::GetInstance().ClearSavedGame(username);
			std::cout << "[GameOver] Saved game cleared after final score submission" << std::endl;
		}
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
	level->UnloadLevel();
}
