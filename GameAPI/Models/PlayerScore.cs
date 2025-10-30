using System.ComponentModel.DataAnnotations;

namespace GameAPI.Models
{
    public class PlayerScore
    {
        public int Id { get; set; }

        [Required]
        [MaxLength(50)]
        public string Username { get; set; } = string.Empty;

        [Required]
        [MaxLength(100)]
        public string Password { get; set; } = string.Empty;

        [Required]
        public int Score { get; set; }

        public int KillCount { get; set; }

        public int Wave { get; set; }
    }
}
