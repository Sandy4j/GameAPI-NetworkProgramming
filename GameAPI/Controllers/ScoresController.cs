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
     .Skip((page - 1) * pageSize)
           .Take(pageSize)
          .Select(s => new PlayerScoreResponseDto
             {
         Id = s.Id,
         Username = s.Username,
 Score = s.Score,
          KillCount = s.KillCount,
      Wave = s.Wave
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
       Username = playerScore.Username,
          Score = playerScore.Score,
    KillCount = playerScore.KillCount,
    Wave = playerScore.Wave
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

            // First, get the data from database
            var topScores = await _context.PlayerScores
          .OrderByDescending(s => s.Score)
.Take(n)
            .ToListAsync(); // Execute query first

            // Then, map to DTO with ranking (in-memory operation)
         var leaderboard = topScores
          .Select((s, index) => new LeaderboardEntryDto
{
                Rank = index + 1, // Now we can use index
    Username = s.Username,
                 Score = s.Score,
         KillCount = s.KillCount,
        Wave = s.Wave
       })
  .ToList();

 _logger.LogInformation("Retrieved top {Count} scores for leaderboard", leaderboard.Count);

            return Ok(leaderboard);
        }

      // GET: api/scores/rank/{username}
     /// <summary>
     /// Get player's rank by username
        /// </summary>
        [HttpGet("rank/{username}")]
      public async Task<ActionResult<PlayerRankDto>> GetPlayerRank(string username)
     {
            // Find player's best score
       var playerScore = await _context.PlayerScores
     .Where(s => s.Username.ToLower() == username.ToLower())
             .OrderByDescending(s => s.Score)
        .FirstOrDefaultAsync();

     if (playerScore == null)
    {
  return NotFound(new { message = $"Player '{username}' not found" });
       }

      // Count how many scores are better
            var rank = await _context.PlayerScores
  .CountAsync(s => s.Score > playerScore.Score) + 1;

   var totalPlayers = await _context.PlayerScores.CountAsync();

         return Ok(new PlayerRankDto
   {
      Username = playerScore.Username,
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

            var playerScore = new PlayerScore
            {
        Username = dto.Username,
    Password = dto.Password,
     Score = dto.Score,
KillCount = dto.KillCount,
                Wave = dto.Wave
       };

    _context.PlayerScores.Add(playerScore);
   await _context.SaveChangesAsync();

   _logger.LogInformation("New score created: Player={Username}, Score={Score}", 
       playerScore.Username, playerScore.Score);

       var response = new PlayerScoreResponseDto
   {
     Id = playerScore.Id,
 Username = playerScore.Username,
        Score = playerScore.Score,
      KillCount = playerScore.KillCount,
  Wave = playerScore.Wave
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

    var playerScore = await _context.PlayerScores.FindAsync(id);
      if (playerScore == null)
        {
  return NotFound(new { message = $"Score with ID {id} not found" });
}

    playerScore.Username = dto.Username;
            playerScore.Password = dto.Password;
            playerScore.Score = dto.Score;
            playerScore.KillCount = dto.KillCount;
      playerScore.Wave = dto.Wave;

       try
            {
      await _context.SaveChangesAsync();
       _logger.LogInformation("Score updated: ID={Id}, Player={Username}, Score={Score}", 
        id, playerScore.Username, playerScore.Score);
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

      _logger.LogInformation("Score deleted: ID={Id}, Player={Username}", 
 id, playerScore.Username);

            return NoContent();
        }

// GET: api/scores/player/{username}/history
        /// <summary>
        /// Get all scores for a specific player
    /// </summary>
  [HttpGet("player/{username}/history")]
     public async Task<ActionResult<IEnumerable<PlayerScoreResponseDto>>> GetPlayerHistory(string username)
      {
var scores = await _context.PlayerScores
         .Where(s => s.Username.ToLower() == username.ToLower())
     .OrderByDescending(s => s.Score)
       .Select(s => new PlayerScoreResponseDto
          {
        Id = s.Id,
          Username = s.Username,
         Score = s.Score,
         KillCount = s.KillCount,
        Wave = s.Wave
       })
        .ToListAsync();

         if (!scores.Any())
       {
        return NotFound(new { message = $"No scores found for player '{username}'" });
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
   var totalPlayers = await _context.PlayerScores.Select(s => s.Username).Distinct().CountAsync();
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
