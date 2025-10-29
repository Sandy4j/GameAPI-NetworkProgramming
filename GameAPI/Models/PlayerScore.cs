using System.ComponentModel.DataAnnotations;

namespace GameAPI.Models
{
    public class PlayerScore
    {
        public int Id { get; set; }
      
        [Required(ErrorMessage = "PlayerName is required")]
        [MaxLength(100, ErrorMessage = "PlayerName cannot exceed 100 characters")]
        public string PlayerName { get; set; } = string.Empty;
        
        [Required(ErrorMessage = "Score is required")]
        [Range(0, int.MaxValue, ErrorMessage = "Score must be >= 0")]
        public int Score { get; set; }
        
        // Additional fields untuk game shooter
        public int Kills { get; set; } = 0;  // Jumlah enemy terbunuh
        public int Deaths { get; set; } = 0; // Jumlah kematian
        public int ShotsFired { get; set; } = 0; // Jumlah tembakan
        public int ShotsHit { get; set; } = 0;   // Jumlah tembakan mengenai
     
        public DateTime CreatedAt { get; set; } = DateTime.UtcNow;
        public DateTime? UpdatedAt { get; set; }
        
        // Computed property untuk accuracy
        public double Accuracy => ShotsFired > 0 ? Math.Round((double)ShotsHit / ShotsFired * 100, 2) : 0;
    }
}
