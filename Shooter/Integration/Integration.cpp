#include "Integration.h"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <iostream>

using json = nlohmann::json;

namespace GameAPI
{
    APIClient::APIClient(const std::string& baseUrl)
        : baseUrl(baseUrl), verifySSL(false)
    {
    }

    void APIClient::SetBaseUrl(const std::string& url)
    {
        baseUrl = url;
    }

    void APIClient::SetVerifySSL(bool verify)
    {
        verifySSL = verify;
    }

    std::string APIClient::BuildUrl(const std::string& endpoint) const
    {
   return baseUrl + endpoint;
    }

    template<typename T>
    ApiResponse<T> APIClient::CreateErrorResponse(int statusCode, const std::string& message)
  {
   ApiResponse<T> response;
        response.success = false;
      response.statusCode = statusCode;
  response.errorMessage = message;
        return response;
    }

    // POST: Create a new score
    ApiResponse<PlayerScoreData> APIClient::CreateScore(
      const std::string& username,
        const std::string& password,
     int score,
   int killCount,
    int wave)
    {
        ApiResponse<PlayerScoreData> response;
        
        try
 {
            json requestBody = {
   {"username", username},
  {"password", password},
         {"score", score},
                {"killCount", killCount},
    {"wave", wave}
       };

     auto r = cpr::Post(
        cpr::Url{BuildUrl("/scores")},
   cpr::Header{{"Content-Type", "application/json"}},
   cpr::Body{requestBody.dump()},
          cpr::VerifySsl{verifySSL}
            );

          response.statusCode = r.status_code;

   if (r.status_code == 201) // Created
            {
      auto jsonResponse = json::parse(r.text);
     response.success = true;
   response.data.id = jsonResponse["id"];
        response.data.username = jsonResponse["username"];
    response.data.score = jsonResponse["score"];
            response.data.killCount = jsonResponse["killCount"];
         response.data.wave = jsonResponse["wave"];
            }
            else
      {
  response.success = false;
                auto errorJson = json::parse(r.text);
              response.errorMessage = errorJson.contains("message") 
? errorJson["message"].get<std::string>()
          : "Failed to create score";
       }
        }
        catch (const std::exception& e)
   {
    response.success = false;
         response.statusCode = 0;
            response.errorMessage = std::string("Exception: ") + e.what();
        }

        return response;
    }

    // GET: Get all scores with pagination
    ApiResponse<PaginatedScores> APIClient::GetScores(int page, int pageSize)
    {
        ApiResponse<PaginatedScores> response;

        try
        {
auto r = cpr::Get(
 cpr::Url{BuildUrl("/scores")},
    cpr::Parameters{{"page", std::to_string(page)}, {"pageSize", std::to_string(pageSize)}},
         cpr::VerifySsl{verifySSL}
            );

            response.statusCode = r.status_code;

   if (r.status_code == 200)
      {
    auto jsonResponse = json::parse(r.text);
    response.success = true;

         // Parse pagination
          response.data.pagination.page = jsonResponse["pagination"]["page"];
                response.data.pagination.pageSize = jsonResponse["pagination"]["pageSize"];
       response.data.pagination.totalCount = jsonResponse["pagination"]["totalCount"];
          response.data.pagination.totalPages = jsonResponse["pagination"]["totalPages"];

       // Parse data
     for (const auto& item : jsonResponse["data"])
    {
    PlayerScoreData scoreData;
            scoreData.id = item["id"];
        scoreData.username = item["username"];
         scoreData.score = item["score"];
       scoreData.killCount = item["killCount"];
        scoreData.wave = item["wave"];
          response.data.data.push_back(scoreData);
           }
            }
    else
   {
      response.success = false;
             response.errorMessage = "Failed to get scores";
            }
        }
        catch (const std::exception& e)
        {
 response.success = false;
            response.statusCode = 0;
      response.errorMessage = std::string("Exception: ") + e.what();
        }

        return response;
    }

