using System.ComponentModel.DataAnnotations;

namespace GameAPI.DTOs
{
    // DTO untuk request create/update
    public class CreatePlayerScoreDto
    {
        [Required(ErrorMessage = "PlayerName is required")]
        [MaxLength(100, ErrorMessage = "PlayerName cannot exceed 100 characters")]
        public string PlayerName { get; set; } = string.Empty;
  
        [Required(ErrorMessage = "Score is required")]
        [Range(0, int.MaxValue, ErrorMessage = "Score must be >= 0")]
        public int Score { get; set; }
        
        [Range(0, int.MaxValue, ErrorMessage = "Kills must be >= 0")]
        public int Kills { get; set; } = 0;
        
        [Range(0, int.MaxValue, ErrorMessage = "Deaths must be >= 0")]
        public int Deaths { get; set; } = 0;
        
        [Range(0, int.MaxValue, ErrorMessage = "ShotsFired must be >= 0")]
        public int ShotsFired { get; set; } = 0;
  
 [Range(0, int.MaxValue, ErrorMessage = "ShotsHit must be >= 0")]
    public int ShotsHit { get; set; } = 0;
    }

    // DTO untuk response
    public class PlayerScoreResponseDto
    {
        public int Id { get; set; }
   public string PlayerName { get; set; } = string.Empty;
     public int Score { get; set; }
        public int Kills { get; set; }
        public int Deaths { get; set; }
        public int ShotsFired { get; set; }
        public int ShotsHit { get; set; }
        public double Accuracy { get; set; }
        public DateTime CreatedAt { get; set; }
   public DateTime? UpdatedAt { get; set; }
    }
    
    // DTO untuk leaderboard
    public class LeaderboardEntryDto
    {
        public int Rank { get; set; }
        public string PlayerName { get; set; } = string.Empty;
        public int Score { get; set; }
        public int Kills { get; set; }
   public double Accuracy { get; set; }
        public DateTime CreatedAt { get; set; }
    }
    
    // DTO untuk rank info
    public class PlayerRankDto
    {
  public string PlayerName { get; set; } = string.Empty;
   public int Rank { get; set; }
        public int Score { get; set; }
        public int TotalPlayers { get; set; }
    }
}
