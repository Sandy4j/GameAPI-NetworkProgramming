#include <iostream>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "GameManager.h"
#include "InputManager.h"
#include "../../Integration/GameAPIManager.h"

#include "Level.h"

#include "PauseState.h"

PauseState::PauseState()
{
	InputManager::GetInstance().BindKeyFunction(std::bind(&PauseState::UnPause, this), GLFW_KEY_ESCAPE, EInputEventType::ePress, EGameState::ePauseMenu);

	level = new Level();
}

void PauseState::UnPause()
{
	GameState& state = GameManager::GetInstance().GetGameState();
	state.ChangeState(state.GetEnumState(ETrasition::ePrevious));
}

void PauseState::iEnter()
{
	ImGuiIO& io = ImGui::GetIO();
	io.ClearInputKeys();

	GameManager::GetInstance().SetLevel(level);

	std::cout << "Pausee" << std::endl;
	glfwSetCursor(GameManager::GetInstance().GetWindow(), nullptr);
	level->LoadLevel("pause_level.json");
}

void PauseState::iUpdateLogic()
{
	int id = level->GetButtonID();

	if (id == 1)
		GameManager::GetInstance().GetGameState().ChangeState(GameManager::GetInstance().GetGameState().GetEnumState(ETrasition::ePrevious));

	if (id == 2)
		GameManager::GetInstance().GetGameState().ChangeState(EGameState::eMainMenu);

	if (id == 3)
	{
		std::cout << "[Pause] Saving game and exiting..." << std::endl;
	bool saved = GameAPIManager::GetInstance().SaveCurrentGameSession();
		
		if (saved)
		{
			std::cout << "[Pause] Game saved successfully!" << std::endl;
		}
		else
		{
			std::cerr << "[Pause] Failed to save game: " << GameAPIManager::GetInstance().GetLastError() << std::endl;
		}
		
		GameManager::GetInstance().GetGameState().ChangeState(EGameState::eMainMenu);
	}
}

void PauseState::iUpdateRenderObject()
{
	level->UpdateRenderObject();
}

void PauseState::iUpdateRenderUI()
{
	level->UpdateRenderUI();
}

void PauseState::iExit()
{

}
