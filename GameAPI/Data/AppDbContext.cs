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
                entity.Property(p => p.Username)
                    .IsRequired()
                    .HasMaxLength(50);
                entity.Property(p => p.Password)
                    .IsRequired()
                    .HasMaxLength(100);
                entity.Property(p => p.Score).IsRequired();
                
                // Index untuk query leaderboard cepat (sort berdasarkan Score DESC)
                entity.HasIndex(p => p.Score);
                // Index untuk search by username
                entity.HasIndex(p => p.Username);
             });

             // Seed data untuk testing
            modelBuilder.Entity<PlayerScore>().HasData(
                new PlayerScore
                {
                    Id = 1,
                    Username = "ProGamer",
                    Password = "password123",
                    Score = 1500,
                    KillCount = 30,
                    Wave = 15
                },
                new PlayerScore
                {
                    Id = 2,
                    Username = "Sniper",
                    Password = "sniper456",
                    Score = 1200,
                    KillCount = 25,
                    Wave = 12
                }
            );
        }
    }
}
