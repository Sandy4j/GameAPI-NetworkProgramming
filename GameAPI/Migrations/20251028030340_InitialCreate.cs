using System;
using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

#pragma warning disable CA1814 // Prefer jagged arrays over multidimensional

namespace GameAPI.Migrations
{
    /// <inheritdoc />
    public partial class InitialCreate : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.CreateTable(
                name: "PlayerScores",
                columns: table => new
                {
                    Id = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    PlayerName = table.Column<string>(type: "TEXT", maxLength: 100, nullable: false),
                    Score = table.Column<int>(type: "INTEGER", nullable: false),
                    Kills = table.Column<int>(type: "INTEGER", nullable: false),
                    Deaths = table.Column<int>(type: "INTEGER", nullable: false),
                    ShotsFired = table.Column<int>(type: "INTEGER", nullable: false),
                    ShotsHit = table.Column<int>(type: "INTEGER", nullable: false),
                    CreatedAt = table.Column<DateTime>(type: "TEXT", nullable: false, defaultValueSql: "CURRENT_TIMESTAMP"),
                    UpdatedAt = table.Column<DateTime>(type: "TEXT", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_PlayerScores", x => x.Id);
                });

            migrationBuilder.InsertData(
                table: "PlayerScores",
                columns: new[] { "Id", "CreatedAt", "Deaths", "Kills", "PlayerName", "Score", "ShotsFired", "ShotsHit", "UpdatedAt" },
                values: new object[,]
                {
                    { 1, new DateTime(2025, 10, 26, 3, 3, 39, 751, DateTimeKind.Utc).AddTicks(9792), 5, 30, "ProGamer", 1500, 150, 120, null },
                    { 2, new DateTime(2025, 10, 27, 3, 3, 39, 751, DateTimeKind.Utc).AddTicks(9798), 3, 25, "Sniper", 1200, 100, 95, null },
                    { 3, new DateTime(2025, 10, 27, 22, 3, 39, 751, DateTimeKind.Utc).AddTicks(9800), 10, 20, "Rusher", 980, 200, 80, null }
                });

            migrationBuilder.CreateIndex(
                name: "IX_PlayerScores_PlayerName",
                table: "PlayerScores",
                column: "PlayerName");

            migrationBuilder.CreateIndex(
                name: "IX_PlayerScores_Score_CreatedAt",
                table: "PlayerScores",
                columns: new[] { "Score", "CreatedAt" });
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "PlayerScores");
        }
    }
}