    // GET: Get score by ID
    ApiResponse<PlayerScoreData> APIClient::GetScoreById(int id)
    {
        ApiResponse<PlayerScoreData> response;

        try
        {
auto r = cpr::Get(
                cpr::Url{BuildUrl("/scores/" + std::to_string(id))},
     cpr::VerifySsl{verifySSL}
       );

      response.statusCode = r.status_code;

    if (r.status_code == 200)
            {
   auto jsonResponse = json::parse(r.text);
  response.success = true;
      response.data.id = jsonResponse["id"];
         response.data.username = jsonResponse["username"];
  response.data.score = jsonResponse["score"];
         response.data.killCount = jsonResponse["killCount"];
     response.data.wave = jsonResponse["wave"];
            }
  else
        {
        response.success = false;
       auto errorJson = json::parse(r.text);
    response.errorMessage = errorJson.contains("message")
    ? errorJson["message"].get<std::string>()
           : "Score not found";
    }
     }
        catch (const std::exception& e)
        {
            response.success = false;
            response.statusCode = 0;
        response.errorMessage = std::string("Exception: ") + e.what();
   }

        return response;
    }

    // GET: Get top N scores (leaderboard)
    ApiResponse<std::vector<LeaderboardEntry>> APIClient::GetTopScores(int n)
    {
        ApiResponse<std::vector<LeaderboardEntry>> response;

     try
        {
       auto r = cpr::Get(
     cpr::Url{BuildUrl("/scores/top/" + std::to_string(n))},
cpr::VerifySsl{verifySSL}
         );

   response.statusCode = r.status_code;

  if (r.status_code == 200)
        {
  auto jsonResponse = json::parse(r.text);
 response.success = true;

  for (const auto& item : jsonResponse)
       {
       LeaderboardEntry entry;
   entry.rank = item["rank"];
   entry.username = item["username"];
        entry.score = item["score"];
       entry.killCount = item["killCount"];
      entry.wave = item["wave"];
         response.data.push_back(entry);
        }
            }
       else
       {
                response.success = false;
    response.errorMessage = "Failed to get leaderboard";
}
        }
        catch (const std::exception& e)
        {
   response.success = false;
         response.statusCode = 0;
response.errorMessage = std::string("Exception: ") + e.what();
        }

        return response;
    }

    // GET: Get player rank
    ApiResponse<PlayerRankData> APIClient::GetPlayerRank(const std::string& username)
    {
      ApiResponse<PlayerRankData> response;

        try
        {
    auto r = cpr::Get(
cpr::Url{BuildUrl("/scores/rank/" + username)},
        cpr::VerifySsl{verifySSL}
  );

            response.statusCode = r.status_code;

            if (r.status_code == 200)
            {
        auto jsonResponse = json::parse(r.text);
       response.success = true;
        response.data.username = jsonResponse["username"];
     response.data.rank = jsonResponse["rank"];
     response.data.score = jsonResponse["score"];
          response.data.totalPlayers = jsonResponse["totalPlayers"];
            }
      else
            {
    response.success = false;
        auto errorJson = json::parse(r.text);
                response.errorMessage = errorJson.contains("message")
            ? errorJson["message"].get<std::string>()
   : "Player not found";
   }
        }
        catch (const std::exception& e)
        {
            response.success = false;
            response.statusCode = 0;
            response.errorMessage = std::string("Exception: ") + e.what();
        }

 return response;
    }

    // GET: Get player history
    ApiResponse<std::vector<PlayerScoreData>> APIClient::GetPlayerHistory(const std::string& username)
    {
  ApiResponse<std::vector<PlayerScoreData>> response;

        try
        {
    auto r = cpr::Get(
  cpr::Url{BuildUrl("/scores/player/" + username + "/history")},
        cpr::VerifySsl{verifySSL}
   );

            response.statusCode = r.status_code;

        if (r.status_code == 200)
      {
   auto jsonResponse = json::parse(r.text);
    response.success = true;

  for (const auto& item : jsonResponse)
 {
            PlayerScoreData scoreData;
             scoreData.id = item["id"];
      scoreData.username = item["username"];
         scoreData.score = item["score"];
               scoreData.killCount = item["killCount"];
        scoreData.wave = item["wave"];
   response.data.push_back(scoreData);
       }
       }
          else
            {
    response.success = false;
              auto errorJson = json::parse(r.text);
        response.errorMessage = errorJson.contains("message")
   ? errorJson["message"].get<std::string>()
             : "No history found";
 }
        }
        catch (const std::exception& e)
        {
   response.success = false;
response.statusCode = 0;
        response.errorMessage = std::string("Exception: ") + e.what();
        }

        return response;
    }

