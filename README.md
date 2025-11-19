# 🎮 GameAPI - Network Programming Project

Sistem terintegrasi yang terdiri dari REST API Backend (.NET) dan Game Shooter Client (C++/OpenGL) dengan fitur leaderboard, save/load game state, dan manajemen skor online.

## 📋 Deskripsi Proyek

Project ini merupakan implementasi Network Programming yang menggabungkan:
- **REST API Backend** berbasis ASP.NET Core dengan Entity Framework
- **Game Shooter Client** berbasis C++ dengan OpenGL
- **Database** SQLite untuk penyimpanan data
- **HTTP Communication** menggunakan CPR library (C++)

Game shooter dapat berkomunikasi dengan server untuk menyimpan skor, mengambil leaderboard, dan menyimpan/memuat state permainan secara online.

## ✨ Fitur Utama

### 🔧 REST API (Backend)
- ✅ **Manajemen Skor Pemain**
  - Create, Read, Update, Delete (CRUD) skor
  - Pagination dan sorting
  - Leaderboard top N pemain
  - Ranking pemain dan history
  - Statistik game (rata-rata skor, total kills, dll)
  
- ✅ **Game Session Management**
  - Save game state (score, wave, kills, custom data)
  - Load game state
  - Multiple active sessions per player
  - Deactivate/remove old sessions

- ✅ **Dokumentasi API Otomatis**
  - Swagger UI interaktif
  - OpenAPI specification
  
- ✅ **CORS Support**
  - Akses dari jaringan lokal
  - Support untuk client C++

### 🎮 Game Shooter Client
- ✅ **Integrasi API Lengkap**
  - Submit skor otomatis saat game over
  - Display leaderboard in-game
  - Save/load game progress ke server
  - Player authentication
  
- ✅ **Features Game**
  - Multiple characters
  - Wave-based gameplay
  - Kill counter & scoring system
  - Level system dengan JSON data
  
- ✅ **C++ API Client Library**
  - Type-safe data structures
  - Error handling
  - Singleton pattern manager
  - Easy-to-use API wrappers

## 🏗️ Teknologi yang Digunakan

### Backend
- **Framework**: ASP.NET Core 8.0
- **ORM**: Entity Framework Core
- **Database**: SQLite
- **API Documentation**: Swagger/OpenAPI
- **Language**: C# 12

### Game Client
- **Language**: C++17
- **Graphics**: OpenGL (GLFW, GLAD)
- **HTTP Client**: CPR library
- **JSON Parser**: nlohmann/json
- **Build System**: MSBuild / Visual Studio

## 📁 Struktur Proyek

```
GameAPI-NetworkProgramming/
├── GameAPI/                    # REST API Backend (.NET)
│   ├── Controllers/
│   │   ├── ScoresController.cs        # Endpoint manajemen skor
│   │   └── SessionsController.cs      # Endpoint game sessions
│   ├── Models/
│   │   ├── PlayerScore.cs             # Model skor pemain
│   │   └── GameSession.cs             # Model session game
│   ├── DTOs/                          # Data Transfer Objects
│   ├── Data/
│   │   └── AppDbContext.cs            # Database context
│   ├── Migrations/                     # EF Core migrations
│   └── Program.cs                      # Entry point & configuration
│
├── Shooter/                    # Game Client (C++)
│   ├── Shooter.cpp                    # Main game entry point
│   ├── core/                          # Game engine core
│   │   ├── Engine.cpp/h
│   │   ├── graphics_pipeline/
│   │   └── patterns/
│   ├── game/                          # Game logic
│   │   ├── entity/                    # Game entities
│   │   ├── level/                     # Level management
│   │   └── logic/                     # Game mechanics
│   ├── Integration/                   # API Integration
│   │   ├── GameAPIManager.cpp/h       # High-level API manager
│   │   ├── Integration.cpp/h          # Low-level API client
│   │   └── *.md                       # Integration docs
│   ├── assets/                        # Game assets
│   │   ├── character/                 # Character sprites
│   │   ├── data_levels/               # Level JSON files
│   │   ├── ui/                        # UI assets
│   │   └── font/
│   └── libraries/                     # External libraries
│
├── NETWORK_ACCESS_GUIDE.md     # Panduan akses network
├── vcpkg.json                  # Package dependencies
└── README.md                   # Dokumentasi ini
```

