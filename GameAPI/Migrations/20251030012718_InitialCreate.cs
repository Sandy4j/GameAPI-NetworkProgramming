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
                    Username = table.Column<string>(type: "TEXT", maxLength: 50, nullable: false),
                    Password = table.Column<string>(type: "TEXT", maxLength: 100, nullable: false),
                    Score = table.Column<int>(type: "INTEGER", nullable: false),
                    KillCount = table.Column<int>(type: "INTEGER", nullable: false),
                    Wave = table.Column<int>(type: "INTEGER", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_PlayerScores", x => x.Id);
                });

            migrationBuilder.InsertData(
                table: "PlayerScores",
                columns: new[] { "Id", "KillCount", "Password", "Score", "Username", "Wave" },
                values: new object[,]
                {
                    { 1, 30, "password123", 1500, "ProGamer", 15 },
                    { 2, 25, "sniper456", 1200, "Sniper", 12 },
                    { 3, 20, "rush789", 980, "Rusher", 10 }
                });

            migrationBuilder.CreateIndex(
                name: "IX_PlayerScores_Score",
                table: "PlayerScores",
                column: "Score");

            migrationBuilder.CreateIndex(
                name: "IX_PlayerScores_Username",
                table: "PlayerScores",
                column: "Username");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "PlayerScores");
        }
    }
}
