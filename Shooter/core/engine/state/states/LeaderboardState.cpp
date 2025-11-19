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
	level = new Level("leaderboard_level.json");
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
	
	// Update UI dengan data
	UpdateLeaderboardUI();
}

void LeaderboardState::LoadLeaderboard()
{
	std::cout << "[Leaderboard] Loading leaderboard from API..." << std::endl;
	isLoading = true;
	errorMessage.clear();
	
	// Ambil top 5 dari REST API (sesuai dengan UI yang tersedia)
	leaderboardData = GameAPIManager::GetInstance().GetLeaderboard(5);
	
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

void LeaderboardState::UpdateLeaderboardUI()
{
	Entity* entity = level->GetEntity();
	if (!entity) return;
	
	// Update status text
	TextBlock* statusText = entity->GetComponent<TextBlock>(100);
	if (statusText)
	{
		if (isLoading)
		{
			statusText->label = "Loading leaderboard...";
		}
		else if (!errorMessage.empty())
		{
			statusText->label = errorMessage;
		}
		else
		{
			statusText->label = ""; // Clear status if data loaded successfully
		}
	}
	
	// Clear all entries first
	for (int i = 0; i < 5; i++)
	{
		int baseId = 20 + (i * 10); // 20, 30, 40, 50, 60
		
		TextBlock* rankText = entity->GetComponent<TextBlock>(baseId);
		TextBlock* usernameText = entity->GetComponent<TextBlock>(baseId + 1);
		TextBlock* scoreText = entity->GetComponent<TextBlock>(baseId + 2);
		TextBlock* killsText = entity->GetComponent<TextBlock>(baseId + 3);
		TextBlock* waveText = entity->GetComponent<TextBlock>(baseId + 4);
		
		if (rankText) rankText->label = "";
		if (usernameText) usernameText->label = "";
		if (scoreText) scoreText->label = "";
		if (killsText) killsText->label = "";
		if (waveText) waveText->label = "";
	}
	
	// Fill with actual data
	if (!leaderboardData.empty())
	{
		std::string currentUsername = GameManager::GetInstance().GetUsername();
		
		for (size_t i = 0; i < leaderboardData.size() && i < 5; i++)
		{
			const auto& entry = leaderboardData[i];
			int baseId = 20 + (i * 10);
			
			TextBlock* rankText = entity->GetComponent<TextBlock>(baseId);
			TextBlock* usernameText = entity->GetComponent<TextBlock>(baseId + 1);
			TextBlock* scoreText = entity->GetComponent<TextBlock>(baseId + 2);
			TextBlock* killsText = entity->GetComponent<TextBlock>(baseId + 3);
			TextBlock* waveText = entity->GetComponent<TextBlock>(baseId + 4);
			
			// Add medal/prefix for top 3
			std::string rankPrefix;
			if (entry.rank == 1) rankPrefix = " ";
			else if (entry.rank == 2) rankPrefix = " ";
			else if (entry.rank == 3) rankPrefix = " ";
			else rankPrefix = "#";
			
			// Check if this is current player
			bool isCurrentPlayer = (entry.username == currentUsername);
			std::string usernameDisplay = isCurrentPlayer ? ">> " + entry.username + " <<" : entry.username;
			
			if (rankText) rankText->label = rankPrefix + std::to_string(entry.rank);
			if (usernameText) usernameText->label = usernameDisplay;
			if (scoreText) scoreText->label = std::to_string(entry.score);
			if (killsText) killsText->label = std::to_string(entry.killCount);
			if (waveText) waveText->label = std::to_string(entry.wave);
		}
	}
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
		UpdateLeaderboardUI();
	}
}

void LeaderboardState::iUpdateRenderObject()
{
	level->UpdateRenderObject();
}

void LeaderboardState::iUpdateRenderUI()
{
	level->UpdateRenderUI();
}

void LeaderboardState::iExit()
{
	std::cout << "[Leaderboard] Exiting leaderboard state" << std::endl;
	level->UnloadLevel();
}
