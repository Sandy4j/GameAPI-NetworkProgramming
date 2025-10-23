#include <iostream>
#include <functional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "GameManager.h"
#include "InputManager.h"

#include "Level.h"
#include "Entity.h"
#include "Transform.h"
#include "Button.h"

#include "MainMenuState.h"

MainMenuState::MainMenuState()
{
	level = new Level();
}

void MainMenuState::iEnter()
{
	ImGuiIO& io = ImGui::GetIO();
	io.ClearInputKeys();

	std::cout << "UPDATE MAIN MENU" << std::endl;
	glfwSetCursor(GameManager::GetInstance().GetWindow(), nullptr);
	level->LoadLevel("mainmenu_level.json");
}

void MainMenuState::iUpdateLogic()
{
	int id = level->GetButtonID();

	if (id == 1)
		GameManager::GetInstance().GetGameState().ChangeState(EGameState::eGameplay);

	if (id == 2)
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

}
