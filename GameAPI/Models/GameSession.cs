using System.ComponentModel.DataAnnotations;

namespace GameAPI.Models
{
    public class GameSession
    {
        public int Id { get; set; }
 
        [Required]
 [MaxLength(50)]
        public string Username { get; set; } = string.Empty;
        
        public int CurrentScore { get; set; }
    public int CurrentWave { get; set; }
      public int CurrentKillCount { get; set; }
        public string GameStateData { get; set; } = string.Empty;
        
        public DateTime SavedAt { get; set; } = DateTime.UtcNow;
        public bool IsActive { get; set; } = true;
 }
}
