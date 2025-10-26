namespace GameAPI.Models
{
    public class PlayerScore
    {
        public int Id { get; set; }
        public string PlayerName { get; set; } = string.Empty; // Wajib
        public int Score { get; set; } // Wajib
        public DateTime CreatedAt { get; set; } = DateTime.UtcNow; // Otomatis
    }
}
