#include "GameAPIManager.h"
#include "GameManager.h"
#include <iostream>

void GameAPIManager::Initialize(const std::string& apiUrl)
{
    apiClient = std::make_unique<GameAPI::APIClient>(apiUrl);
    apiClient->SetVerifySSL(false);
    std::cout << "[GameAPI] Initialized with URL: " << apiUrl << std::endl;
}

void GameAPIManager::SetPlayerCredentials(const std::string& username, const std::string& password)
{
    currentUsername = username;
    currentPassword = password;
}

void GameAPIManager::SetLastError(const std::string& error)
{
    lastError = error;
    std::cerr << "[GameAPI Error] " << error << std::endl;
}

bool GameAPIManager::SubmitCurrentGameScore()
{
    if (!apiClient)
 {
        SetLastError("API Client not initialized");
        return false;
    }

    // Get data from GameManager
    auto& gameManager = GameManager::GetInstance();
    
 // Use stored credentials or get from GameManager
    std::string username = currentUsername.empty() ? gameManager.GetUsername() : currentUsername;
    std::string password = currentPassword.empty() ? gameManager.GetPassword() : currentPassword;
    int score = gameManager.GetScore();
    int wave = gameManager.GetWave();
    int killCount = gameManager.GetKillCount();

    if (username.empty())
    {
 SetLastError("Username is empty");
        return false;
 }

    std::cout << "[GameAPI] Submitting score - User: " << username 
              << ", Score: " << score 
  << ", Wave: " << wave 
          << ", Kills: " << killCount << std::endl;

  auto response = apiClient->SubmitGameScore(username, password, score, killCount, wave);

    if (response.success)
    {
        std::cout << "[GameAPI] Score submitted successfully! ID: " << response.data.id << std::endl;
    return true;
    }
    else
    {
        SetLastError("Failed to submit score: " + response.errorMessage);
        return false;
    }
}

std::vector<GameAPI::LeaderboardEntry> GameAPIManager::GetLeaderboard(int topN)
{
    std::vector<GameAPI::LeaderboardEntry> leaderboard;

    if (!apiClient)
    {
        SetLastError("API Client not initialized");
     return leaderboard;
    }

    auto response = apiClient->GetTopScores(topN);

    if (response.success)
    {
        std::cout << "[GameAPI] Retrieved " << response.data.size() << " leaderboard entries" << std::endl;
        return response.data;
    }
    else
    {
    SetLastError("Failed to get leaderboard: " + response.errorMessage);
        return leaderboard;
    }
}

bool GameAPIManager::GetPlayerRank(int& outRank, int& outTotalPlayers)
{
    if (!apiClient)
  {
  SetLastError("API Client not initialized");
        return false;
    }

    std::string username = currentUsername.empty() 
        ? GameManager::GetInstance().GetUsername() 
        : currentUsername;

    if (username.empty())
    {
  SetLastError("Username is empty");
        return false;
    }

  auto response = apiClient->GetPlayerRank(username);

    if (response.success)
    {
        outRank = response.data.rank;
        outTotalPlayers = response.data.totalPlayers;
        std::cout << "[GameAPI] Player rank: " << outRank 
        << " out of " << outTotalPlayers << std::endl;
        return true;
    }
    else
    {
        SetLastError("Failed to get player rank: " + response.errorMessage);
    return false;
    }
}

bool GameAPIManager::GetGameStats(int& outTotalGames, int& outHighestScore, double& outAvgScore)
{
    if (!apiClient)
    {
        SetLastError("API Client not initialized");
        return false;
    }

    auto response = apiClient->GetStatistics();

    if (response.success)
    {
    outTotalGames = response.data.totalGames;
        outHighestScore = response.data.highestScore;
      outAvgScore = response.data.averageScore;
   std::cout << "[GameAPI] Game stats retrieved - Games: " << outTotalGames 
           << ", Highest: " << outHighestScore 
 << ", Avg: " << outAvgScore << std::endl;
        return true;
    }
    else
    {
        SetLastError("Failed to get game stats: " + response.errorMessage);
        return false;
    }
}

bool GameAPIManager::CheckPlayerExists(const std::string& username)
{
    if (!apiClient)
    {
      SetLastError("API Client not initialized");
        return false;
  }

    // Try to get player rank to see if they exist
    auto response = apiClient->GetPlayerRank(username);
    return response.success;
}

bool GameAPIManager::TestConnection()
{
    if (!apiClient)
    {
        SetLastError("API Client not initialized");
        return false;
    }

    std::cout << "[GameAPI] Testing connection..." << std::endl;
    auto response = apiClient->GetStatistics();

    if (response.success)
    {
      std::cout << "[GameAPI] Connection successful!" << std::endl;
return true;
    }
    else
 {
        SetLastError("Connection test failed: " + response.errorMessage);
        return false;
    }
}
