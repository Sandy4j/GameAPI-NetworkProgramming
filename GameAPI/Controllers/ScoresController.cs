using GameAPI.Data;
using GameAPI.DTOs;
using GameAPI.Models;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;

namespace GameAPI.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class ScoresController : ControllerBase
    {
        private readonly AppDbContext _context;
      private readonly ILogger<ScoresController> _logger;

     public ScoresController(AppDbContext context, ILogger<ScoresController> logger)
        {
         _context = context;
 _logger = logger;
        }

    // GET: api/scores?page=1&pageSize=10
        /// <summary>
        /// Get all player scores with pagination
   /// </summary>
   [HttpGet]
        public async Task<ActionResult<object>> GetScores(
      [FromQuery] int page = 1, 
       [FromQuery] int pageSize = 10)
        {
            if (page < 1) page = 1;
            if (pageSize < 1 || pageSize > 100) pageSize = 10;

            var totalCount = await _context.PlayerScores.CountAsync();
        var scores = await _context.PlayerScores
    .OrderByDescending(s => s.Score)
            .ThenBy(s => s.CreatedAt)
    .Skip((page - 1) * pageSize)
                .Take(pageSize)
     .Select(s => new PlayerScoreResponseDto
    {
   Id = s.Id,
             PlayerName = s.PlayerName,
     Score = s.Score,
   Kills = s.Kills,
          Deaths = s.Deaths,
                ShotsFired = s.ShotsFired,
    ShotsHit = s.ShotsHit,
        Accuracy = s.ShotsFired > 0 ? Math.Round((double)s.ShotsHit / s.ShotsFired * 100, 2) : 0,
     CreatedAt = s.CreatedAt,
  UpdatedAt = s.UpdatedAt
         })
                .ToListAsync();

            return Ok(new
          {
     data = scores,
         pagination = new
   {
    page,
         pageSize,
           totalCount,
       totalPages = (int)Math.Ceiling((double)totalCount / pageSize)
  }
   });
}

// GET: api/scores/5
        /// <summary>
        /// Get a specific player score by ID
        /// </summary>
        [HttpGet("{id}")]
        public async Task<ActionResult<PlayerScoreResponseDto>> GetPlayerScore(int id)
        {
            var playerScore = await _context.PlayerScores.FindAsync(id);

          if (playerScore == null)
  {
                return NotFound(new { message = $"Score with ID {id} not found" });
    }

            return Ok(new PlayerScoreResponseDto
     {
        Id = playerScore.Id,
           PlayerName = playerScore.PlayerName,
    Score = playerScore.Score,
       Kills = playerScore.Kills,
 Deaths = playerScore.Deaths,
        ShotsFired = playerScore.ShotsFired,
     ShotsHit = playerScore.ShotsHit,
    Accuracy = playerScore.Accuracy,
         CreatedAt = playerScore.CreatedAt,
                UpdatedAt = playerScore.UpdatedAt
   });
 }

 // GET: api/scores/top/10
        /// <summary>
        /// Get top N highest scores (leaderboard)
        /// </summary>
  [HttpGet("top/{n}")]
        public async Task<ActionResult<IEnumerable<LeaderboardEntryDto>>> GetTopScores(int n = 10)
        {
   if (n < 1) n = 10;
  if (n > 100) n = 100;

            var topScores = await _context.PlayerScores
      .OrderByDescending(s => s.Score)
            .ThenBy(s => s.CreatedAt)
        .Take(n)
             .Select((s, index) => new LeaderboardEntryDto
        {
      Rank = 0, // Will be set after
            PlayerName = s.PlayerName,
    Score = s.Score,
    Kills = s.Kills,
    Accuracy = s.ShotsFired > 0 ? Math.Round((double)s.ShotsHit / s.ShotsFired * 100, 2) : 0,
      CreatedAt = s.CreatedAt
      })
     .ToListAsync();

            // Set rank manually
   for (int i = 0; i < topScores.Count; i++)
{
            topScores[i].Rank = i + 1;
 }

            return Ok(topScores);
  }

        // GET: api/scores/rank/{playerName}
        /// <summary>
  /// Get player's rank by name
      /// </summary>
        [HttpGet("rank/{playerName}")]
 public async Task<ActionResult<PlayerRankDto>> GetPlayerRank(string playerName)
  {
            // Find player's best score
            var playerScore = await _context.PlayerScores
          .Where(s => s.PlayerName.ToLower() == playerName.ToLower())
           .OrderByDescending(s => s.Score)
     .ThenBy(s => s.CreatedAt)
    .FirstOrDefaultAsync();

        if (playerScore == null)
      {
                return NotFound(new { message = $"Player '{playerName}' not found" });
       }

            // Count how many scores are better
        var rank = await _context.PlayerScores
           .CountAsync(s => 
               s.Score > playerScore.Score || 
       (s.Score == playerScore.Score && s.CreatedAt < playerScore.CreatedAt)) + 1;

            var totalPlayers = await _context.PlayerScores.CountAsync();

  return Ok(new PlayerRankDto
            {
     PlayerName = playerScore.PlayerName,
      Rank = rank,
        Score = playerScore.Score,
      TotalPlayers = totalPlayers
            });
        }

        // POST: api/scores
      /// <summary>
        /// Create a new player score
        /// </summary>
      [HttpPost]
        public async Task<ActionResult<PlayerScoreResponseDto>> CreatePlayerScore(CreatePlayerScoreDto dto)
        {
         if (!ModelState.IsValid)
     {
   return BadRequest(ModelState);
 }

        // Validate ShotsHit <= ShotsFired
       if (dto.ShotsHit > dto.ShotsFired)
      {
                return BadRequest(new { message = "ShotsHit cannot exceed ShotsFired" });
    }

       var playerScore = new PlayerScore
            {
            PlayerName = dto.PlayerName,
 Score = dto.Score,
       Kills = dto.Kills,
          Deaths = dto.Deaths,
          ShotsFired = dto.ShotsFired,
        ShotsHit = dto.ShotsHit,
     CreatedAt = DateTime.UtcNow
};

  _context.PlayerScores.Add(playerScore);
         await _context.SaveChangesAsync();

      _logger.LogInformation("New score created: Player={PlayerName}, Score={Score}", 
      playerScore.PlayerName, playerScore.Score);

    var response = new PlayerScoreResponseDto
            {
       Id = playerScore.Id,
       PlayerName = playerScore.PlayerName,
   Score = playerScore.Score,
            Kills = playerScore.Kills,
         Deaths = playerScore.Deaths,
  ShotsFired = playerScore.ShotsFired,
  ShotsHit = playerScore.ShotsHit,
                Accuracy = playerScore.Accuracy,
          CreatedAt = playerScore.CreatedAt,
         UpdatedAt = playerScore.UpdatedAt
         };

            return CreatedAtAction(nameof(GetPlayerScore), new { id = playerScore.Id }, response);
        }

        // PUT: api/scores/5
        /// <summary>
        /// Update an existing player score
        /// </summary>
     [HttpPut("{id}")]
        public async Task<IActionResult> UpdatePlayerScore(int id, CreatePlayerScoreDto dto)
        {
            if (!ModelState.IsValid)
  {
         return BadRequest(ModelState);
            }

     // Validate ShotsHit <= ShotsFired
  if (dto.ShotsHit > dto.ShotsFired)
        {
       return BadRequest(new { message = "ShotsHit cannot exceed ShotsFired" });
      }

    var playerScore = await _context.PlayerScores.FindAsync(id);
     if (playerScore == null)
        {
         return NotFound(new { message = $"Score with ID {id} not found" });
          }

    playerScore.PlayerName = dto.PlayerName;
            playerScore.Score = dto.Score;
  playerScore.Kills = dto.Kills;
 playerScore.Deaths = dto.Deaths;
            playerScore.ShotsFired = dto.ShotsFired;
  playerScore.ShotsHit = dto.ShotsHit;
          playerScore.UpdatedAt = DateTime.UtcNow;

   try
            {
    await _context.SaveChangesAsync();
     _logger.LogInformation("Score updated: ID={Id}, Player={PlayerName}, Score={Score}", 
              id, playerScore.PlayerName, playerScore.Score);
     }
            catch (DbUpdateConcurrencyException)
            {
         if (!PlayerScoreExists(id))
       {
        return NotFound();
  }
                throw;
            }

         return NoContent();
      }

        // DELETE: api/scores/5
     /// <summary>
        /// Delete a player score
        /// </summary>
        [HttpDelete("{id}")]
        public async Task<IActionResult> DeletePlayerScore(int id)
        {
  var playerScore = await _context.PlayerScores.FindAsync(id);
  if (playerScore == null)
{
   return NotFound(new { message = $"Score with ID {id} not found" });
  }

            _context.PlayerScores.Remove(playerScore);
        await _context.SaveChangesAsync();

            _logger.LogInformation("Score deleted: ID={Id}, Player={PlayerName}", 
       id, playerScore.PlayerName);

        return NoContent();
        }

// GET: api/scores/player/{playerName}/history
        /// <summary>
        /// Get all scores for a specific player
     /// </summary>
        [HttpGet("player/{playerName}/history")]
        public async Task<ActionResult<IEnumerable<PlayerScoreResponseDto>>> GetPlayerHistory(string playerName)
        {
      var scores = await _context.PlayerScores
       .Where(s => s.PlayerName.ToLower() == playerName.ToLower())
  .OrderByDescending(s => s.CreatedAt)
    .Select(s => new PlayerScoreResponseDto
     {
          Id = s.Id,
        PlayerName = s.PlayerName,
    Score = s.Score,
         Kills = s.Kills,
    Deaths = s.Deaths,
      ShotsFired = s.ShotsFired,
   ShotsHit = s.ShotsHit,
         Accuracy = s.ShotsFired > 0 ? Math.Round((double)s.ShotsHit / s.ShotsFired * 100, 2) : 0,
  CreatedAt = s.CreatedAt,
   UpdatedAt = s.UpdatedAt
      })
  .ToListAsync();

            if (!scores.Any())
         {
    return NotFound(new { message = $"No scores found for player '{playerName}'" });
 }

      return Ok(scores);
        }

        // GET: api/scores/stats
   /// <summary>
        /// Get overall game statistics
        /// </summary>
      [HttpGet("stats")]
        public async Task<ActionResult<object>> GetStatistics()
        {
          var totalGames = await _context.PlayerScores.CountAsync();
    var totalPlayers = await _context.PlayerScores.Select(s => s.PlayerName).Distinct().CountAsync();
            var highestScore = await _context.PlayerScores.MaxAsync(s => (int?)s.Score) ?? 0;
  var averageScore = await _context.PlayerScores.AverageAsync(s => (double?)s.Score) ?? 0;

            return Ok(new
            {
  totalGames,
                totalPlayers,
        highestScore,
                averageScore = Math.Round(averageScore, 2)
       });
  }

   private bool PlayerScoreExists(int id)
        {
            return _context.PlayerScores.Any(e => e.Id == id);
}
    }
}
