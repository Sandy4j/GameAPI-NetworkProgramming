using System.ComponentModel.DataAnnotations;

namespace GameAPI.DTOs
{
    public class SaveGameSessionDto
    {
        [Required]
        public string Username { get; set; } = string.Empty;
      
        [Required]
        public string Password { get; set; } = string.Empty;
        
      public int CurrentScore { get; set; }
     public int CurrentWave { get; set; }
      public int CurrentKillCount { get; set; }
        public string GameStateData { get; set; } = string.Empty;
    }

    public class GameSessionResponseDto
    {
        public int Id { get; set; }
        public string Username { get; set; } = string.Empty;
 public int CurrentScore { get; set; }
        public int CurrentWave { get; set; }
        public int CurrentKillCount { get; set; }
        public string GameStateData { get; set; } = string.Empty;
        public DateTime SavedAt { get; set; }
    }
}
