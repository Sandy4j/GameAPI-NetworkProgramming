#include <iostream>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>

#include "GameManager.h"
#include "InputManager.h"
#include "../../Integration/GameAPIManager.h"

#include "Level.h"
#include "Entity.h"
#include "TextBlock.h"
#include "UiTransform.h"

#include "LeaderboardState.h"

LeaderboardState::LeaderboardState()
	: isLoading(true)
{
	level = new Level();
}

void LeaderboardState::iEnter()
{
	ImGuiIO& io = ImGui::GetIO();
	io.ClearInputKeys();

	GameManager::GetInstance().SetLevel(level);

	std::cout << "[Leaderboard] Entering leaderboard state" << std::endl;
	glfwSetCursor(GameManager::GetInstance().GetWindow(), nullptr);
	
	// Load level untuk background dan UI
	level->LoadLevel("leaderboard_level.json");
	
	// Load leaderboard data dari REST API
	LoadLeaderboard();
}

void LeaderboardState::LoadLeaderboard()
{
	std::cout << "[Leaderboard] Loading leaderboard from API..." << std::endl;
	isLoading = true;
	errorMessage.clear();
	
	// Ambil top 10 dari REST API
	leaderboardData = GameAPIManager::GetInstance().GetLeaderboard(10);
	
	if (leaderboardData.empty())
	{
		errorMessage = GameAPIManager::GetInstance().GetLastError();
		
		// Jika tidak ada error message, berarti database kosong
		if (errorMessage.empty())
		{
			errorMessage = "No scores yet. Be the first to play!";
			std::cout << "[Leaderboard] Database is empty - no scores found" << std::endl;
		}
		else
		{
			std::cerr << "[Leaderboard] Error: " << errorMessage << std::endl;
		}
	}
	else
	{
		std::cout << "[Leaderboard] Successfully loaded " << leaderboardData.size() << " entries" << std::endl;
		
		// Debug: Print first entry
		if (!leaderboardData.empty())
		{
			std::cout << "[Leaderboard] Top entry: #" << leaderboardData[0].rank 
			   << " " << leaderboardData[0].username 
			          << " - " << leaderboardData[0].score << " pts" << std::endl;
		}
	}
	
	isLoading = false;
}

void LeaderboardState::iUpdateLogic()
{
	int id = level->GetButtonID();

	// Button "Back" untuk kembali ke main menu
	if (id == 1)
	{
		std::cout << "[Leaderboard] Returning to main menu" << std::endl;
		GameManager::GetInstance().GetGameState().ChangeState(EGameState::eMainMenu);
	}
	
	// Button "Refresh" untuk reload leaderboard
	if (id == 2)
	{
		std::cout << "[Leaderboard] Refreshing leaderboard..." << std::endl;
		LoadLeaderboard();
	}
}

void LeaderboardState::iUpdateRenderObject()
{
	level->UpdateRenderObject();
}

void LeaderboardState::iUpdateRenderUI()
{
	level->UpdateRenderUI();
	
	// Render leaderboard menggunakan ImGui
	ImGui::SetNextWindowPos(ImVec2(100, 100), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(600, 500), ImGuiCond_FirstUseEver);
	
	ImGui::Begin("LEADERBOARD", nullptr, ImGuiWindowFlags_NoCollapse);
	
	if (isLoading)
	{
		ImGui::Text("Loading leaderboard...");
	}
	else if (!errorMessage.empty())
	{
		ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.3f, 1.0f), "%s", errorMessage.c_str());
	}
	else if (!leaderboardData.empty())
	{
		// Header
		ImGui::Separator();
		ImGui::Columns(5, "leaderboard_columns");
		ImGui::SetColumnWidth(0, 60);
		ImGui::SetColumnWidth(1, 200);
		ImGui::SetColumnWidth(2, 100);
		ImGui::SetColumnWidth(3, 100);
		ImGui::SetColumnWidth(4, 100);
		
		ImGui::Text("Rank"); ImGui::NextColumn();
		ImGui::Text("Username"); ImGui::NextColumn();
		ImGui::Text("Score"); ImGui::NextColumn();
		ImGui::Text("Kills"); ImGui::NextColumn();
		ImGui::Text("Wave"); ImGui::NextColumn();
		ImGui::Separator();
		
		// Data
		std::string currentUsername = GameManager::GetInstance().GetUsername();
		
		for (const auto& entry : leaderboardData)
		{
			// Highlight current player
			bool isCurrentPlayer = (entry.username == currentUsername);
			if (isCurrentPlayer)
			{
				ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.8f, 0.2f, 1.0f));
			}
			
			// Rank dengan medal untuk top 3
			if (entry.rank == 1)
				ImGui::Text("%d", entry.rank);
			else if (entry.rank == 2)
				ImGui::Text("%d", entry.rank);
			else if (entry.rank == 3)
				ImGui::Text("%d", entry.rank);
			else
				ImGui::Text("#%d", entry.rank);
			ImGui::NextColumn();
			
			// Username
			if (isCurrentPlayer)
				ImGui::Text(">> %s", entry.username.c_str());
			else
				ImGui::Text("%s", entry.username.c_str());
			ImGui::NextColumn();
			
			// Score
			ImGui::Text("%d", entry.score);
			ImGui::NextColumn();
			
			// Kills
			ImGui::Text("%d", entry.killCount);
			ImGui::NextColumn();
			
			// Wave
			ImGui::Text("%d", entry.wave);
			ImGui::NextColumn();
			
			if (isCurrentPlayer)
			{
				ImGui::PopStyleColor();
			}
		}
		
		ImGui::Columns(1);
		ImGui::Separator();
	}
	
	ImGui::Spacing();
	
	if (ImGui::Button("Refresh", ImVec2(120, 30)))
	{
		LoadLeaderboard();
	}
	
	ImGui::SameLine();
	
	if (ImGui::Button("⬅️ Back to Menu", ImVec2(150, 30)))
	{
		GameManager::GetInstance().GetGameState().ChangeState(EGameState::eMainMenu);
	}
	
	ImGui::End();
}

void LeaderboardState::iExit()
{
	std::cout << "[Leaderboard] Exiting leaderboard state" << std::endl;
}