## 🚀 Cara Menjalankan

### Prerequisites
- **.NET 8.0 SDK** - [Download](https://dotnet.microsoft.com/download)
- **Visual Studio 2022** (untuk C++)
- **vcpkg** - Package manager untuk C++
- **Git**

### 1️⃣ Setup Backend (REST API)

```powershell
# Clone repository
git clone <repository-url>
cd GameAPI-NetworkProgramming

# Masuk ke direktori GameAPI
cd GameAPI

# Restore dependencies
dotnet restore

# Jalankan migrations (optional, database sudah ada)
dotnet ef database update

# Jalankan server
dotnet run --launch-profile http
```

Server akan berjalan di: `http://0.0.0.0:5155`

**Akses Swagger UI:**
- Lokal: `http://localhost:5155/swagger`
- Dari device lain: `http://<IP-SERVER>:5155/swagger`

### 2️⃣ Setup Game Client (Shooter)

```powershell
# Install dependencies via vcpkg
vcpkg install cpr:x64-windows
vcpkg install nlohmann-json:x64-windows
vcpkg integrate install

# Buka solution di Visual Studio
# Shooter.sln atau GameAPI.sln

# Build project (F7)
# Run project (F5 atau Ctrl+F5)
```

**Konfigurasi API Endpoint:**

Edit di `GameAPIManager.cpp` atau initialization code:
```cpp
GameAPIManager::GetInstance().Initialize("http://localhost:5155/api");
```

Ganti dengan IP server jika berbeda device.

### 3️⃣ Testing Koneksi

**Test API dari Browser:**
```
http://localhost:5155/api/scores
http://localhost:5155/api/scores/top/10
```

**Test dari Game:**
- Jalankan game
- Cek console untuk "API Connection: Success"
- Main game sampai game over
- Cek apakah skor ter-submit
- Buka leaderboard in-game

## 📡 API Endpoints

### Scores Controller

| Method | Endpoint | Deskripsi |
|--------|----------|-----------|
| `GET` | `/api/scores` | Get all scores (with pagination) |
| `GET` | `/api/scores/{id}` | Get specific score by ID |
| `GET` | `/api/scores/top/{n}` | Get top N scores (leaderboard) |
| `GET` | `/api/scores/rank/{username}` | Get player rank |
| `GET` | `/api/scores/player/{username}/history` | Get player's score history |
| `GET` | `/api/scores/stats` | Get overall game statistics |
| `POST` | `/api/scores` | Create new score |
| `PUT` | `/api/scores/{id}` | Update existing score |
| `DELETE` | `/api/scores/{id}` | Delete score |

### Sessions Controller

| Method | Endpoint | Deskripsi |
|--------|----------|-----------|
| `GET` | `/api/sessions/user/{username}` | Get user's active sessions |
| `GET` | `/api/sessions/{id}` | Get session by ID |
| `POST` | `/api/sessions` | Save new game session |
| `PUT` | `/api/sessions/{id}` | Update existing session |
| `DELETE` | `/api/sessions/{id}` | Delete session |
| `POST` | `/api/sessions/{id}/deactivate` | Deactivate session |

**Contoh Request/Response:** Lihat `GameAPI.http` atau Swagger UI

## 🎯 Cara Menggunakan API di Game

### Submit Score

```cpp
#include "GameAPIManager.h"

// Set credentials
GameAPIManager::GetInstance().SetPlayerCredentials(username, password);

// Submit skor saat game over
if (GameAPIManager::GetInstance().SubmitCurrentGameScore()) {
    std::cout << "Score submitted!" << std::endl;
}
```

### Get Leaderboard

```cpp
auto leaderboard = GameAPIManager::GetInstance().GetLeaderboard(10);

for (const auto& entry : leaderboard) {
    std::cout << entry.rank << ". " << entry.username 
              << " - " << entry.score << " pts" << std::endl;
}
```

### Save Game State

```cpp
#include "Integration.h"

GameSessionDto session;
session.username = currentPlayer;
session.currentScore = playerScore;
session.currentWave = waveNumber;
session.currentKillCount = killCount;
session.gameStateData = SerializeGameState(); // Custom JSON

auto result = apiClient.CreateGameSession(session);
if (result.success) {
    std::cout << "Game saved! Session ID: " << result.data.id << std::endl;
}
```

### Load Game State

```cpp
auto sessions = apiClient.GetUserSessions(username);

if (!sessions.data.empty()) {
    auto session = sessions.data[0]; // Latest active session
    
    playerScore = session.currentScore;
    waveNumber = session.currentWave;
    killCount = session.currentKillCount;
    DeserializeGameState(session.gameStateData);
}
```

## 🗄️ Database Schema

### PlayerScores Table
```sql
CREATE TABLE PlayerScores (
    Id INTEGER PRIMARY KEY AUTOINCREMENT,
    Username TEXT NOT NULL,
    Password TEXT NOT NULL,
    Score INTEGER NOT NULL,
    KillCount INTEGER DEFAULT 0,
    Wave INTEGER DEFAULT 0
);

CREATE INDEX IX_PlayerScores_Score ON PlayerScores(Score);
CREATE INDEX IX_PlayerScores_Username ON PlayerScores(Username);
```

### GameSessions Table
```sql
CREATE TABLE GameSessions (
    Id INTEGER PRIMARY KEY AUTOINCREMENT,
    Username TEXT NOT NULL,
    CurrentScore INTEGER NOT NULL,
    CurrentWave INTEGER NOT NULL,
    CurrentKillCount INTEGER NOT NULL,
    GameStateData TEXT NOT NULL,
    SavedAt TEXT NOT NULL,
    IsActive INTEGER NOT NULL DEFAULT 1
);

CREATE INDEX IX_GameSessions_Username ON GameSessions(Username);
CREATE INDEX IX_GameSessions_Username_IsActive ON GameSessions(Username, IsActive);
```

## 🔧 Konfigurasi

### Backend Configuration

**appsettings.json:**
```json
{
  "ConnectionStrings": {
    "DefaultConnection": "Data Source=game_scores.db"
  },
  "Logging": {
    "LogLevel": {
      "Default": "Information"
    }
  }
}
```

**launchSettings.json:**
```json
{
  "profiles": {
    "http": {
      "commandName": "Project",
      "launchBrowser": false,
      "applicationUrl": "http://0.0.0.0:5155",
      "environmentVariables": {
        "ASPNETCORE_ENVIRONMENT": "Development"
      }
    }
  }
}
```

### Game Client Configuration

Edit endpoint di initialization:
```cpp
// Development (localhost)
GameAPIManager::GetInstance().Initialize("http://localhost:5155/api");

// Production / Jaringan lokal
GameAPIManager::GetInstance().Initialize("http://192.168.1.100:5155/api");
```

## 📊 Fitur Network Programming

### ✅ Implemented Features
- [x] RESTful API dengan CRUD operations
- [x] HTTP Request/Response handling
- [x] JSON serialization/deserialization
- [x] Client-Server architecture
- [x] Database persistence
- [x] Error handling & validation
- [x] Cross-platform networking (Windows)
- [x] CORS support untuk local network
- [x] API documentation (Swagger)
- [x] Pagination & filtering
- [x] Entity relationships

### 🔄 Communication Flow

```
┌─────────────────┐                    ┌─────────────────┐
│   Game Client   │                    │   REST API      │
│   (C++ / CPR)   │◄──────HTTP────────►│  (ASP.NET Core) │
│                 │    JSON Request    │                 │
│  GameAPIManager │    JSON Response   │  Controllers    │
└─────────────────┘                    └─────────────────┘
         │                                      │
         │                                      │
         ▼                                      ▼
┌─────────────────┐                    ┌─────────────────┐
│  Game Manager   │                    │  AppDbContext   │
│  Score/Session  │                    │  EF Core        │
└─────────────────┘                    └─────────────────┘
                                                │
                                                ▼
                                       ┌─────────────────┐
                                       │  SQLite DB      │
                                       │  game_scores.db │
                                       └─────────────────┘
```

## 🧪 Testing

### API Testing dengan Swagger
1. Buka `http://localhost:5155/swagger`
2. Expand endpoint yang ingin dicoba
3. Klik "Try it out"
4. Isi parameters
5. Click "Execute"
6. Lihat response

### API Testing dengan HTTP File
Gunakan `GameAPI.http` di Visual Studio atau VS Code dengan REST Client extension.

### Game Integration Testing
1. Run API server
2. Run game client
3. Check console logs untuk connection status
4. Play game sampai game over
5. Verify skor ter-submit di Swagger/database
6. Check leaderboard in-game

## 📚 Dokumentasi Tambahan

Dokumentasi lengkap tersedia di folder `Shooter/Integration/`:
- **[README.md](Shooter/Integration/README.md)** - Quick start guide
- **[INTEGRATION_SUMMARY.md](Shooter/Integration/INTEGRATION_SUMMARY.md)** - Overview integrasi
- **[BUILD_INSTRUCTIONS.md](Shooter/Integration/BUILD_INSTRUCTIONS.md)** - Setup detail
- **[QUICK_START.md](Shooter/Integration/QUICK_START.md)** - Panduan cepat
- **[ARCHITECTURE.md](Shooter/Integration/ARCHITECTURE.md)** - Arsitektur sistem
- **[CODE_SNIPPETS.md](Shooter/Integration/CODE_SNIPPETS.md)** - Contoh kode
- **[NETWORK_ACCESS_GUIDE.md](NETWORK_ACCESS_GUIDE.md)** - Panduan akses network

## 🐛 Troubleshooting

### API Server tidak bisa diakses dari device lain

**Solusi:**
1. Pastikan firewall mengizinkan port 5155
2. Gunakan `http://0.0.0.0:5155` saat menjalankan server
3. Akses dengan IP address server, bukan `0.0.0.0`
4. Cek IP dengan `ipconfig` (Windows)

```powershell
# Tambahkan firewall rule
netsh advfirewall firewall add rule name="GameAPI" dir=in action=allow protocol=TCP localport=5155
```

### Game tidak bisa connect ke API

**Solusi:**
1. Cek API server sudah running
2. Verify endpoint URL di GameAPIManager
3. Test endpoint di browser terlebih dahulu
4. Cek console log untuk error detail
5. Pastikan CPR library ter-install dengan benar

### Database migration errors

**Solusi:**
```powershell
# Hapus database dan migrations
rm game_scores.db
rm -r Migrations/

# Buat migration baru
dotnet ef migrations add InitialCreate
dotnet ef database update
```

### Build errors di C++

**Solusi:**
1. Pastikan vcpkg sudah integrate
2. Verify dependencies sudah terinstall
3. Clean & rebuild solution
4. Check include paths dan library paths

## 🎓 Learning Outcomes

Project ini mengimplementasikan konsep:
- ✅ REST API design principles
- ✅ HTTP protocol (GET, POST, PUT, DELETE)
- ✅ JSON data format
- ✅ Client-Server architecture
- ✅ Database operations (CRUD)
- ✅ ORM (Object-Relational Mapping)
- ✅ API documentation (Swagger/OpenAPI)
- ✅ Cross-language integration (C# ↔ C++)
- ✅ Error handling & validation
- ✅ Pagination & filtering
- ✅ Authentication concepts
- ✅ Network programming best practices

## 📝 License

Project ini dibuat untuk keperluan pembelajaran Network Programming.

## 👥 Tim Pengembang

<table>
  <tr>
    <td align="center">
      <a href="https://github.com/Sandy4j">
        <img src="https://github.com/Sandy4j.png" width="100px;" alt="Sandy4j"/><br />
        <sub><b>Sandy4j</b></sub>
      </a><br />
      <sub>REST API Backend</sub>
    </td>
    <td align="center">
      <a href="https://github.com/Xtripsy">
        <img src="https://github.com/Xtripsy.png" width="100px;" alt="Xtripsy"/><br />
        <sub><b>Xtripsy</b></sub>
      </a><br />
      <sub>Game Shooter Client</sub>
    </td>
  </tr>
</table>

---

## 📞 Support

Jika ada pertanyaan atau issues:
1. Check dokumentasi di folder `Integration/`
2. Lihat troubleshooting section
3. Open issue di repository
4. Contact tim pengembang

---

**Happy Coding! 🚀**

