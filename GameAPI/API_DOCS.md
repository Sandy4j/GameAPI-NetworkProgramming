# ?? API Documentation

Complete API reference for GameAPI endpoints.

---

## Base URL

```
Development: https://localhost:7016/api
Production: https://your-domain.com/api
```

---

## Authentication

Currently **no authentication** required. For production, implement JWT authentication.

---

## Error Responses

All endpoints return standard HTTP status codes:

| Code | Meaning |
|------|---------|
| 200 | OK - Request successful |
| 201 | Created - Resource created |
| 204 | No Content - Successful with no response body |
| 400 | Bad Request - Invalid input |
| 404 | Not Found - Resource not found |
| 500 | Internal Server Error |

### Error Response Format:
```json
{
  "message": "Error description here"
}
```

---

## Endpoints

### 1. Get All Scores

Get paginated list of all player scores.

**Endpoint:** `GET /api/scores`

**Query Parameters:**

| Parameter | Type | Default | Description |
|-----------|------|---------|-------------|
| page | int | 1 | Page number (min: 1) |
| pageSize | int | 10 | Items per page (min: 1, max: 100) |

**Request Example:**
```http
GET /api/scores?page=1&pageSize=10
```

**Response (200 OK):**
```json
{
  "data": [
    {
      "id": 1,
      "playerName": "ProGamer",
      "score": 1500,
    "kills": 30,
      "deaths": 5,
      "shotsFired": 150,
      "shotsHit": 120,
  "accuracy": 80.0,
      "createdAt": "2025-10-26T03:03:39.7519792Z",
    "updatedAt": null
    }
  ],
  "pagination": {
    "page": 1,
    "pageSize": 10,
    "totalCount": 3,
    "totalPages": 1
  }
}
```

---

### 2. Get Score by ID

Get a specific player score by its ID.

**Endpoint:** `GET /api/scores/{id}`

**Path Parameters:**

| Parameter | Type | Required | Description |
|-----------|------|----------|-------------|
| id | int | Yes | Score ID |

**Request Example:**
```http
GET /api/scores/1
```

**Response (200 OK):**
```json
{
  "id": 1,
  "playerName": "ProGamer",
  "score": 1500,
  "kills": 30,
  "deaths": 5,
  "shotsFired": 150,
  "shotsHit": 120,
  "accuracy": 80.0,
  "createdAt": "2025-10-26T03:03:39.7519792Z",
  "updatedAt": null
}
```

**Response (404 Not Found):**
```json
{
  "message": "Score with ID 999 not found"
}
```

---

### 3. Get Top Scores (Leaderboard)

Get top N highest scores ordered by score (descending).

**Endpoint:** `GET /api/scores/top/{n}`

**Path Parameters:**

| Parameter | Type | Default | Description |
|-----------|------|---------|-------------|
| n | int | 10 | Number of top scores to return (min: 1, max: 100) |

**Request Example:**
```http
GET /api/scores/top/5
```

**Response (200 OK):**
```json
[
  {
    "rank": 1,
    "playerName": "ProGamer",
    "score": 1500,
    "kills": 30,
    "accuracy": 80.0,
  "createdAt": "2025-10-26T03:03:39.7519792Z"
  },
  {
    "rank": 2,
    "playerName": "Sniper",
    "score": 1200,
    "kills": 25,
    "accuracy": 95.0,
    "createdAt": "2025-10-27T03:03:39.7519798Z"
  }
]
```

---

### 4. Get Player Rank

Get a player's current rank based on their best score.

**Endpoint:** `GET /api/scores/rank/{playerName}`

**Path Parameters:**

| Parameter | Type | Required | Description |
|-----------|------|----------|-------------|
| playerName | string | Yes | Player name (case-insensitive) |

**Request Example:**
```http
GET /api/scores/rank/ProGamer
```

**Response (200 OK):**
```json
{
  "playerName": "ProGamer",
  "rank": 1,
"score": 1500,
  "totalPlayers": 3
}
```

**Response (404 Not Found):**
```json
{
  "message": "Player 'NonExistent' not found"
}
```

---

### 5. Get Player History

Get all score entries for a specific player.

**Endpoint:** `GET /api/scores/player/{playerName}/history`

**Path Parameters:**

| Parameter | Type | Required | Description |
|-----------|------|----------|-------------|
| playerName | string | Yes | Player name (case-insensitive) |

**Request Example:**
```http
GET /api/scores/player/ProGamer/history
```

**Response (200 OK):**
```json
[
  {
    "id": 5,
    "playerName": "ProGamer",
    "score": 1650,
    "kills": 35,
    "deaths": 5,
    "shotsFired": 160,
    "shotsHit": 130,
    "accuracy": 81.25,
    "createdAt": "2025-10-28T05:00:00Z",
    "updatedAt": null
  },
  {
    "id": 1,
    "playerName": "ProGamer",
    "score": 1500,
    "kills": 30,
    "deaths": 5,
    "shotsFired": 150,
    "shotsHit": 120,
    "accuracy": 80.0,
    "createdAt": "2025-10-26T03:03:39.7519792Z",
    "updatedAt": null
  }
]
```

**Response (404 Not Found):**
```json
{
  "message": "No scores found for player 'NonExistent'"
}
```

---

### 6. Get Statistics

Get overall game statistics.

**Endpoint:** `GET /api/scores/stats`

**Request Example:**
```http
GET /api/scores/stats
```

**Response (200 OK):**
```json
{
  "totalGames": 15,
  "totalPlayers": 8,
  "highestScore": 1800,
  "averageScore": 1125.5
}
```

---

### 7. Create Score

Create a new player score entry.

**Endpoint:** `POST /api/scores`

**Request Headers:**
```
Content-Type: application/json
```

