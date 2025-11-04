using System.ComponentModel.DataAnnotations;

namespace GameAPI.DTOs
{
    // DTO untuk request create/update
    public class CreatePlayerScoreDto
    {
        [Required(ErrorMessage = "Username is required")]
        [MaxLength(50, ErrorMessage = "Username cannot exceed 50 characters")]
        public string Username { get; set; } = string.Empty;
  
        [Required(ErrorMessage = "Password is required")]
        [MaxLength(100, ErrorMessage = "Password cannot exceed 100 characters")]
        public string Password { get; set; } = string.Empty;
  
        [Required(ErrorMessage = "Score is required")]
        [Range(0, int.MaxValue, ErrorMessage = "Score must be >= 0")]
        public int Score { get; set; }
        
        [Range(0, int.MaxValue, ErrorMessage = "KillCount must be >= 0")]
        public int KillCount { get; set; } = 0;
        
        [Range(0, int.MaxValue, ErrorMessage = "Wave must be >= 0")]
        public int Wave { get; set; } = 0;
    }

    // DTO untuk response
    public class PlayerScoreResponseDto
    {
        public int Id { get; set; }
        public string Username { get; set; } = string.Empty;
        public int Score { get; set; }
        public int KillCount { get; set; }
        public int Wave { get; set; }
    }
    
    // DTO untuk leaderboard
    public class LeaderboardEntryDto
    {
        public int Rank { get; set; }
        public string Username { get; set; } = string.Empty;
        public int Score { get; set; }
        public int KillCount { get; set; }
        public int Wave { get; set; }
    }
    
    // DTO untuk rank info
    public class PlayerRankDto
    {
        public string Username { get; set; } = string.Empty;
        public int Rank { get; set; }
        public int Score { get; set; }
        public int TotalPlayers { get; set; }
    }
}
