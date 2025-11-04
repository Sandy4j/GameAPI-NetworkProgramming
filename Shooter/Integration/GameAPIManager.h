#ifndef GAMEAPIMANAGER_H
#define GAMEAPIMANAGER_H

#include "Integration.h"
#include <memory>

class GameAPIManager
{
public:
    static GameAPIManager& GetInstance()
 {
    static GameAPIManager instance;
        return instance;
    }

    // Initialize the API client
    // Untuk akses dari device lain, gunakan IP address server
void Initialize(const std::string& apiUrl = "http://localhost:5155/api");

    // Submit current game score
 bool SubmitCurrentGameScore();

    // Get leaderboard for display
 std::vector<GameAPI::LeaderboardEntry> GetLeaderboard(int topN = 10);

    // Get player's current rank
    bool GetPlayerRank(int& outRank, int& outTotalPlayers);

    // Get game statistics
    bool GetGameStats(int& outTotalGames, int& outHighestScore, double& outAvgScore);

    // Check if player exists and can login (basic check)
  bool CheckPlayerExists(const std::string& username);

void SetPlayerCredentials(const std::string& username, const std::string& password);

    std::string GetLastError() const { return lastError; }

  bool TestConnection();

private:
    GameAPIManager() = default;
    ~GameAPIManager() = default;
    GameAPIManager(const GameAPIManager&) = delete;
    GameAPIManager& operator=(const GameAPIManager&) = delete;

    std::unique_ptr<GameAPI::APIClient> apiClient;
    std::string currentUsername;
    std::string currentPassword;
 std::string lastError;

 void SetLastError(const std::string& error);
};

#endif
