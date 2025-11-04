#ifndef INTEGRATION_H
#define INTEGRATION_H

#include <string>
#include <vector>
#include <optional>
#include <functional>

namespace GameAPI
{
    // DTO structures matching the C# API
    struct PlayerScoreData
    {
 int id;
        std::string username;
        int score;
        int killCount;
        int wave;
    };

    struct LeaderboardEntry
    {
        int rank;
      std::string username;
        int score;
        int killCount;
        int wave;
    };

    struct PlayerRankData
 {
      std::string username;
        int rank;
        int score;
        int totalPlayers;
    };

    struct GameStatistics
    {
      int totalGames;
    int totalPlayers;
        int highestScore;
        double averageScore;
    };

  struct PaginationInfo
    {
        int page;
int pageSize;
        int totalCount;
     int totalPages;
    };

    struct PaginatedScores
    {
std::vector<PlayerScoreData> data;
        PaginationInfo pagination;
    };

    // API Response wrapper
    template<typename T>
  struct ApiResponse
    {
   bool success;
        int statusCode;
        std::string errorMessage;
      T data;
    };

    class APIClient
    {
    public:
 APIClient(const std::string& baseUrl = "https://localhost:7016/api");
        ~APIClient() = default;

        // Set base URL
     void SetBaseUrl(const std::string& url);

    // POST: Create a new score
 ApiResponse<PlayerScoreData> CreateScore(
            const std::string& username,
            const std::string& password,
          int score,
            int killCount,
            int wave
        );

        // GET: Get all scores with pagination
        ApiResponse<PaginatedScores> GetScores(int page = 1, int pageSize = 10);

    // GET: Get score by ID
        ApiResponse<PlayerScoreData> GetScoreById(int id);

      // GET: Get top N scores (leaderboard)
        ApiResponse<std::vector<LeaderboardEntry>> GetTopScores(int n = 10);

        // GET: Get player rank
  ApiResponse<PlayerRankData> GetPlayerRank(const std::string& username);

        // GET: Get player history
        ApiResponse<std::vector<PlayerScoreData>> GetPlayerHistory(const std::string& username);

        // GET: Get game statistics
ApiResponse<GameStatistics> GetStatistics();

  // PUT: Update existing score
   ApiResponse<bool> UpdateScore(
       int id,
       const std::string& username,
    const std::string& password,
            int score,
            int killCount,
  int wave
        );

        // DELETE: Delete score
        ApiResponse<bool> DeleteScore(int id);

   // Helper: Submit score at end of game
        ApiResponse<PlayerScoreData> SubmitGameScore(
            const std::string& username,
 const std::string& password,
            int score,
            int killCount,
     int wave
     );

     // Enable/Disable SSL verification (useful for development)
  void SetVerifySSL(bool verify);

 private:
     std::string baseUrl;
        bool verifySSL;

        // Helper methods
    std::string BuildUrl(const std::string& endpoint) const;
  template<typename T>
        ApiResponse<T> CreateErrorResponse(int statusCode, const std::string& message);
 };

} // namespace GameAPI

#endif // INTEGRATION_H
