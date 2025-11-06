#include <iostream>
#include <functional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "GameManager.h"
#include "InputManager.h"
#include "../../Integration/GameAPIManager.h"

#include "Level.h"
#include "Entity.h"
#include "Transform.h"
#include "Button.h"

#include "MainMenuState.h"

MainMenuState::MainMenuState()
{
	level = new Level("mainmenu_level.json");
}

void MainMenuState::iEnter()
{
	ImGuiIO& io = ImGui::GetIO();
	io.ClearInputKeys();

	GameManager::GetInstance().SetLevel(level);

	glfwSetCursor(GameManager::GetInstance().GetWindow(), nullptr);
	level->LoadLevel("mainmenu_level.json");

	level->GetEntity()->GetComponent<TextBlock>(5)->label = "username: " + GameManager::GetInstance().GetUsername();
	level->GetEntity()->GetComponent<TextBlock>(6)->label = "score: " + std::to_string(GameManager::GetInstance().GetScore());

	std::string username = GameManager::GetInstance().GetUsername();
	Button* continueButton = level->GetEntity()->GetComponent<Button>(3);
	
	if (continueButton && continueButton->transform)
	{
		if (!username.empty() && GameAPIManager::GetInstance().HasSavedGame(username))
		{
			continueButton->transform->b_is_active = true;
		}
		else
		{
			continueButton->transform->b_is_active = false;
		}
	}
}

void MainMenuState::iUpdateLogic()
{
	int id = level->GetButtonID();

	if (id == 1)
	{
		std::cout << "[MainMenu] Starting new game" << std::endl;
		
		std::string username = GameManager::GetInstance().GetUsername();
		if (!username.empty())
		{
			GameAPIManager::GetInstance().ClearSavedGame(username);
		}
		
		GameManager::GetInstance().SetScore(0);
		GameManager::GetInstance().SetWave(0);
		
		GameManager::GetInstance().GetGameState().ChangeState(EGameState::eGameplay);
	}

	if (id == 2)
	{
		std::cout << "[MainMenu] Opening leaderboard" << std::endl;
		GameManager::GetInstance().GetGameState().ChangeState(EGameState::eLeaderboard);
	}

	if (id == 3)
	{
		std::cout << "[MainMenu] Loading saved game..." << std::endl;
		
		int savedScore, savedWave, savedKills;
		if (GameAPIManager::GetInstance().LoadGameSession(savedScore, savedWave, savedKills))
		{
			std::cout << "[MainMenu] Restoring game state: Score=" << savedScore 
			        << ", Wave=" << savedWave << std::endl;
			
			GameManager::GetInstance().SetScore(savedScore);
			GameManager::GetInstance().SetWave(savedWave);
			GameManager::GetInstance().GetGameState().ChangeState(EGameState::eGameplay);
		}
		else
		{
			std::cerr << "[MainMenu] Failed to load saved game" << std::endl;
		}
	}

	if (id == 4)
	{
		GameManager::GetInstance().SetIsExit(true);
		glfwSetWindowShouldClose(GameManager::GetInstance().GetWindow(), GLFW_TRUE);
	}
}

void MainMenuState::iUpdateRenderObject()
{
	level->UpdateRenderObject();
}

void MainMenuState::iUpdateRenderUI()
{
	level->UpdateRenderUI();
}

void MainMenuState::iExit()
{
	level->UnloadLevel();
}
