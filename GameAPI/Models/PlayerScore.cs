using System.ComponentModel.DataAnnotations;

namespace GameAPI.Models
{
    public class PlayerScore
    {
        public int Id { get; set; }
      
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
}
