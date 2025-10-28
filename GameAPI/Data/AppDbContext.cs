using GameAPI.Models;
using Microsoft.EntityFrameworkCore;

namespace GameAPI.Data
{
    public class AppDbContext : DbContext
    {
        public AppDbContext(DbContextOptions<AppDbContext> options) : base(options) { }

        public DbSet<PlayerScore> PlayerScores => Set<PlayerScore>();

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder.Entity<PlayerScore>(entity =>
            {
                entity.Property(p => p.PlayerName)
                    .IsRequired()
                    .HasMaxLength(100);
                entity.Property(p => p.Score).IsRequired();
                entity.Property(p => p.CreatedAt)
                    .HasDefaultValueSql("CURRENT_TIMESTAMP");
                // Index untuk query leaderboard cepat (sort berdasarkan Score DESC, CreatedAt ASC)
                entity.HasIndex(p => new { p.Score, p.CreatedAt });
                // Index untuk search by player name
                entity.HasIndex(p => p.PlayerName);
                // Ignore computed property
                entity.Ignore(p => p.Accuracy);
            });

            // Seed data untuk testing
            modelBuilder.Entity<PlayerScore>().HasData(
                new PlayerScore
                {
                    Id = 1,
                    PlayerName = "ProGamer",
                    Score = 1500,
                    Kills = 30,
                    Deaths = 5,
                    ShotsFired = 150,
                    ShotsHit = 120,
                    CreatedAt = DateTime.UtcNow.AddDays(-2)
                },
                new PlayerScore
                {
                    Id = 2,
                    PlayerName = "Sniper",
                    Score = 1200,
                    Kills = 25,
                    Deaths = 3,
                    ShotsFired = 100,
                    ShotsHit = 95,
                    CreatedAt = DateTime.UtcNow.AddDays(-1)
                },
                new PlayerScore
                {
                    Id = 3,
                    PlayerName = "Rusher",
                    Score = 980,
                    Kills = 20,
                    Deaths = 10,
                    ShotsFired = 200,
                    ShotsHit = 80,
                    CreatedAt = DateTime.UtcNow.AddHours(-5)
                }
            );
        }
    }
}