**Request Body:**
```json
{
  "playerName": "NewPlayer",
  "score": 800,
  "kills": 15,
  "deaths": 8,
  "shotsFired": 100,
  "shotsHit": 70
}
```

**Body Parameters:**

| Field | Type | Required | Constraints |
|-------|------|----------|-------------|
| playerName | string | Yes | Max 100 characters |
| score | int | Yes | >= 0 |
| kills | int | No | >= 0, default: 0 |
| deaths | int | No | >= 0, default: 0 |
| shotsFired | int | No | >= 0, default: 0 |
| shotsHit | int | No | >= 0, <= shotsFired, default: 0 |

**Response (201 Created):**
```json
{
  "id": 4,
  "playerName": "NewPlayer",
  "score": 800,
  "kills": 15,
  "deaths": 8,
  "shotsFired": 100,
  "shotsHit": 70,
  "accuracy": 70.0,
  "createdAt": "2025-10-28T03:10:00.000Z",
  "updatedAt": null
}
```

**Response (400 Bad Request):**
```json
{
  "message": "ShotsHit cannot exceed ShotsFired"
}
```

Or validation errors:
```json
{
  "errors": {
    "PlayerName": ["PlayerName is required"],
    "Score": ["Score must be >= 0"]
  }
}
```

---

### 8. Update Score

Update an existing score entry.

**Endpoint:** `PUT /api/scores/{id}`

**Path Parameters:**

| Parameter | Type | Required | Description |
|-----------|------|----------|-------------|
| id | int | Yes | Score ID to update |

**Request Headers:**
```
Content-Type: application/json
```

**Request Body:**
```json
{
  "playerName": "UpdatedPlayer",
  "score": 950,
  "kills": 20,
  "deaths": 8,
  "shotsFired": 120,
  "shotsHit": 90
}
```

**Request Example:**
```http
PUT /api/scores/4
Content-Type: application/json

{
  "playerName": "UpdatedPlayer",
  "score": 950,
  "kills": 20,
  "deaths": 8,
  "shotsFired": 120,
  "shotsHit": 90
}
```

**Response (204 No Content)**

No response body on success.

**Response (404 Not Found):**
```json
{
  "message": "Score with ID 999 not found"
}
```

**Response (400 Bad Request):**
```json
{
  "message": "ShotsHit cannot exceed ShotsFired"
}
```

---

### 9. Delete Score

Delete a score entry.

**Endpoint:** `DELETE /api/scores/{id}`

**Path Parameters:**

| Parameter | Type | Required | Description |
|-----------|------|----------|-------------|
| id | int | Yes | Score ID to delete |

**Request Example:**
```http
DELETE /api/scores/4
```

**Response (204 No Content)**

No response body on success.

**Response (404 Not Found):**
```json
{
  "message": "Score with ID 999 not found"
}
```

---

## Data Models

### PlayerScoreResponseDto

```typescript
{
  id: number;      // Unique identifier
  playerName: string;      // Player name (max 100 chars)
  score: number;           // Game score (>= 0)
  kills: number;           // Number of kills
  deaths: number;   // Number of deaths
  shotsFired: number;      // Total shots fired
  shotsHit: number;    // Shots that hit target
  accuracy: number;        // Computed: (shotsHit/shotsFired) * 100
  createdAt: string;       // ISO 8601 datetime (UTC)
  updatedAt: string | null; // ISO 8601 datetime (UTC) or null
}
```

### CreatePlayerScoreDto

```typescript
{
  playerName: string;      // Required, max 100 chars
  score: number;           // Required, >= 0
  kills?: number;          // Optional, >= 0, default: 0
  deaths?: number;         // Optional, >= 0, default: 0
  shotsFired?: number;     // Optional, >= 0, default: 0
  shotsHit?: number;     // Optional, >= 0, <= shotsFired, default: 0
}
```

### LeaderboardEntryDto

```typescript
{
  rank: number;   // Player's rank position
  playerName: string;      // Player name
  score: number;// Best score
  kills: number;        // Number of kills
  accuracy: number;   // Accuracy percentage
  createdAt: string;       // ISO 8601 datetime (UTC)
}
```

### PlayerRankDto

```typescript
{
  playerName: string;      // Player name
  rank: number;            // Current rank
  score: number;   // Best score
  totalPlayers: number;  // Total number of unique players
}
```

---

## Rate Limiting

Currently **no rate limiting** implemented. For production, consider:

- Rate limiting per IP
- API key authentication
- Request throttling

---

## CORS

CORS is configured to allow all origins in development. For production:

1. Configure specific origins
2. Restrict allowed methods
3. Set appropriate headers

---

## Best Practices

### 1. Pagination
Always use pagination for large datasets:
```http
GET /api/scores?page=1&pageSize=20
```

### 2. Error Handling
Always check status code and handle errors:
```javascript
if (response.status === 200) {
  // Success
} else if (response.status === 404) {
  // Not found
} else {
  // Other error
}
```

### 3. Validation
Validate input before sending:
- PlayerName: Not empty, max 100 chars
- Score: >= 0
- ShotsHit: <= ShotsFired

### 4. Performance
- Cache leaderboard data (updates every X minutes)
- Use pagination for large result sets
- Index queries properly (already optimized)

---

## Changelog

### Version 1.0.0 (2025-10-28)
- Initial release
- Basic CRUD operations
- Leaderboard system
- Player ranking
- Statistics endpoint

---

## Support

For issues or questions:
- GitHub Issues: [GameAPI-NetworkProgramming](https://github.com/Sandy4j/GameAPI-NetworkProgramming/issues)
- Documentation: `README.md`

---

**API Version:** 1.0.0  
**Last Updated:** October 28, 2025  
**Author:** Sandy4j
