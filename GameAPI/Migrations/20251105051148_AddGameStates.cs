using System;
using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace GameAPI.Migrations
{
    /// <inheritdoc />
    public partial class AddGameStates : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.CreateTable(
                name: "GameSessions",
                columns: table => new
                {
                    Id = table.Column<int>(type: "INTEGER", nullable: false)
                        .Annotation("Sqlite:Autoincrement", true),
                    Username = table.Column<string>(type: "TEXT", maxLength: 50, nullable: false),
                    CurrentScore = table.Column<int>(type: "INTEGER", nullable: false),
                    CurrentWave = table.Column<int>(type: "INTEGER", nullable: false),
                    CurrentKillCount = table.Column<int>(type: "INTEGER", nullable: false),
                    GameStateData = table.Column<string>(type: "TEXT", nullable: false),
                    SavedAt = table.Column<DateTime>(type: "TEXT", nullable: false),
                    IsActive = table.Column<bool>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_GameSessions", x => x.Id);
                });

            migrationBuilder.CreateIndex(
                name: "IX_GameSessions_Username",
                table: "GameSessions",
                column: "Username");

            migrationBuilder.CreateIndex(
                name: "IX_GameSessions_Username_IsActive",
                table: "GameSessions",
                columns: new[] { "Username", "IsActive" });
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "GameSessions");
        }
    }
}