    // GET: Get game statistics
    ApiResponse<GameStatistics> APIClient::GetStatistics()
    {
      ApiResponse<GameStatistics> response;

 try
        {
    auto r = cpr::Get(
        cpr::Url{BuildUrl("/scores/stats")},
       cpr::VerifySsl{verifySSL}
          );

response.statusCode = r.status_code;

            if (r.status_code == 200)
     {
    auto jsonResponse = json::parse(r.text);
     response.success = true;
response.data.totalGames = jsonResponse["totalGames"];
      response.data.totalPlayers = jsonResponse["totalPlayers"];
 response.data.highestScore = jsonResponse["highestScore"];
      response.data.averageScore = jsonResponse["averageScore"];
       }
      else
            {
         response.success = false;
     response.errorMessage = "Failed to get statistics";
          }
        }
        catch (const std::exception& e)
        {
      response.success = false;
            response.statusCode = 0;
       response.errorMessage = std::string("Exception: ") + e.what();
    }

        return response;
    }

    // PUT: Update existing score
    ApiResponse<bool> APIClient::UpdateScore(
        int id,
        const std::string& username,
        const std::string& password,
    int score,
 int killCount,
        int wave)
    {
        ApiResponse<bool> response;

        try
     {
   json requestBody = {
    {"username", username},
     {"password", password},
         {"score", score},
    {"killCount", killCount},
         {"wave", wave}
    };

            auto r = cpr::Put(
              cpr::Url{BuildUrl("/scores/" + std::to_string(id))},
      cpr::Header{{"Content-Type", "application/json"}},
     cpr::Body{requestBody.dump()},
         cpr::VerifySsl{verifySSL}
            );

            response.statusCode = r.status_code;

if (r.status_code == 204) // No Content
   {
       response.success = true;
        response.data = true;
       }
            else
            {
    response.success = false;
            response.data = false;
auto errorJson = json::parse(r.text);
  response.errorMessage = errorJson.contains("message")
            ? errorJson["message"].get<std::string>()
       : "Failed to update score";
    }
        }
        catch (const std::exception& e)
        {
   response.success = false;
            response.statusCode = 0;
            response.data = false;
   response.errorMessage = std::string("Exception: ") + e.what();
      }

    return response;
    }

    // DELETE: Delete score
    ApiResponse<bool> APIClient::DeleteScore(int id)
    {
        ApiResponse<bool> response;

        try
        {
            auto r = cpr::Delete(
                cpr::Url{BuildUrl("/scores/" + std::to_string(id))},
      cpr::VerifySsl{verifySSL}
            );

       response.statusCode = r.status_code;

            if (r.status_code == 204) // No Content
            {
             response.success = true;
          response.data = true;
       }
          else
      {
     response.success = false;
        response.data = false;
    auto errorJson = json::parse(r.text);
     response.errorMessage = errorJson.contains("message")
         ? errorJson["message"].get<std::string>()
      : "Failed to delete score";
    }
    }
        catch (const std::exception& e)
        {
          response.success = false;
  response.statusCode = 0;
            response.data = false;
  response.errorMessage = std::string("Exception: ") + e.what();
        }

        return response;
    }

 // Helper: Submit score at end of game
    ApiResponse<PlayerScoreData> APIClient::SubmitGameScore(
        const std::string& username,
        const std::string& password,
   int score,
        int killCount,
  int wave)
    {
        return CreateScore(username, password, score, killCount, wave);
    }

}