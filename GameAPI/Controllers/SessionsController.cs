using GameAPI.Data;
using GameAPI.DTOs;
using GameAPI.Models;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;

namespace GameAPI.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class SessionsController : ControllerBase
    {
        private readonly AppDbContext _context;
    private readonly ILogger<SessionsController> _logger;

     public SessionsController(AppDbContext context, ILogger<SessionsController> logger)
        {
            _context = context;
      _logger = logger;
        }

   // POST: api/sessions/save
  /// <summary>
        /// Save current game progress
        /// </summary>
        [HttpPost("save")]
    public async Task<ActionResult<GameSessionResponseDto>> SaveGameSession(SaveGameSessionDto dto)
        {
       if (!ModelState.IsValid)
 {
       return BadRequest(ModelState);
  }

     // Deactivate old sessions for this user
     var oldSessions = await _context.GameSessions
   .Where(s => s.Username.ToLower() == dto.Username.ToLower() && s.IsActive)
     .ToListAsync();

   foreach (var session in oldSessions)
      {
   session.IsActive = false;
     }

 // Create new session
 var gameSession = new GameSession
  {
        Username = dto.Username,
     CurrentScore = dto.CurrentScore,
    CurrentWave = dto.CurrentWave,
       CurrentKillCount = dto.CurrentKillCount,
 GameStateData = dto.GameStateData,
          SavedAt = DateTime.UtcNow,
      IsActive = true
       };

  _context.GameSessions.Add(gameSession);
   await _context.SaveChangesAsync();

         _logger.LogInformation("Game session saved: Player={Username}, Score={Score}, Wave={Wave}", 
gameSession.Username, gameSession.CurrentScore, gameSession.CurrentWave);

       var response = new GameSessionResponseDto
      {
Id = gameSession.Id,
         Username = gameSession.Username,
   CurrentScore = gameSession.CurrentScore,
           CurrentWave = gameSession.CurrentWave,
    CurrentKillCount = gameSession.CurrentKillCount,
     GameStateData = gameSession.GameStateData,
 SavedAt = gameSession.SavedAt
   };

    return Ok(response);
     }

     // GET: api/sessions/load/{username}
     /// <summary>
    /// Load saved game progress for a player
        /// </summary>
        [HttpGet("load/{username}")]
  public async Task<ActionResult<GameSessionResponseDto>> LoadGameSession(string username)
   {
   var session = await _context.GameSessions
       .Where(s => s.Username.ToLower() == username.ToLower() && s.IsActive)
   .OrderByDescending(s => s.SavedAt)
      .FirstOrDefaultAsync();

 if (session == null)
  {
        return NotFound(new { message = $"No saved game found for player '{username}'" });
      }

      _logger.LogInformation("Game session loaded: Player={Username}, Score={Score}, Wave={Wave}",
 session.Username, session.CurrentScore, session.CurrentWave);

      var response = new GameSessionResponseDto
       {
    Id = session.Id,
   Username = session.Username,
   CurrentScore = session.CurrentScore,
          CurrentWave = session.CurrentWave,
   CurrentKillCount = session.CurrentKillCount,
    GameStateData = session.GameStateData,
        SavedAt = session.SavedAt
            };

      return Ok(response);
     }

     // DELETE: api/sessions/clear/{username}
   /// <summary>
   /// Clear saved game session for a player
    /// </summary>
        [HttpDelete("clear/{username}")]
        public async Task<IActionResult> ClearGameSession(string username)
 {
    var sessions = await _context.GameSessions
      .Where(s => s.Username.ToLower() == username.ToLower() && s.IsActive)
        .ToListAsync();

      if (!sessions.Any())
   {
  return NotFound(new { message = $"No active session found for player '{username}'" });
       }

   foreach (var session in sessions)
            {
    session.IsActive = false;
    }

      await _context.SaveChangesAsync();

      _logger.LogInformation("Game sessions cleared for player: {Username}", username);

     return NoContent();
     }

      // GET: api/sessions/check/{username}
     /// <summary>
        /// Check if player has saved game session
        /// </summary>
        [HttpGet("check/{username}")]
  public async Task<ActionResult<object>> CheckSavedGame(string username)
   {
      var hasSession = await _context.GameSessions
     .AnyAsync(s => s.Username.ToLower() == username.ToLower() && s.IsActive);

      return Ok(new { hasSavedGame = hasSession });
        }
    }
}
