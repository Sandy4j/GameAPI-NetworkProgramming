#include <iostream>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_opengl3_loader.h>

#include "GameManager.h"

#include "UIManager.h"

void UIManager::iInit()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	//io.Fonts->AddFontFromFileTTF("assets/font/Pixeled.ttf", 28.0f);
	ImGui_ImplGlfw_InitForOpenGL(GameManager::GetInstance().GetWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void UIManager::iUpdate()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	GameManager::GetInstance().GetGameState().UpdateRenderUI();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UIManager::iShutdown()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}
